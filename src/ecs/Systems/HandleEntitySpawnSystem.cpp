/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** HandleEntitySpawnSystem
*/

#include "HandleEntitySpawnSystem.hh"
#include <lua.h>

RType::HandleEntitySpawnSystem::HandleEntitySpawnSystem(std::function<std::shared_ptr<Entity>()> addEntity, std::function<void(std::shared_ptr<Entity>)> deleteEntity):
    ASystem(S_ENTITY_MOB_SYSTEM, addEntity, deleteEntity), _prevTime(-1)
{
    createEntityMap();
}

RType::HandleEntitySpawnSystem::HandleEntitySpawnSystem(std::function<std::shared_ptr<Entity>()> addEntity, std::function<void(std::shared_ptr<Entity>)> deleteEntity, std::function<void(const std::basic_string<unsigned char> &message)> sendToAllClient):
    ASystem(S_ENTITY_MOB_SYSTEM, addEntity, deleteEntity), _sendToAllClient(sendToAllClient)
{
    createEntityMap();
}

RType::HandleEntitySpawnSystem::~HandleEntitySpawnSystem()
{
}

void RType::HandleEntitySpawnSystem::effects(std::vector<std::shared_ptr<RType::Entity>> entities) {
    for (const auto &entity : entities) {
        if (verifyRequiredComponent(entity)) {
            effect(entity);
            continue;
        } else if (entity->getComponent<EntityTypeComponent>() != nullptr && entity->getComponent<EntityTypeComponent>()->getEntityType() == RType::E_PLAYER) {
            if (entity->getComponent<PowerUpComponent>() != nullptr && entity->getComponent<PowerUpComponent>()->getPowerUps(RType::SHIELD) == true) {
                entity->getComponent<PowerUpComponent>()->setPowerUps(RType::SHIELD, false);
                createEntity(RType::E_SHIELD, entity, std::make_pair(0, 0));
            }
            if (entity->getComponent<PowerUpComponent>() != nullptr && entity->getComponent<PowerUpComponent>()->getPowerUps(RType::FORCE_POD) == true) {
                switch (entity->getComponent<EntityTypeComponent>()->getForcePodType()){
                    case F_LVL_1:
                        entity->getComponent<PowerUpComponent>()->setPowerUps(RType::FORCE_POD, false);
                        createEntity(RType::E_FORCEPOD, entity, std::make_pair(0, 0));
                        break;
                    case F_LVL_2:
                        entity->getComponent<PowerUpComponent>()->setPowerUps(RType::FORCE_POD, false);
                        createEntity(RType::E_FORCEPOD_2, entity, std::make_pair(0, 0));
                        break;
                    default:
                    break;
                }
            }
        }
    }
}

void RType::HandleEntitySpawnSystem::effect(std::shared_ptr<RType::Entity> entity)
{
    lua_State *luaState;
    int time = entity->getComponent<RType::ClockComponent>()->getClock(LEVEL_CLOCK).getElapsedTime().asSeconds();

    if (verifyRequiredComponent(entity) == false || time == _prevTime)
        return;
    luaState = entity->getComponent<RType::ParseLevelInfoComponent>()->getLuaState();
    if (entity->getComponent<RType::ParseLevelInfoComponent>()->getFunctionPushed() == false) {
        lua_pushlightuserdata(luaState, this);
        lua_pushcclosure(luaState, &HandleEntitySpawnSystem::luaTrampolineCreateEntity, 1);
        lua_setglobal(luaState, "createEntity");
        entity->getComponent<RType::ParseLevelInfoComponent>()->setFunctionPushed(true);
    }
    lua_getglobal(luaState, "Level");
    if (!lua_istable(luaState, -1)) {
        std::cerr << "Error: 'level' is not a table in Lua." << std::endl;
        lua_pop(luaState, 1);
        return;
    }
    lua_getfield(luaState, -1, "update");
    if (!lua_isfunction(luaState, -1)) {
        std::cerr << "Error: 'update' is not a function in Lua." << std::endl;
        lua_pop(luaState, 2);
        return;
    }
    lua_pushinteger(luaState, time);
    if (lua_pcall(luaState, 1, 0, 0) != LUA_OK) {
        std::cerr << "Error calling 'update': " << lua_tostring(luaState, -1) << std::endl;
        lua_pop(luaState, 1);
    }
    lua_pop(luaState, 1);
    _prevTime = time;
}

bool RType::HandleEntitySpawnSystem::verifyRequiredComponent(std::shared_ptr<RType::Entity> entity)
{
    if (GET_ENTITY_TYPE(entity) == RType::E_WINDOW &&
        entity->getComponent<RType::ClockComponent>() != nullptr &&
        entity->getComponent<RType::ParseLevelInfoComponent>() != nullptr)
        return true;
    return false;
}

int RType::HandleEntitySpawnSystem::luaTrampolineCreateEntity(lua_State *L)
{
    HandleEntitySpawnSystem *instance = static_cast<HandleEntitySpawnSystem *>(lua_touserdata(L, lua_upvalueindex(1)));

    instance->createEntity(L);
    return 0;
}

void RType::HandleEntitySpawnSystem::createEntity(lua_State *LuaState)
{
    Json::Reader reader;
    Json::Value entityInfo;
    std::ifstream file;
    std::shared_ptr<RType::Entity> entity = _addEntity();
    EntityType type = static_cast<EntityType>(luaL_checkinteger(LuaState, 1));
    int posY = luaL_checkinteger(LuaState, 2);
    int posX = luaL_checkinteger(LuaState, 3);
    std::string filepath("./config/entities/" + _entityTypeMap[type] + ".json");

    file.open(filepath);
    if (!file.is_open() || !reader.parse(file, entityInfo)) {
        std::cerr << "Error while reading or parsing the json: " << filepath << std::endl;
        return;
    }
    file.close();
    entity->PUSH_TYPE_E(static_cast<EntityType>(type));
    POS_COMPONENT position = entity->PUSH_POS_E(posX, posY);
    entity->PUSH_SCALE_E(entityInfo["scale"]["x"].asFloat(),
                         entityInfo["scale"]["y"].asFloat());
    entity->PUSH_RECT_E(entityInfo["rect"]["x"].asInt(),
                        entityInfo["rect"]["y"].asInt(),
                        entityInfo["rect"]["width"].asInt(),
                        entityInfo["rect"]["height"].asInt());
    entity->PUSH_CLOCK_E();
    if (entityInfo["health"].asBool() == true)
        entity->PUSH_HEALTH_E(entityInfo["health"].asInt());
    if (entityInfo["damage"].asBool() == true)
        entity->PUSH_DAMAGE_E(entityInfo["damage"].asInt());
    if (entityInfo["speed"].asBool() == true)
        entity->PUSH_VELOCITY_E(SERVER_SPEED(entityInfo["speed"].asInt()));
    if (entityInfo["pattern"].asBool() == true)
        entity->PUSH_PATTERN_E(static_cast<RType::PatternType>(entityInfo["pattern"].asInt()));
    if (entityInfo["isShooting"].asBool() == true) {
        auto action = entity->PUSH_ACTION_E();
        action->setActions(SHOOTING, true);
    }
    if (entityInfo["intervalShoot"].asBool() == true) {
        entity->PUSH_INTERVALSHOOT_E(entityInfo["intervalShoot"].asFloat());
    }
    _sendToAllClient(Encoder::newEntity(type, entity->getId(), position->getPositionX(), position->getPositionY()));
}

void RType::HandleEntitySpawnSystem::createEntity(RType::EntityType type,
                                                  std::shared_ptr<RType::Entity> toFollow,
                                                  std::pair<int, int> offset) {
    Json::Reader reader;
    Json::Value entityInfo;
    std::ifstream file;
    std::shared_ptr<RType::Entity> entity = _addEntity();
    std::string filepath("./config/entities/" + _entityTypeMap[type] + ".json");
    int posX = toFollow->getComponent<PositionComponent>()->getPositionY() - offset.first;
    int posY = toFollow->getComponent<PositionComponent>()->getPositionY() - offset.second;
    bool isFollowing = false;

    file.open(filepath);
    if (!file.is_open() || !reader.parse(file, entityInfo)) {
        std::cerr << "Error while reading or parsing the json: " << filepath << std::endl;
        return;
    }
    file.close();
    entity->PUSH_TYPE_E(static_cast<EntityType>(type));
    POS_COMPONENT position = entity->PUSH_POS_E(posX, posY);
    entity->PUSH_SCALE_E(entityInfo["scale"]["x"].asFloat(),
                         entityInfo["scale"]["y"].asFloat());
    entity->PUSH_RECT_E(entityInfo["rect"]["x"].asInt(),
                        entityInfo["rect"]["y"].asInt(),
                        entityInfo["rect"]["width"].asInt(),
                        entityInfo["rect"]["height"].asInt());
    entity->PUSH_CLOCK_E();
    if (entityInfo["health"].asBool() == true)
        entity->PUSH_HEALTH_E(entityInfo["health"].asInt());
    if (entityInfo["damage"].asBool() == true)
        entity->PUSH_DAMAGE_E(entityInfo["damage"].asInt());
    if (entityInfo["speed"].asBool() == true)
        entity->PUSH_VELOCITY_E(SERVER_SPEED(entityInfo["speed"].asInt()));
    if (entityInfo["pattern"].asBool() == true) {
        entity->PUSH_PATTERN_E(static_cast<RType::PatternType>(entityInfo["pattern"].asInt()));
        if (entityInfo["pattern"].asInt() == RType::FOLLOW_PLAYER) {
            entity->SET_ENTITY_TO_FOLLOW_E(toFollow);
            isFollowing = true;
        }
    }
    if (entityInfo["isShooting"].asBool() == true) {
        auto action = entity->PUSH_ACTION_E();
        action->setActions(SHOOTING, true);
    }
    if (entityInfo["intervalShoot"].asBool() == true) {
        entity->PUSH_INTERVALSHOOT_E(entityInfo["intervalShoot"].asFloat());
    }
    if (isFollowing == true) {
        _sendToAllClient(Encoder::newEntity(type, entity->getId(), position->getPositionX(), position->getPositionY(), toFollow->getId()));
    } else {
        _sendToAllClient(Encoder::newEntity(type, entity->getId(), position->getPositionX(), position->getPositionY()));
    }
}

void RType::HandleEntitySpawnSystem::createEntityMap(void)
{
    _entityTypeMap[E_OTHER] = "other";
    _entityTypeMap[E_WINDOW] = "window";
    _entityTypeMap[E_PLAYER] = "player";
    _entityTypeMap[E_ALLIES] = "player";
    _entityTypeMap[E_SMALL_SPACESHIP] = "small_spaceship";
    _entityTypeMap[E_OCTOPUS] = "octopus";
    _entityTypeMap[E_FLY] = "fly";
    _entityTypeMap[E_BOSS] = "boss";
    _entityTypeMap[E_BUTTON] = "button";
    _entityTypeMap[E_LAYER] = "layer";
    _entityTypeMap[E_BULLET] = "bullet";
    _entityTypeMap[E_SHIELD] = "shield";
    _entityTypeMap[E_ITEM_WEAPON] = "item_weapon";
    _entityTypeMap[E_ITEM_SHIELD] = "item_shield";
    _entityTypeMap[E_ITEM_HEAL] = "item_heal";
    _entityTypeMap[E_BULLET] = "bullet";
    _entityTypeMap[E_BULLET_2] = "bullet_2";
    _entityTypeMap[E_BULLET_3] = "bullet_3";
    _entityTypeMap[E_BULLET_4] = "bullet_4";
    _entityTypeMap[E_ENNEMY_BULLET] = "ennemy_bullet";
    _entityTypeMap[E_BULLET_EFFECT] = "bullet_effect";
    _entityTypeMap[E_HIT_EFFECT] = "hit_effect";
    _entityTypeMap[E_EXPLOSION_EFFECT] = "explosion_effect";
    _entityTypeMap[E_TEXT] = "text";
    _entityTypeMap[E_ITEM_FORCEPOD] = "item_forcepod";
    _entityTypeMap[E_FORCEPOD] = "forcepod";
    _entityTypeMap[E_FORCEPOD_BULLET] = "forcepod_bullet";
    _entityTypeMap[E_FORCEPOD_2] = "forcepod2";
    _entityTypeMap[E_BULLET_LASER] = "laser";
    _entityTypeMap[E_BULLET_LASER_2] = "laser2";
    _entityTypeMap[E_BULLET_LASER_3] = "laser3";
    _entityTypeMap[E_BULLET_LASER_4] = "laser4";
}

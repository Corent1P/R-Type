/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** HandleEntitySpawnSystem
*/

#include "HandleEntitySpawnSystem.hh"

RType::HandleEntitySpawnSystem::HandleEntitySpawnSystem(std::function<std::shared_ptr<Entity>()> addEntity, std::function<void(std::shared_ptr<Entity>)> deleteEntity):
    ASystem(S_ENTITY_MOB_SYSTEM, addEntity, deleteEntity)
{
}

RType::HandleEntitySpawnSystem::HandleEntitySpawnSystem(std::function<std::shared_ptr<Entity>()> addEntity, std::function<void(std::shared_ptr<Entity>)> deleteEntity, std::function<void(const std::basic_string<unsigned char> &message)> sendToAllClient):
    ASystem(S_ENTITY_MOB_SYSTEM, addEntity, deleteEntity), _sendToAllClient(sendToAllClient)
{
}

RType::HandleEntitySpawnSystem::~HandleEntitySpawnSystem()
{
}

void RType::HandleEntitySpawnSystem::effect(std::shared_ptr<RType::Entity> entity)
{
    if (entity->getComponent<RType::ClockComponent>()->getClock(RType::SPAWN_CLOCK).getElapsedTime().asSeconds() > 2) {
        createEntity(1920, _y_spawn, E_FLY);
        createEntity(1920, _y_spawn + 100, E_OCTOPUS);
        createEntity(1920, _y_spawn - 100, E_SMALL_SPACESHIP);
        entity->getComponent<RType::ClockComponent>()->getClock(RType::SPAWN_CLOCK).restart();
        _y_spawn += 100 * _sign;
        if (_y_spawn <= 100 || _y_spawn >= 700)
            _sign *= -1;
    }
}

bool RType::HandleEntitySpawnSystem::verifyRequiredComponent(std::shared_ptr<RType::Entity> entity)
{
    if (GET_ENTITY_TYPE(entity) == RType::E_WINDOW && entity->getComponent<RType::ClockComponent>() != nullptr)
        return true;
    return false;
}

void RType::HandleEntitySpawnSystem::createEntity(int posX, int posY, EntityType type)
{
    Json::Reader reader;
    Json::Value entityInfo;
    std::ifstream file;
    std::shared_ptr<RType::Entity> entity = _addEntity();
    std::string filepath("./config/entities/");

    filepath += std::to_string(type);
    filepath += ".json";
    file.open(filepath);
    if (!file.is_open() || !reader.parse(file, entityInfo)) {
        std::cerr << "Error while reading or parsing the json: " << filepath << std::endl;
        return;
    }
    file.close();
    entity->PUSH_TYPE_E(type);
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

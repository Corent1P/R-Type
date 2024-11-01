/*
** EPITECH PROJECT, 2024
** rType
** File description:
** AttackPatterns
*/

#include "AttackPatterns.hh"

void RType::AttackPatterns::spawnBabyFly(std::shared_ptr<RType::Entity> boss, std::function<std::shared_ptr<Entity>()> addEntity, std::function<void(const std::basic_string<unsigned char> &message)> sendMessageToAllClient)
{
    auto position = boss->getComponent<PositionComponent>();
    if (!position)
        return;

    int bossX = position->getPositionX();
    int bossY = position->getPositionY();


    for (int i = 0; i < 5; i++) {
        int posY = bossY + i * 100;
        createEntity(E_BABY_FLY, bossX, posY, addEntity, sendMessageToAllClient);
    }
}

void RType::AttackPatterns::spawnSting(std::shared_ptr<RType::Entity> boss, std::function<std::shared_ptr<Entity>()> addEntity, std::function<void(const std::basic_string<unsigned char> &message)> sendMessageToAllClient)
{
    auto position = boss->getComponent<PositionComponent>();
    auto rect = boss->getComponent<IntRectComponent>();
    auto scale = boss->getComponent<ScaleComponent>();

    if (!position || !rect || !scale)
        return;

    int bossX = position->getPositionX();
    int bossY = position->getPositionY();
    int bossHeight = rect->getIntRectHeight() * scale->getScaleY();

    for (int i = 0; i < 10; i++) {
        int posY = bossY - 100 + (std::rand() % (bossHeight + 200));

        createEntity(E_STING, bossX, posY, addEntity, sendMessageToAllClient);
    }
}

void RType::AttackPatterns::spaceShipShoot(std::shared_ptr<RType::Entity> boss, std::function<std::shared_ptr<Entity>()> addEntity, std::function<void(const std::basic_string<unsigned char> &message)> sendMessageToAllClient)
{
    auto position = boss->getComponent<PositionComponent>();
    auto rect = boss->getComponent<IntRectComponent>();
    auto scale = boss->getComponent<ScaleComponent>();

    if (!position || !rect || !scale)
        return;


    int bossX = position->getPositionX();
    int bossY = position->getPositionY();
    int bossHeight = rect->getIntRectHeight() * scale->getScaleY();

    int posY = bossY + (bossHeight / 2) + 50;

    createEntity(E_SPACE_SHIP_BULLET, bossX, posY, addEntity, sendMessageToAllClient);
}

void RType::AttackPatterns::waveShoot(std::shared_ptr<RType::Entity> boss, std::function<std::shared_ptr<Entity>()> addEntity, std::function<void(const std::basic_string<unsigned char> &message)> sendMessageToAllClient)
{
    auto position = boss->getComponent<PositionComponent>();
    auto rect = boss->getComponent<IntRectComponent>();
    auto scale = boss->getComponent<ScaleComponent>();

    if (!position || !rect || !scale)
        return;


    int bossX = position->getPositionX();
    int bossY = position->getPositionY();
    int bossHeight = rect->getIntRectHeight() * scale->getScaleY();

    int posY = bossY + (bossHeight / 2) + 50;

    createEntity(E_SPACE_SHIP_BULLET, bossX, posY, addEntity, sendMessageToAllClient);
    createEntity(E_SPACE_SHIP_SEMI_DIAGONAL_UP, bossX, posY, addEntity, sendMessageToAllClient);
    createEntity(E_SPACE_SHIP_SEMI_DIAGONAL_DOWN, bossX, posY, addEntity, sendMessageToAllClient);
    createEntity(E_SPACE_SHIP_DIAGONAL_UP, bossX, posY, addEntity, sendMessageToAllClient);
    createEntity(E_SPACE_SHIP_DIAGONAL_DOWN, bossX, posY, addEntity, sendMessageToAllClient);
}

void RType::AttackPatterns::spawnBabyOctopus(std::shared_ptr<RType::Entity> boss, std::function<std::shared_ptr<Entity>()> addEntity, std::function<void(const std::basic_string<unsigned char> &message)> sendMessageToAllClient)
{
    auto position = boss->getComponent<PositionComponent>();
    auto rect = boss->getComponent<IntRectComponent>();
    auto scale = boss->getComponent<ScaleComponent>();

    if (!position || !rect || !scale)
        return;

    int bossX = position->getPositionX();
    int bossY = position->getPositionY();
    int bossHeight = rect->getIntRectHeight() * scale->getScaleY();
    int posY = bossY + (bossHeight / 2.);

    createEntity(E_BABY_OCTOPUS, bossX - 50, posY, addEntity, sendMessageToAllClient);

    for (int i = 75; i < 400; i += 75) {
        createEntity(E_BABY_OCTOPUS, bossX - 50 + i, posY - i, addEntity, sendMessageToAllClient);
        createEntity(E_BABY_OCTOPUS, bossX - 50 + i, posY + i, addEntity, sendMessageToAllClient);
    }
}

void RType::AttackPatterns::spawnKamikazeOctopus(std::shared_ptr<RType::Entity> boss, std::function<std::shared_ptr<Entity>()> addEntity, std::function<void(const std::basic_string<unsigned char> &message)> sendMessageToAllClient)
{
    auto position = boss->getComponent<PositionComponent>();
    auto rect = boss->getComponent<IntRectComponent>();
    auto scale = boss->getComponent<ScaleComponent>();

    if (!position || !rect || !scale)
        return;

    int bossX = position->getPositionX();
    int bossY = position->getPositionY();
    int bossHeight = rect->getIntRectHeight() * scale->getScaleY();
    int posY = bossY + (bossHeight / 2.);

    createEntity(E_BABY_OCTOPUS, bossX, posY, addEntity, sendMessageToAllClient);

    for (int i = 75; i < 400; i += 75) {
        createEntity(E_BABY_OCTOPUS, bossX - i, posY - i, addEntity, sendMessageToAllClient);
        createEntity(E_BABY_OCTOPUS, bossX - i, posY + i, addEntity, sendMessageToAllClient);
    }
}

void RType::AttackPatterns::spawnWallStaticBomb(std::shared_ptr<RType::Entity> boss, std::function<std::shared_ptr<Entity>()> addEntity, std::function<void(const std::basic_string<unsigned char> &message)> sendMessageToAllClient)
{
    auto position = boss->getComponent<PositionComponent>();
    auto rect = boss->getComponent<IntRectComponent>();
    auto scale = boss->getComponent<ScaleComponent>();

    if (!position || !rect || !scale)
        return;

    int randomNumber = std::rand() % 9;

    for (int posY = 0; posY < 9; posY++) {
        if (randomNumber == posY)
            continue;
        createEntity(E_STATIC_BOMB, 1920, posY * 120, addEntity, sendMessageToAllClient);
    }
}

void RType::AttackPatterns::spawnWallZigZagBomb(std::shared_ptr<RType::Entity> boss, std::function<std::shared_ptr<Entity>()> addEntity, std::function<void(const std::basic_string<unsigned char> &message)> sendMessageToAllClient)
{
    auto position = boss->getComponent<PositionComponent>();
    auto rect = boss->getComponent<IntRectComponent>();
    auto scale = boss->getComponent<ScaleComponent>();

    if (!position || !rect || !scale)
        return;

    for (int posY = 0; posY < 8; posY++) {
        if (std::rand() % 2)
            createEntity(E_ZIGZAG_BOMB, 1920, posY * 120, addEntity, sendMessageToAllClient);
        else
            createEntity(E_ZIGZAG_BOMB_REVERSE, 1920, posY * 120, addEntity, sendMessageToAllClient);

    }
}

void RType::AttackPatterns::createEntity(const RType::EntityType &type, const int &posX, const int &posY, std::function<std::shared_ptr<Entity>()> addEntity, std::function<void(const std::basic_string<unsigned char> &message)> sendMessageToAllClient)
{
    Json::Reader reader;
    Json::Value entityInfo;
    std::ifstream file;

    std::shared_ptr<RType::Entity> entity = addEntity();
    std::shared_ptr<RType::Entity> entityToFollow = nullptr;
    std::unordered_map<EntityType, std::string> entityTypeMap;

    entityTypeMap[E_OTHER] = "other";
    entityTypeMap[E_WINDOW] = "window";
    entityTypeMap[E_PLAYER] = "allies";
    entityTypeMap[E_ALLIES] = "allies";
    entityTypeMap[E_SPACE_SHIP_1] = "space_ship_1";
    entityTypeMap[E_SPACE_SHIP_2] = "space_ship_2";
    entityTypeMap[E_SPACE_SHIP_3] = "space_ship_3";
    entityTypeMap[E_OCTOPUS] = "octopus";
    entityTypeMap[E_FLY] = "fly";
    entityTypeMap[E_BABY_FLY] = "baby_fly";
    entityTypeMap[E_FLY_BOSS] = "fly_boss";
    entityTypeMap[E_SPACE_SHIP_BOSS] = "space_ship_boss";
    entityTypeMap[E_OCTOPUS_BOSS] = "octopus_boss";
    entityTypeMap[E_BOMBER_BOSS] = "bomber_boss";
    entityTypeMap[E_BABY_OCTOPUS] = "baby_octopus";
    entityTypeMap[E_SPACE_SHIP_4] = "space_ship_4";
    entityTypeMap[E_BUTTON] = "button";
    entityTypeMap[E_LAYER] = "layer";
    entityTypeMap[E_SHIELD] = "shield";
    entityTypeMap[E_ITEM_WEAPON] = "item_weapon";
    entityTypeMap[E_ITEM_SHIELD] = "item_shield";
    entityTypeMap[E_ITEM_HEAL] = "item_heal";
    entityTypeMap[E_BULLET] = "bullet_1";
    entityTypeMap[E_BULLET_2] = "bullet_2";
    entityTypeMap[E_BULLET_3] = "bullet_3";
    entityTypeMap[E_BULLET_4] = "bullet_4";
    entityTypeMap[E_SPACE_SHIP_BULLET] = "space_ship_bullet";
    entityTypeMap[E_SPACE_SHIP_SEMI_DIAGONAL_UP] = "space_ship_semi_diagonal_up_bullet";
    entityTypeMap[E_SPACE_SHIP_SEMI_DIAGONAL_DOWN] = "space_ship_semi_diagonal_down_bullet";
    entityTypeMap[E_SPACE_SHIP_DIAGONAL_UP] = "space_ship_diagonal_up_bullet";
    entityTypeMap[E_SPACE_SHIP_DIAGONAL_DOWN] = "space_ship_diagonal_down_bullet";
    entityTypeMap[E_ENNEMY_BULLET] = "ennemy_bullet";
    entityTypeMap[E_BULLET_EFFECT] = "bullet_effect";
    entityTypeMap[E_HIT_EFFECT] = "hit_effect";
    entityTypeMap[E_EXPLOSION_EFFECT] = "explosion_effect";
    entityTypeMap[E_TEXT] = "text";
    entityTypeMap[E_ITEM_FORCEPOD] = "item_forcepod";
    entityTypeMap[E_FORCEPOD] = "forcepod";
    entityTypeMap[E_FORCEPOD_BULLET] = "forcepod_bullet";
    entityTypeMap[E_FORCEPOD_2] = "forcepod2";
    entityTypeMap[E_FORCEPOD_3] = "forcepod3";
    entityTypeMap[E_BULLET_LASER] = "laser";
    entityTypeMap[E_BULLET_LASER_2] = "laser2";
    entityTypeMap[E_BULLET_LASER_3] = "laser3";
    entityTypeMap[E_BULLET_LASER_4] = "laser4";
    entityTypeMap[E_CHARGING_EFFECT] = "charging_effect";
    entityTypeMap[E_FORCEPOD_BULLET_2] = "forcepod_bullet2";
    entityTypeMap[E_FORCEPOD_BULLET_3] = "forcepod_bullet3";
    entityTypeMap[E_STING] = "sting";
    entityTypeMap[E_STATIC_BOMB] = "static_bomb";
    entityTypeMap[E_ZIGZAG_BOMB] = "zigzag_bomb";
    entityTypeMap[E_ZIGZAG_BOMB_REVERSE] = "zigzag_bomb_reverse";


    std::string filepath("./config/entities/" + entityTypeMap[type] + ".json");

    file.open(filepath);
    if (!file.is_open() || !reader.parse(file, entityInfo)) {
        std::cerr << "Error while reading or parsing the json: " << filepath << std::endl;
        return;
    }

    entity->PUSH_TYPE_E(type);
    auto position = entity->PUSH_POS_E(posX, posY - 20);
    auto scale = entity->PUSH_SCALE_E(entityInfo["scale"]["x"].asFloat(),
                                                 entityInfo["scale"]["y"].asFloat());
    auto intRect = entity->PUSH_RECT_E(entityInfo["rect"]["x"].asInt(),
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

    if (entityInfo["score"].asBool() == true) {
        entity->pushComponent(std::make_shared<ScoreComponent>(entityInfo["score"].asInt()));
    }

    if (entityInfo["attack"].isArray()) {
        auto attackComponent = entity->PUSH_ATTACK_E();
        for (const auto &attack : entityInfo["attack"]) {
            if (attack.isString()) {
                attackComponent->pushBackAttacksPatterns(attack.asString());
            }
        }
    }

    file.close();

    if (sendMessageToAllClient)
        sendMessageToAllClient(Encoder::newEntity(type, entity->getId(), position->getPositionX(), position->getPositionY()));
}

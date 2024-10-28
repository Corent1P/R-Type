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



void RType::AttackPatterns::createEntity(const RType::EntityType &type, const int &posX, const int &posY, std::function<std::shared_ptr<Entity>()> addEntity, std::function<void(const std::basic_string<unsigned char> &message)> sendMessageToAllClient)
{
    Json::Reader reader;
    Json::Value entityInfo;
    std::ifstream file;

    std::shared_ptr<RType::Entity> entity = addEntity();
    std::shared_ptr<RType::Entity> entityToFollow = nullptr;
    std::unordered_map<EntityType, std::string> entityTypeMap;

    entityTypeMap[E_SPACE_SHIP_1] = "small_spaceship";
    entityTypeMap[E_OCTOPUS] = "octopus";
    entityTypeMap[E_FLY] = "fly";
    entityTypeMap[E_BABY_FLY] = "baby_fly";
    entityTypeMap[E_STING] = "sting";

    entityTypeMap[E_BOSS] = "boss";

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
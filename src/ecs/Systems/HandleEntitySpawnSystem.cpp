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

void RType::HandleEntitySpawnSystem::effects(std::vector<std::shared_ptr<RType::Entity>> entities) {
    for (const auto &entity : entities) {
        if (verifyRequiredComponent(entity)) {
            effect(entity);
            continue;
        } else if (entity->getComponent<EntityTypeComponent>() != nullptr && entity->getComponent<EntityTypeComponent>()->getEntityType() == RType::E_PLAYER) {
            if (entity->getComponent<PowerUpComponent>() != nullptr && entity->getComponent<PowerUpComponent>()->getPowerUps(RType::SHIELD) == true) {
                entity->getComponent<PowerUpComponent>()->setPowerUps(RType::SHIELD, false);
                createShied(entity);
                break;
            }
        }
    }
}
void RType::HandleEntitySpawnSystem::effect(std::shared_ptr<RType::Entity> entity)
{
    if (entity->getComponent<RType::ClockComponent>()->getClock(RType::SPAWN_CLOCK).getElapsedTime().asSeconds() > 1) {
        //createMobFly(1920, _y_spawn);
        createMobOctopus(1920, _y_spawn + 100);
        //createMobSpaceShip(1920, _y_spawn - 100);
        createItemWeapon(1920, _y_spawn);
        createItemShield(1920, _y_spawn + 100);
        entity->getComponent<RType::ClockComponent>()->getClock(RType::SPAWN_CLOCK).restart();
        if (_y_spawn > 100)
            _y_spawn -= 100;
        else
            _y_spawn = 700;
    }
}

bool RType::HandleEntitySpawnSystem::verifyRequiredComponent(std::shared_ptr<RType::Entity> entity)
{
    if (GET_ENTITY_TYPE(entity) == RType::E_WINDOW && entity->getComponent<RType::ClockComponent>() != nullptr)
        return true;
    return false;
}

void RType::HandleEntitySpawnSystem::createMobOctopus(int posX, int posY)
{
    std::shared_ptr<RType::Entity> mob = _addEntity();

    mob->pushComponent(std::make_shared<RType::EntityTypeComponent>(RType::E_OCTOPUS));
    mob->pushComponent(std::make_shared<RType::HealthComponent>(3));
    mob->pushComponent(std::make_shared<RType::DamageComponent>(2));
    auto position = mob->pushComponent(std::make_shared<RType::PositionComponent>(posX, posY));
    mob->pushComponent(std::make_shared<RType::ScaleComponent>(2.0, 2.0));
    mob->pushComponent(std::make_shared<RType::IntRectComponent>(0, 0, 41, 46));
    mob->pushComponent(std::make_shared<RType::DirectionPatternComponent>(UP_N_DOWN_LEFT));
    mob->pushComponent(std::make_shared<VelocityComponent>(SERVER_SPEED(OCTOPUS_SPEED)));
    mob->pushComponent(std::make_shared<ClockComponent>());
    _sendToAllClient(Encoder::newEntity(E_OCTOPUS, mob->getId(), position->getPositionX(), position->getPositionY()));
}

void RType::HandleEntitySpawnSystem::createMobFly(int posX, int posY)
{
    std::shared_ptr<RType::Entity> mob = _addEntity();

    mob->pushComponent(std::make_shared<RType::EntityTypeComponent>(RType::E_FLY));
    mob->pushComponent(std::make_shared<RType::HealthComponent>(5));
    mob->pushComponent(std::make_shared<RType::DamageComponent>(2));
    auto position = mob->pushComponent(std::make_shared<RType::PositionComponent>(posX, posY));
    mob->pushComponent(std::make_shared<RType::ScaleComponent>(2.0, 2.0));
    mob->pushComponent(std::make_shared<RType::IntRectComponent>(0, 0, 65, 74));
    mob->pushComponent(std::make_shared<RType::DirectionPatternComponent>(UP_N_DOWN_LEFT));
    mob->pushComponent(std::make_shared<VelocityComponent>(SERVER_SPEED(FLY_SPEED)));
    mob->pushComponent(std::make_shared<ClockComponent>());
    _sendToAllClient(Encoder::newEntity(E_FLY, mob->getId(), position->getPositionX(), position->getPositionY()));
}

void RType::HandleEntitySpawnSystem::createMobSpaceShip(int posX, int posY)
{
    std::shared_ptr<RType::Entity> mob = _addEntity();

    mob->pushComponent(std::make_shared<RType::EntityTypeComponent>(RType::E_SMALL_SPACESHIP));
    mob->pushComponent(std::make_shared<RType::HealthComponent>(2));
    mob->pushComponent(std::make_shared<RType::DamageComponent>(2));
    auto position = mob->pushComponent(std::make_shared<RType::PositionComponent>(posX, posY));
    mob->pushComponent(std::make_shared<RType::ScaleComponent>(2.0, 2.0));
    mob->pushComponent(std::make_shared<RType::IntRectComponent>(0, 0, 29, 29));
    mob->pushComponent(std::make_shared<RType::DirectionPatternComponent>(STRAIGHT_LEFT));
    mob->pushComponent(std::make_shared<VelocityComponent>(SERVER_SPEED(SPACESHIP_SPEED)));
    mob->pushComponent(std::make_shared<ClockComponent>());
    _sendToAllClient(Encoder::newEntity(E_SMALL_SPACESHIP, mob->getId(), position->getPositionX(), position->getPositionY()));
}

void RType::HandleEntitySpawnSystem::createItemWeapon(int x, int y)
{
    std::cout << "create item with pos " << x << ":" << y << std::endl;
    std::shared_ptr<RType::Entity> item = _addEntity();

    item->pushComponent(std::make_shared<RType::EntityTypeComponent>(RType::E_ITEM_WEAPON));
    auto position = item->pushComponent(std::make_shared<RType::PositionComponent>(x, y));
    item->pushComponent(std::make_shared<RType::ScaleComponent>(1.0, 1.0));
    item->pushComponent(std::make_shared<RType::IntRectComponent>(0, 0, 32, 32));
    item->pushComponent(std::make_shared<RType::DirectionPatternComponent>(STRAIGHT_LEFT));
    item->pushComponent(std::make_shared<VelocityComponent>(SERVER_SPEED(SPACESHIP_SPEED)));
    item->pushComponent(std::make_shared<ClockComponent>());
    _sendToAllClient(Encoder::newEntity(E_ITEM_WEAPON, item->getId(), position->getPositionX(), position->getPositionY()));
}


void RType::HandleEntitySpawnSystem::createItemShield(int x, int y)
{
    std::cout << "create item with pos " << x << ":" << y << std::endl;
    std::shared_ptr<RType::Entity> item = _addEntity();

    item->pushComponent(std::make_shared<RType::EntityTypeComponent>(RType::E_ITEM_SHIELD));
    auto position = item->pushComponent(std::make_shared<RType::PositionComponent>(x, y));
    item->pushComponent(std::make_shared<RType::ScaleComponent>(1.0, 1.0));
    item->pushComponent(std::make_shared<RType::IntRectComponent>(0, 0, 32, 32));
    item->pushComponent(std::make_shared<RType::DirectionPatternComponent>(STRAIGHT_LEFT));
    item->pushComponent(std::make_shared<VelocityComponent>(SERVER_SPEED(SPACESHIP_SPEED)));
    item->pushComponent(std::make_shared<ClockComponent>());
    _sendToAllClient(Encoder::newEntity(E_ITEM_SHIELD, item->getId(), position->getPositionX(), position->getPositionY()));
}

void RType::HandleEntitySpawnSystem::createShied(std::shared_ptr<RType::Entity> entity) {
    std::cout << "create a new shield entity" << std::endl;
    std::shared_ptr<RType::Entity> shield = _addEntity();
    shield->pushComponent(std::make_shared<RType::EntityTypeComponent>(RType::E_SHIELD));
    shield->pushComponent(std::make_shared<RType::HealthComponent>(4));
    auto position = shield->pushComponent(std::make_shared<RType::PositionComponent>(entity->getComponent<RType::PositionComponent>()->getPositionX() - ((entity->getComponent<RType::IntRectComponent>()->getIntRectWidth() / 2) * entity->getComponent<ScaleComponent>()->getScaleX()), entity->getComponent<RType::PositionComponent>()->getPositionY() - ((entity->getComponent<RType::IntRectComponent>()->getIntRectHeight() / 2) * entity->getComponent<ScaleComponent>()->getScaleY())));
    shield->pushComponent(std::make_shared<RType::ScaleComponent>(3.0, 3.0));
    shield->pushComponent(std::make_shared<RType::IntRectComponent>(0, 0, 32, 32));
    shield->pushComponent(std::make_shared<RType::DirectionPatternComponent>(FOLLOW_PLAYER));
    shield->pushComponent(std::make_shared<VelocityComponent>(SERVER_SPEED(10)));
    shield->pushComponent(std::make_shared<ClockComponent>());
    _sendToAllClient(Encoder::newEntity(E_SHIELD, shield->getId(), position->getPositionX(), position->getPositionY()));
}
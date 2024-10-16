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
    if (entity->getComponent<RType::ClockComponent>()->getClock(RType::SPAWN_CLOCK).getElapsedTime().asSeconds() > 1) {
        createMobFly(1920, _y_spawn);
        createMobOctopus(1920, _y_spawn + 100);
        createMobSpaceShip(1920, _y_spawn - 100);
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

void RType::HandleEntitySpawnSystem::createMobOctopus(int posX, int posY)
{
    std::shared_ptr<RType::Entity> mob = _addEntity();

    mob->pushComponent(std::make_shared<RType::EntityTypeComponent>(RType::E_OCTOPUS));
    mob->pushComponent(std::make_shared<RType::HealthComponent>(3));
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
    auto position = mob->pushComponent(std::make_shared<RType::PositionComponent>(posX, posY));
    mob->pushComponent(std::make_shared<RType::ScaleComponent>(2.0, 2.0));
    mob->pushComponent(std::make_shared<RType::IntRectComponent>(0, 0, 29, 29));
    mob->pushComponent(std::make_shared<RType::DirectionPatternComponent>(STRAIGHT_LEFT));
    mob->pushComponent(std::make_shared<VelocityComponent>(SERVER_SPEED(SPACESHIP_SPEED)));
    mob->pushComponent(std::make_shared<ClockComponent>());
    _sendToAllClient(Encoder::newEntity(E_SMALL_SPACESHIP, mob->getId(), position->getPositionX(), position->getPositionY()));
}

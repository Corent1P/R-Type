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
        createEntity(2000, _y_spawn);
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

void RType::HandleEntitySpawnSystem::createEntity(int x, int y)
{
    std::shared_ptr<RType::Entity> mob = _addEntity();

    mob->pushComponent(std::make_shared<RType::EntityTypeComponent>(RType::E_MOB));
    std::shared_ptr<RType::PositionComponent> position = mob->pushComponent(std::make_shared<RType::PositionComponent>(x, y));
    mob->pushComponent(std::make_shared<RType::IntRectComponent>(0, 0, 29, 29));
    mob->pushComponent(std::make_shared<RType::HealthComponent>(25));
    mob->pushComponent(std::make_shared<RType::ClockComponent>());
    mob->pushComponent(std::make_shared<RType::VelocityComponent>(3));

    mob->pushComponent(std::make_shared<RType::DirectionPatternComponent>(STRAIGHT_LEFT));
    _sendToAllClient(Encoder::newEntity(E_MOB, mob->getId(), position->getPositionX(), position->getPositionY()));
}

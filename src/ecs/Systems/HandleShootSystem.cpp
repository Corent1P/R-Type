/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** handle entity shooting methods
*/

#include "HandleShootSystem.hpp"

RType::HandleShootSystem::HandleShootSystem(std::function<std::shared_ptr<Entity>()> addEntity, std::function<void(std::shared_ptr<Entity>)> deleteEntity, std::function<void(const std::basic_string<unsigned char> &message)> sendMessageToServer, std::function<void(const std::basic_string<unsigned char> &message)> sendMessageToAllClient):
    ASystem(S_SHOOT, addEntity, deleteEntity), _sendMessageToServer(sendMessageToServer), _sendMessageToAllClient(sendMessageToAllClient)
{
}

RType::HandleShootSystem::~HandleShootSystem()
{
}

void RType::HandleShootSystem::effects(std::vector<std::shared_ptr<RType::Entity>> entities) {
    for (const auto &entity: entities) {
        if (verifyRequiredComponent(entity) && entity->getComponent<ActionComponent>()->getActions(RType::SHOOTING) == true) {
            if (entity->getComponent<EntityTypeComponent>()->getEntityType() == E_PLAYER && _sendMessageToServer) {
                entity->getComponent<RType::ActionComponent>()->setActions(RType::SHOOTING, false);
                _sendMessageToServer(Encoder::actionPlayer(true, false, false, false));
            } else if (EntityTypeComponent::isMob(entity->getComponent<EntityTypeComponent>()->getEntityType()) && _sendMessageToAllClient
                && entity->GET_CLOCK && entity->getComponent<ShootIntervalComponent>()
                && entity->GET_SHOOTING_CLOCK.getElapsedTime().asSeconds() > entity->getComponent<ShootIntervalComponent>()->getShootInterval()) {
                createEnnemyBullet(entity);
                entity->GET_SHOOTING_CLOCK.restart();
            } else if ((entity->getComponent<EntityTypeComponent>()->getEntityType() == E_FORCEPOD || entity->getComponent<EntityTypeComponent>()->getEntityType() == E_FORCEPOD_2) && _sendMessageToAllClient
                && entity->GET_CLOCK && entity->getComponent<ShootIntervalComponent>()
                && entity->GET_SHOOTING_CLOCK.getElapsedTime().asSeconds() > entity->getComponent<ShootIntervalComponent>()->getShootInterval()) {
                createForcePodBullet(entity);
                entity->GET_SHOOTING_CLOCK.restart();
            }
        }
        if (entity->getComponent<RType::ClockComponent>() != nullptr
        && entity->getComponent<RType::EntityTypeComponent>()->getEntityType() == RType::E_BULLET_EFFECT
        && entity->getComponent<RType::ClockComponent>()->getClock(SHOOTING_EFFECT).getElapsedTime().asSeconds() >= 0.05) {
            _deleteEntity(entity);
        }
    }
}

void RType::HandleShootSystem::effect(std::shared_ptr<RType::Entity> entity)
{
    (void) entity;
}

bool RType::HandleShootSystem::verifyRequiredComponent(std::shared_ptr<RType::Entity> entity)
{
    if (entity->getComponent<RType::EntityTypeComponent>() == nullptr
    || entity->getComponent<RType::ActionComponent>() == nullptr) {
        return false;
    }
    return (true);
}

void RType::HandleShootSystem::createEnnemyBullet(const std::shared_ptr<RType::Entity> &entity)
{
    std::shared_ptr<RType::Entity> bullet = _addEntity();

    bullet->pushComponent(std::make_shared<RType::EntityTypeComponent>(RType::E_ENNEMY_BULLET));

    float x = entity->getComponent<PositionComponent>()->getPositions().x;
    float y = entity->getComponent<PositionComponent>()->getPositions().y + ((entity->getComponent<IntRectComponent>()->getIntRectHeight() * entity->getComponent<ScaleComponent>()->getScaleY()) / 2.);

    std::shared_ptr<RType::PositionComponent> position = bullet->pushComponent(std::make_shared<RType::PositionComponent>(x, y));
    bullet->pushComponent(std::make_shared<RType::DirectionPatternComponent>(RType::STRAIGHT_LEFT));
    bullet->pushComponent(std::make_shared<RType::IntRectComponent>(0, 0, 19, 6));
    bullet->pushComponent(std::make_shared<RType::ScaleComponent>(2.0, 2.0));
    bullet->pushComponent(std::make_shared<RType::VelocityComponent>(21));
    bullet->pushComponent(std::make_shared<RType::ClockComponent>());
    bullet->pushComponent(std::make_shared<RType::MenuComponent>(GAME));
    bullet->pushComponent(std::make_shared<RType::DamageComponent>(1));

    _sendMessageToAllClient(Encoder::newEntity(E_ENNEMY_BULLET, bullet->getId(), position->getPositionX(), position->getPositionY()));
}

void RType::HandleShootSystem::createForcePodBullet(const std::shared_ptr<RType::Entity> &entity)
{
    std::shared_ptr<RType::Entity> bullet = _addEntity();

    bullet->pushComponent(std::make_shared<RType::EntityTypeComponent>(RType::E_FORCEPOD_BULLET));

    float x = entity->getComponent<PositionComponent>()->getPositions().x + (entity->getComponent<IntRectComponent>()->getIntRectWidth() * entity->getComponent<ScaleComponent>()->getScaleX());
    float y = entity->getComponent<PositionComponent>()->getPositions().y + ((entity->getComponent<IntRectComponent>()->getIntRectHeight() * entity->getComponent<ScaleComponent>()->getScaleY()) / 2.) - 5;

    std::shared_ptr<RType::PositionComponent> position = bullet->pushComponent(std::make_shared<RType::PositionComponent>(x, y));
    bullet->pushComponent(std::make_shared<RType::DirectionPatternComponent>(RType::STRAIGHT_RIGHT));
    bullet->pushComponent(std::make_shared<RType::IntRectComponent>(0, 0, 19, 6));
    bullet->pushComponent(std::make_shared<RType::ScaleComponent>(2.0, 2.0));
    bullet->pushComponent(std::make_shared<RType::VelocityComponent>(21));
    bullet->pushComponent(std::make_shared<RType::ClockComponent>());
    bullet->pushComponent(std::make_shared<RType::MenuComponent>(GAME));
    bullet->pushComponent(std::make_shared<RType::DamageComponent>(1));

    _sendMessageToAllClient(Encoder::newEntity(E_FORCEPOD_BULLET, bullet->getId(), position->getPositionX(), position->getPositionY()));
}

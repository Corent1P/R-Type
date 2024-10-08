/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** handle entity Colision methods
*/

#include "HandleColisionSystem.hpp"

RType::HandleColisionSystem::HandleColisionSystem(std::function<std::shared_ptr<Entity>()> addEntity, std::function<void(std::shared_ptr<Entity>)> deleteEntity):
    ASystem(S_COLISION, addEntity, deleteEntity)
{
}

RType::HandleColisionSystem::~HandleColisionSystem()
{
}

void RType::HandleColisionSystem::effects(std::vector<std::shared_ptr<RType::Entity>> entities) {
    for (const auto &entity: entities) {
        if (verifyRequiredComponent(entity)) {
            auto position1 = entity->getComponent<PositionComponent>()->getPositions();
            auto width1 = entity->getComponent<IntRectComponent>()->getIntRectWidth();
            auto height1 = entity->getComponent<IntRectComponent>()->getIntRectWidth();
            for (const auto &otherEntity: entities)
                if (entity->getId() != otherEntity->getId() && verifyRequiredComponent(otherEntity)) {
                    auto position2 = otherEntity->getComponent<PositionComponent>()->getPositions();
                    auto width2 = otherEntity->getComponent<IntRectComponent>()->getIntRectWidth();
                    auto height2 = otherEntity->getComponent<IntRectComponent>()->getIntRectWidth();
                    if (position1.x + width1 > position2.x
                    && position1.x < position2.x + width2
                    && position1.y + height1 > position2.y
                    && position1.y < position2.y + height2) {
                        if (entity->getComponent<RType::EntityTypeComponent>()->getEntityType() == RType::E_PLAYER && otherEntity->getComponent<RType::EntityTypeComponent>()->getEntityType() == RType::E_BULLET)
                            std::cout << "Player intersect bullet" << std::endl;
                        if (entity->getComponent<RType::EntityTypeComponent>()->getEntityType() == RType::E_BULLET && otherEntity->getComponent<RType::EntityTypeComponent>()->getEntityType() == RType::E_PLAYER)
                            std::cout << "Bullet intersect player" << std::endl;
                        if (entity->getComponent<RType::EntityTypeComponent>()->getEntityType() == RType::E_PLAYER && otherEntity->getComponent<RType::EntityTypeComponent>()->getEntityType() == RType::E_MOB)
                            std::cout << "Player intersect mob" << std::endl;
                        if (entity->getComponent<RType::EntityTypeComponent>()->getEntityType() == RType::E_MOB && otherEntity->getComponent<RType::EntityTypeComponent>()->getEntityType() == RType::E_PLAYER)
                            std::cout << "Mob intersect Player" << std::endl;
                        if (entity->getComponent<RType::EntityTypeComponent>()->getEntityType() == RType::E_BULLET && otherEntity->getComponent<RType::EntityTypeComponent>()->getEntityType() == RType::E_MOB)
                            std::cout << "Bullet intersect mob" << std::endl;
                        if (entity->getComponent<RType::EntityTypeComponent>()->getEntityType() == RType::E_MOB && otherEntity->getComponent<RType::EntityTypeComponent>()->getEntityType() == RType::E_BULLET)
                            std::cout << "Mob intersect Bullet" << std::endl;
                    }
                }
        }
    }
}

void RType::HandleColisionSystem::effect(std::shared_ptr<RType::Entity> entity)
{
    (void) entity;
}

bool RType::HandleColisionSystem::verifyRequiredComponent(std::shared_ptr<RType::Entity> entity)
{
    if (entity->getComponent<RType::PositionComponent>() == nullptr
    || entity->getComponent<RType::IntRectComponent>() == nullptr
    || entity->getComponent<RType::EntityTypeComponent>()->getEntityType() == RType::E_LAYER) {
        return false;
    }
    return (true);
}
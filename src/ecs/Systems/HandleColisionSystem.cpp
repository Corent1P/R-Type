/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** handle entity Colision methods
*/

#include "HandleColisionSystem.hpp"

RType::HandleColisionSystem::HandleColisionSystem(std::function<std::shared_ptr<Entity>()> addEntity, std::function<void(std::shared_ptr<Entity>)> deleteEntity):
    ASystem(COLISION, addEntity, deleteEntity)
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
                if (entity->getId() != otherEntity->getId() && otherEntity->getComponent<RType::PositionComponent>() != nullptr && otherEntity->getComponent<RType::EntityTypeComponent>()->getEntityType() != RType::LAYER) {
                    auto position2 = otherEntity->getComponent<PositionComponent>()->getPositions();
                    auto width2 = otherEntity->getComponent<IntRectComponent>()->getIntRectWidth();
                    auto height2 = otherEntity->getComponent<IntRectComponent>()->getIntRectWidth();
                    if (position1.x + width1 > position2.x
                    && position1.x < position2.x + width2
                    && position1.y + height1 > position2.y
                    && position1.y < position2.y + height2) {
                        std::cout << position1.x << " " << position1.y << " " << width1 << " " << height1 << std::endl;
                        std::cout << position2.x << " " << position2.y << " " << width2 << " " << height2 << std::endl;

                        std::cout << "intersection" << *entity << *otherEntity <<std::endl;
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
    if (entity->getComponent<RType::DirectionComponent>() == nullptr
    || entity->getComponent<RType::ActionComponent>() == nullptr
    || entity->getComponent<RType::SpriteComponent>() == nullptr)
    {
        return false;
    }
    return (true);
}
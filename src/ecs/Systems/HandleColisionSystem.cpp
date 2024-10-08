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
            auto playerGlobalBounds = entity->getComponent<SpriteComponent>()->getSprite()->getGlobalBounds();
            for (const auto &otherEntity: entities)
                if (entity->getId() != otherEntity->getId() && otherEntity->getComponent<RType::SpriteComponent>() != nullptr && otherEntity->getComponent<RType::EntityTypeComponent>()->getEntityType() != RType::LAYER) {
                    auto otherGlobalBounds = otherEntity->getComponent<SpriteComponent>()->getSprite()->getGlobalBounds();
                    if (playerGlobalBounds.intersects(otherGlobalBounds)) {
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
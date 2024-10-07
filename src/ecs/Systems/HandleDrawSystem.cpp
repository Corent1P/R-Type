/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** handle draw system methods
*/

#include "HandleDrawSystem.hpp"

RType::HandleDrawSystem::HandleDrawSystem(std::function<std::shared_ptr<Entity>()> addEntity, std::function<void(std::shared_ptr<Entity>)> deleteEntity):
    ASystem(S_DRAW, addEntity, deleteEntity)
{
}

RType::HandleDrawSystem::~HandleDrawSystem()
{
}


void RType::HandleDrawSystem::effects(std::vector<std::shared_ptr<RType::Entity>> entities)
{
    for (const auto &w: entities) {
        if (GET_WINDOW_FOR_DRAW != nullptr) {
            GET_WINDOW_FOR_DRAW->getWindow()->clear();
            for (const auto &e: entities) {
                // std::cout << "HandleDrawSystem " << e->getId() << std::endl;
                if (verifyRequiredComponent(e)) {
                    GET_WINDOW_FOR_DRAW->getWindow()->draw(*(e->getComponent<RType::SpriteComponent>()->getSprite()));
                }
            }
            GET_WINDOW_FOR_DRAW->getWindow()->display();
            return;
        }
    }
}

void RType::HandleDrawSystem::effect(std::shared_ptr<RType::Entity> entity)
{
    (void) entity;
}

bool RType::HandleDrawSystem::verifyRequiredComponent(std::shared_ptr<RType::Entity> entity)
{
    if (entity->getComponent<RType::PositionComponent>() == nullptr
    ||entity->getComponent<RType::SpriteComponent>() == nullptr) {
        return false;
    }
    if (entity->getComponent<RType::EntityTypeComponent>()->getEntityType() == RType::E_LAYER
        && entity->getComponent<RType::LevelComponent>()->getLevel() != 1)
        return false;

    return (true);
}
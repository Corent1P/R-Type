/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** handle entity shooting methods
*/

#include "HandleShootSystem.hpp"

RType::HandleShootSystem::HandleShootSystem():
    ASystem(MOVE)
{
}

RType::HandleShootSystem::~HandleShootSystem()
{
}

void RType::HandleShootSystem::effects(std::vector<std::shared_ptr<RType::Entity>> entities) {
    for (const auto &entity: entities) {
        if (verifyRequiredComponent(entity)) {
            if (entity->getComponent<ActionComponent>()->getAction() == RType::SHOOTING) {
                // create a new entity called shot asign a spirte, direction, position to it.
            }
        }
    }
}

void RType::HandleShootSystem::effect(std::shared_ptr<RType::Entity> entity)
{
    (void) entity;
}

bool RType::HandleShootSystem::verifyRequiredComponent(std::shared_ptr<RType::Entity> entity)
{
    if (entity->getComponent<RType::DirectionComponent>() == nullptr || entity->getComponent<RType::ActionComponent>() == nullptr)
    {
        return false;
    }
    return (true);
}
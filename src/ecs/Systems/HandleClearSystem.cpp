/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** system handling direction clear methods
*/

#include "HandleClearSystem.hpp"

RType::HandleClearSystem::HandleClearSystem(std::function<std::shared_ptr<Entity>()> addEntity, std::function<void(std::shared_ptr<Entity>)> deleteEntity):
    ASystem(S_CLEAR, addEntity, deleteEntity)
{
}

RType::HandleClearSystem::~HandleClearSystem()
{
}

void RType::HandleClearSystem::effect(std::shared_ptr<RType::Entity> entity)
{
    entity->getComponent<SFWindowComponent>()->getWindow()->clear();

}

bool RType::HandleClearSystem::verifyRequiredComponent(std::shared_ptr<RType::Entity> entity)
{
    if (entity->getComponent<RType::SFWindowComponent>() == nullptr) {
        return false;
    }
    return (true);
}
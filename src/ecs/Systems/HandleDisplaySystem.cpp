/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** system handling direction pattern methods
*/

#include "HandleDisplaySystem.hpp"

RType::HandleDisplaySystem::HandleDisplaySystem(std::function<std::shared_ptr<Entity>()> addEntity, std::function<void(std::shared_ptr<Entity>)> deleteEntity):
    ASystem(S_DISPLAY, addEntity, deleteEntity)
{
}

RType::HandleDisplaySystem::~HandleDisplaySystem()
{
}

void RType::HandleDisplaySystem::effect(std::shared_ptr<RType::Entity> entity)
{
    entity->getComponent<SFWindowComponent>()->getWindow()->display();
}

bool RType::HandleDisplaySystem::verifyRequiredComponent(std::shared_ptr<RType::Entity> entity)
{
    if (entity->getComponent<RType::SFWindowComponent>() == nullptr) {
        return false;
    }
    return (true);
}
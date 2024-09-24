/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** handle entity movements methods
*/

#include "HandleMoveSystem.hpp"

HandleMoveSystem::HandleMoveSystem()
{
}

HandleMoveSystem::~HandleMoveSystem()
{
}

void HandleMoveSystem::effect(std::vector<std::shared_ptr<RType::Entity>> entities)
{
}

bool HandleMoveSystem::verifyRequiredComponent(std::shared_ptr<RType::Entity> entity)
{

}

RType::SystemType HandleMoveSystem::getType() const
{
    return _type;
}
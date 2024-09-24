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

void HandleMoveSystem::effect(std::shared_ptr<RType::Entity> entity)
{
}

bool HandleMoveSystem::verifyRequiredComponent(std::shared_ptr<RType::Entity> entity)
{

}

RType::SystemType HandleMoveSystem::getType() const
{
    return _type;
}
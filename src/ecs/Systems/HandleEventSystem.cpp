/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** handle event system methods
*/

#include "HandleEventSystem.hpp"

HandleEventSystem::HandleEventSystem()
{
}

HandleEventSystem::~HandleEventSystem()
{
}

void HandleEventSystem::effect(std::shared_ptr<Entity> entities)
{
    for (auto e: entites) {

        if (!verifyRequiredComponent(e)) {
            std::cout << "nothing to do around here" << std::endl;
        } else {
            //.. thing to do with the correct entity
        }
    }
}

bool HandleEventSystem::verifyRequiredComponent(Entity entity)
{
    //check for the correct entity
}

SystemType HandleEventSystem::getType() const
{
    return _type;
}
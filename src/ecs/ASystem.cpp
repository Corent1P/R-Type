/*
** EPITECH PROJECT, 2024
** rType
** File description:
** ASystem
*/

#include "ASystem.hh"

RType::ASystem::ASystem(SystemType type):
    _type(type)
{
}

void RType::ASystem::effects(std::vector<std::shared_ptr<RType::Entity>> entities)
{
    for (const auto &e: entities) {
        if (verifyRequiredComponent(e))
            effect(e);
    }
}

void RType::ASystem::effect(std::shared_ptr<RType::Entity> entity)
{
    (void) entity;
}

bool RType::ASystem::verifyRequiredComponent(std::shared_ptr<RType::Entity> entity)
{
    (void) entity;
    return false;
}

RType::SystemType RType::ASystem::getType() const
{
	return _type;
}

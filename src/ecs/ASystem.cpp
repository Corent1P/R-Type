/*
** EPITECH PROJECT, 2024
** rType
** File description:
** ASystem
*/

#include "ASystem.hh"

RType::ASystem::ASystem(SystemType type, std::function<void(std::shared_ptr<Entity>)> addEntity, std::function<void(std::shared_ptr<Entity>)> deleteEntity):
    _type(type), _addEntity(addEntity), _deleteEntity(deleteEntity)
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

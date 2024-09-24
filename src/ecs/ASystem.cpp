/*
** EPITECH PROJECT, 2024
** rType
** File description:
** ASystem
*/

#include "ASystem.hh"

RType::ASystem::ASystem():
    _type(SystemBasic)
{
}

void RType::ASystem::effect(std::shared_ptr<Entity> entities)
{
     std::cout<< entities << std::endl;
}

bool RType::ASystem::verifyRequiredComponent(Entity entity)
{
    std::cout<< entity<< std::endl;
    return false;
}

RType::SystemType RType::ASystem::getType() const
{
	return _type;
}

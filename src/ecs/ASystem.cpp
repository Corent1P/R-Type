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

void RType::ASystem::effect(std::vector<std::shared_ptr<RType::Entity>> entities)
{
    std::cout << entities.at(1) << std::endl;
}

bool RType::ASystem::verifyRequiredComponent(std::shared_ptr<RType::Entity> entity)
{
    std::cout<< entity<< std::endl;
    return false;
}

RType::SystemType RType::ASystem::getType() const
{
	return _type;
}
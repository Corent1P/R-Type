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

void RType::ASystem::effect()
{
}

bool RType::ASystem::verifyRequiredComponent()
{
    return false;
}

RType::SystemType RType::ASystem::getType() const
{
	return _type;
}

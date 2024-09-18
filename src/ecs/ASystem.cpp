/*
** EPITECH PROJECT, 2024
** rType
** File description:
** ASystem
*/

#include "ASystem.hpp"

ASystem::ASystem():
    _type(SystemBasic)
{
}

void ASystem::effect()
{
}

bool ASystem::verifyRequiredComponent()
{
    return false;
}

bool ASystem::getType() const
{
	return _type;
}

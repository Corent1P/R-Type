/*
** EPITECH PROJECT, 2024
** rType
** File description:
** ASystem
*/

#include "ASystem.hpp"

void ASystem::effect()
{
}

bool ASystem::verifyRequiredComponent()
{
    return false;
}

std::ostream &operator<<(std::ostream &s, const ASystem &system)
{
    (void) system;
    s << "Basic System" << std::endl;
    return s;
}

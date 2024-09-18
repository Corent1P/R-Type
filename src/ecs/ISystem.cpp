/*
** EPITECH PROJECT, 2024
** rType
** File description:
** ISystem
*/

#include "ISystem.hpp"

std::ostream &operator<<(std::ostream &s, const ISystem &system)
{
    s << "System: ";

    switch (system.getType()) {
        case SystemBasic:
            s << "basic";
            break;
        default:
            s << "unknown";
            break;
    }
    s << std::endl;
    return s;
}

/*
** EPITECH PROJECT, 2024
** rType
** File description:
** ISystem
*/

#include "ISystem.hh"

std::ostream &operator<<(std::ostream &s, const RType::ISystem &system)
{
    s << "System: ";

    switch (system.getType()) {
        case RType::BASIC:
            s << "Basic system";
            break;
        case RType::EVENT:
            s << "Event system";
            break;
        case RType::DRAW:
            s << "Draw system";
            break;
        default:
            s << "Unknown system";
            break;
    }
    return s;
}

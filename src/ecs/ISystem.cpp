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
        case RType::SystemBasic:
            s << "basic";
            break;
        case RType::SystemHandleEvent:
            s << "handle event System";
            break;
        default:
            s << "unknown";
            break;
    }
    return s;
}
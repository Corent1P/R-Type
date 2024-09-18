/*
** EPITECH PROJECT, 2024
** rType
** File description:
** IComponent
*/

#include "IComponent.hpp"

std::ostream &operator<<(std::ostream &s, const IComponent &component)
{
    s << "Component: ";

    switch (component.getType()) {
        case ComponentBasic:
            s << "basic";
            break;
        default:
            s << "unknown";
            break;
    }
    return s;
}

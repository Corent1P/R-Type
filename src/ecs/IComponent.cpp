/*
** EPITECH PROJECT, 2024
** rType
** File description:
** IComponent
*/

#include "IComponent.hpp"

std::ostream &operator<<(std::ostream &s, const IComponent &component)
{
    switch (component.getType()) {
        case ComponentBasic:
            s << "Basic Component";
            break;
        case ComponentPosition:
            s << component.getOutput();
            break;
        case ComponentHealth:
            s << component.getOutput();
            break;
        default:
            s << "Unknown Component";
            break;
    }
    return s;
}

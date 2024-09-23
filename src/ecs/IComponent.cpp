/*
** EPITECH PROJECT, 2024
** rType
** File description:
** IComponent
*/

#include "IComponent.hpp"

std::ostream &operator<<(std::ostream &s, const RType::IComponent &component)
{
    switch (component.getType()) {
        case RType::ComponentBasic:
            s << "Basic Component";
            break;
        case RType::ComponentPosition:
            s << component.getOutput();
            break;
        case RType::ComponentHealth:
            s << component.getOutput();
            break;
        default:
            s << "Unknown Component";
            break;
    }
    return s;
}

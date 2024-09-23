/*
** EPITECH PROJECT, 2024
** rType
** File description:
** IComponent
*/

#include "IComponent.hh"

std::ostream &operator<<(std::ostream &s, const RType::IComponent &component)
{
    s << component.getOutput();
    return s;
}

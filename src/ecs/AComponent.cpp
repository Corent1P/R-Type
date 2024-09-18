/*
** EPITECH PROJECT, 2024
** rType
** File description:
** AComponent
*/

#include "AComponent.hpp"

std::ostream &operator<<(std::ostream &s, const IComponent &component)
{
    (void) component;
    s << "basic";
    return s;
}

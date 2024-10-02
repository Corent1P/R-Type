/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Clock component methods
*/

#include "ClockComponent.hh"


sf::Clock  &RType::ClockComponent::getClock()
{
    return(_clock);
}

std::string RType::ClockComponent::getOutput() const
{
    std::string output("Clock Component");
    return (output);
}

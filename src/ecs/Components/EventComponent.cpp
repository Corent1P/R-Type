/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** sfml event component
*/

#include "EventComponent.hh"

sf::Event& RType::EventComponent::getEvent()
{
    return (_event);
}

std::string RType::EventComponent::getOutput() const
{
    std::string output("Event Component");
    return (output);
}

/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** sfml event component
*/

#include "EventComponent.hh"

EventComponent::EventComponent()
{
    setEvent();
}

EventComponent::~EventComponent()
{
}

void EventComponent::setEvent()
{
    sf::Event e;
    e = _event;
}

sf::Event EventComponent::getEvent() const
{
    return (_event);
}
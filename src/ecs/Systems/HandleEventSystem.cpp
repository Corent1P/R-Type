/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** handle event system methods
*/

#include "HandleEventSystem.hpp"
#include ".././Components/SFWindowComponent.hh"
#include ".././Components/EventComponent.hh"
// #include "SFML/Graphics"

HandleEventSystem::HandleEventSystem()
{
    _type = RType::SystemHandleEvent;
}

HandleEventSystem::~HandleEventSystem()
{
}

void HandleEventSystem::effect(std::shared_ptr<RType::Entity> entity)
{
    while (GET_WINDOW->pollEvent(entity->getComponent<RType::EventComponent>()->getEvent())) {
        if (entity->getComponent<RType::EventComponent>()->getEvent().type == sf::Event::Closed) {
            GET_WINDOW->close();
        }
        GET_WINDOW->clear();
        GET_WINDOW->display();
    }
}

bool HandleEventSystem::verifyRequiredComponent(std::shared_ptr<RType::Entity> entity)
{
    if (entity->getComponent<RType::SFWindowComponent>() == nullptr
    ||entity->getComponent<RType::EventComponent>() == nullptr) {
        return false;
    }
    return (true);
}
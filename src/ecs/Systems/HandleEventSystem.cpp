/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** handle event system methods
*/

#include "HandleEventSystem.hpp"

RType::HandleEventSystem::HandleEventSystem():
    ASystem(EVENT)
{
}

RType::HandleEventSystem::~HandleEventSystem()
{
}

void RType::HandleEventSystem::effect(std::shared_ptr<RType::Entity> entity)
{
    while (GET_WINDOW->pollEvent(entity->getComponent<RType::EventComponent>()->getEvent())) {
        if (entity->getComponent<RType::EventComponent>()->getEvent().type == sf::Event::Closed) {
            GET_WINDOW->close();
        }
    }
}

bool RType::HandleEventSystem::verifyRequiredComponent(std::shared_ptr<RType::Entity> entity)
{
    if (entity->getComponent<RType::SFWindowComponent>() == nullptr
    ||entity->getComponent<RType::EventComponent>() == nullptr) {
        return false;
    }
    return (true);
}
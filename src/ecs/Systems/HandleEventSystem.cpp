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
    _type= RType::SystemHandleEvent;
}

HandleEventSystem::~HandleEventSystem()
{
}

void HandleEventSystem::effect(std::vector<std::shared_ptr<RType::Entity>> entities)
{
    for (const auto &e: entities) {
        if (!verifyRequiredComponent(e)) {
            continue;
        } else {
            sf::Event evt;
            while (GET_WINDOW->pollEvent(evt))
            {
                if (evt.type == sf::Event::Closed) {
                    GET_WINDOW->close();
                    GET_WINDOW_SET_ISOPEN->setisOpen(false);
                }
                GET_WINDOW->clear();
                GET_WINDOW->display();
            }
        }
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

RType::SystemType HandleEventSystem::getType() const
{
    return _type;
}
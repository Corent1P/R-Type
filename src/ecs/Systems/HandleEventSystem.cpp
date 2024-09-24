/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** handle event system methods
*/

#include "HandleEventSystem.hpp"
#include ".././Components/SFWindowComponent.hh"
#include ".././Components/EventComponent.hh"

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
            std::cout << "nothing to do around here" << std::endl;
        } else {
            //.. thing to do with the correct entity
            sf::Event evt;
            while (e->getComponent<RType::SFWindowComponent>()->getWindow()->pollEvent(evt))
            {
                if (e->getComponent<RType::EventComponent>()->getEvent().type == sf::Event::Closed)
                    e->getComponent<RType::SFWindowComponent>()->getWindow()->close();
                e->getComponent<RType::SFWindowComponent>()->getWindow()->clear();
                e->getComponent<RType::SFWindowComponent>()->getWindow()->display();
            }
        }
    }
}

bool HandleEventSystem::verifyRequiredComponent(std::shared_ptr<RType::Entity> entity)
{
    //check for the correct entity

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
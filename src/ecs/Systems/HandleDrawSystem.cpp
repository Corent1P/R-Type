/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** handle draw system methods
*/

#include "HandleEventSystem.hpp"
#include ".././Components/SFWindowComponent.hh"
#include ".././Components/EventComponent.hh"
// #include "SFML/Graphics"

HandleDrawSystem::HandleDrawSystem()
{
    _type= RType::SystemHandleEvent;
}

HandleDrawSystem::~HandleDrawSystem()
{
}


void HandleDrawSystem::effects(std::vector<std::shared_ptr<RType::Entity>> entities)
{
    for (const auto &e: entities) {
        if (verifyRequiredComponent(e)) {
            for (const auto &w: entities) {
                if (w->getComponent<RType::SFWindowComponent>() != nullptr) {
                    w->getComponent<RType::SFWindowComponent>()->getWindow().draw(e->getComponent<TextureComponent>().getTexture())
                }
            }
        }
    }
}

void HandleDrawSystem::effect(std::vector<std::shared_ptr<RType::Entity>> entities)
{

    sf::Event evt;
    while (GET_WINDOW->pollEvent(evt))
    {
        if (evt.type == sf::Event::Closed) {
            GET_WINDOW->close();
        }
        GET_WINDOW->clear();
        GET_WINDOW->display();
    }
}

bool HandleDrawSystem::verifyRequiredComponent(std::shared_ptr<RType::Entity> entity)
{
    if (entity->getComponent<RType::PositionComponent>() == nullptr
    ||entity->getComponent<RType::TextureComponent>() == nullptr) {
        return false;
    }
    return (true);
}

RType::SystemType HandleDrawSystem::getType() const
{
    return _type;
}
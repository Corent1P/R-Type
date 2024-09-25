/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** handle draw system methods
*/

#include "HandleDrawSystem.hpp"
#include ".././Components/SFWindowComponent.hh"
#include ".././Components/SpriteComponent.hh"
#include ".././Components/PositionComponent.hh"
// #include "SFML/Graphics"

RType::HandleDrawSystem::HandleDrawSystem()
{
    _type= RType::SystemHandleEvent;
}

RType::HandleDrawSystem::~HandleDrawSystem()
{
}


void RType::HandleDrawSystem::effects(std::vector<std::shared_ptr<RType::Entity>> entities)
{
    
    for (const auto &w: entities) {
        GET_WINDOW_FOR_DRAW->clear();
        if (GET_WINDOW_FOR_DRAW != nullptr) {
            for (const auto &e: entities) {
                if (verifyRequiredComponent(e)) {
                    GET_WINDOW_FOR_DRAW->draw(e->getComponent<RType::SpriteComponent>()->getSprite());
                }
            }
        }
        GET_WINDOW_FOR_DRAW->display();
    }
}

void RType::HandleDrawSystem::effect(std::shared_ptr<RType::Entity> entity)
{
    (void) entity;
}

bool RType::HandleDrawSystem::verifyRequiredComponent(std::shared_ptr<RType::Entity> entity)
{
    if (entity->getComponent<RType::PositionComponent>() == nullptr
    ||entity->getComponent<RType::SpriteComponent>() == nullptr) {
        return false;
    }
    return (true);
}
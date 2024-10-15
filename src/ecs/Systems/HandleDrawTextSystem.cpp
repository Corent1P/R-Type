/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** handle draw system methods
*/

#include "HandleDrawTextSystem.hpp"

RType::HandleDrawTextSystem::HandleDrawTextSystem(std::function<std::shared_ptr<Entity>()> addEntity, std::function<void(std::shared_ptr<Entity>)> deleteEntity):
    ASystem(S_DRAWTEXT, addEntity, deleteEntity)
{
}

RType::HandleDrawTextSystem::~HandleDrawTextSystem()
{
}


void RType::HandleDrawTextSystem::effects(std::vector<std::shared_ptr<RType::Entity>> entities)
{
    for (const auto &w: entities) {
        if (GET_WINDOW_FOR_DRAW != nullptr) {
            for (const auto &entity: entities) {
                if (verifyRequiredComponent(entity) && entity->GET_MENU == w->GET_MENU) {
                    SET_TEXT_POSITION;
                    GET_WINDOW_FOR_DRAW->getWindow()->draw(*(entity->getComponent<RType::TextComponent>()->getText()));
                }
            }
            return;
        }
    }
}

bool RType::HandleDrawTextSystem::verifyRequiredComponent(std::shared_ptr<RType::Entity> entity)
{
    if (entity->getComponent<RType::PositionComponent>() == nullptr
    || entity->getComponent<RType::TextComponent>() == nullptr) {
        return false;
    }
    return (true);
}

/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** handle draw system methods
*/

#include "HandleDrawSystem.hpp"

RType::HandleDrawSystem::HandleDrawSystem(std::function<std::shared_ptr<Entity>()> addEntity, std::function<void(std::shared_ptr<Entity>)> deleteEntity):
    ASystem(S_DRAW, addEntity, deleteEntity)
{
}

RType::HandleDrawSystem::~HandleDrawSystem()
{
}


void RType::HandleDrawSystem::effects(std::vector<std::shared_ptr<RType::Entity>> entities)
{
    for (const auto &w: entities) {
        if (GET_WINDOW_FOR_DRAW != nullptr) {
            for (const auto &entity: entities) {
                if (verifyRequiredComponent(entity, w)) {
                    //drawHitBox(w, entity);
                    GET_WINDOW_FOR_DRAW->getWindow()->draw(*(entity->getComponent<RType::SpriteComponent>()->getSprite()));
                }
            }
            return;
        }
    }
}

bool RType::HandleDrawSystem::verifyRequiredComponent(std::shared_ptr<RType::Entity> entity)
{
    return !(!entity->getComponent<RType::PositionComponent>() || !entity->getComponent<RType::SpriteComponent>());
}

bool RType::HandleDrawSystem::verifyRequiredComponent(std::shared_ptr<RType::Entity> entity, std::shared_ptr<RType::Entity> window)
{
    if (!entity->getComponent<RType::PositionComponent>() || !entity->getComponent<RType::SpriteComponent>())
        return false;
    if (entity->getComponent<RType::EntityTypeComponent>()->getEntityType() == RType::E_LAYER &&
        entity->getComponent<RType::LevelComponent>()->getLevel() != window->getComponent<RType::LevelComponent>()->getLevel()) {
        return false;
    }

    return (*entity->GET_MENU == *window->GET_MENU);
}

void RType::HandleDrawSystem::drawHitBox(const std::shared_ptr<RType::Entity> &w, const std::shared_ptr<RType::Entity> &entity)
{
    if (entity->getComponent<EntityTypeComponent>()->getEntityType() != E_LAYER) {
        sf::FloatRect bounds = entity->getComponent<RType::SpriteComponent>()->getSprite()->getGlobalBounds();
        sf::RectangleShape rect(sf::Vector2f(bounds.width, bounds.height));
        rect.setPosition(entity->getComponent<RType::SpriteComponent>()->getSprite()->getPosition());
        rect.setOutlineColor(sf::Color::Red);
        rect.setOutlineThickness(2);
        GET_WINDOW_FOR_DRAW->getWindow()->draw(rect);
    }
}

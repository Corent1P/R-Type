/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** handle entity movements methods
*/

#include "HandleMoveSystem.hpp"

RType::HandleMoveSystem::HandleMoveSystem(std::function<void(std::shared_ptr<Entity>)> addEntity, std::function<void(std::shared_ptr<Entity>)> deleteEntity):
    ASystem(MOVE, addEntity, deleteEntity)
{
}

RType::HandleMoveSystem::~HandleMoveSystem()
{
}

void RType::HandleMoveSystem::effects(std::vector<std::shared_ptr<RType::Entity>> entities) {
    for (const auto &entity: entities) {
        if (verifyRequiredComponent(entity)) {
            for (const auto &window: entities) {
                if (window->getComponent<RType::SFWindowComponent>() != nullptr) {
                    auto spriteBounds = entity->getComponent<RType::SpriteComponent>()->getSprite()->getGlobalBounds();
                    float windowHeight = window->getComponent<RType::SFWindowComponent>()->getWindow()->getSize().y;
                    float windowWidth = window->getComponent<RType::SFWindowComponent>()->getWindow()->getSize().x;
                    if (entity->getComponent<RType::EntityTypeComponent>()->getEntityType() == RType::PLAYER) {
                        if (entity->getComponent<RType::DirectionComponent>()->getDirections(LEFT) == true && spriteBounds.left > 0) {
                            entity->getComponent<RType::SpriteComponent>()->getSprite()->move(-10, 0);
                        }
                        if (entity->getComponent<RType::DirectionComponent>()->getDirections(RIGHT) == true && spriteBounds.left + spriteBounds.width < windowWidth) {
                            entity->getComponent<RType::SpriteComponent>()->getSprite()->move(10, 0);
                        }
                        if (entity->getComponent<RType::DirectionComponent>()->getDirections(UP) == true && spriteBounds.top > 0) {
                            entity->getComponent<RType::SpriteComponent>()->getSprite()->move(0, -10);
                        }
                        if (entity->getComponent<RType::DirectionComponent>()->getDirections(DOWN) == true && spriteBounds.top + spriteBounds.height < windowHeight) {
                            entity->getComponent<RType::SpriteComponent>()->getSprite()->move(0, 10);
                        }
                    }
                    if(entity->getComponent<DirectionPatternComponent>() != nullptr) {
                        entity->getComponent<RType::SpriteComponent>()->getSprite()->move(entity->getComponent<RType::DirectionPatternComponent>()->getPattern());
                        if ((entity->getComponent<RType::DirectionPatternComponent>()->getPatternType() == RType::STRAIGHT_LEFT
                        || entity->getComponent<RType::DirectionPatternComponent>()->getPatternType() == RType::UP_N_DOWN_LEFT)
                        && spriteBounds.left + spriteBounds.width < windowWidth) {
                            // _deleteEntity(entity);
                        }

                        if ((entity->getComponent<RType::DirectionPatternComponent>()->getPatternType() == RType::STRAIGHT_RIGHT
                        || entity->getComponent<RType::DirectionPatternComponent>()->getPatternType() == RType::UP_N_DOWN_RIGHT)
                        && spriteBounds.left + spriteBounds.width < windowWidth) {
                            //std::cout << "out right" << std::endl;
                            // _deleteEntity(entity);
                        }
                    }
                }
            }
        }
    }
}

bool RType::HandleMoveSystem::verifyRequiredComponent(std::shared_ptr<RType::Entity> entity)
{
    if (entity->getComponent<RType::DirectionComponent>() == nullptr || entity->getComponent<RType::SpriteComponent>() == nullptr)
    {
        return false;
    }
    return (true);
}
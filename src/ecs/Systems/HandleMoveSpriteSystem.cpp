/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** handle entity movements methods
*/

#include "HandleMoveSpriteSystem.hpp"

RType::HandleMoveSpriteSystem::HandleMoveSpriteSystem(std::function<std::shared_ptr<Entity>()> addEntity, std::function<void(std::shared_ptr<Entity>)> deleteEntity):
    ASystem(S_MOVE, addEntity, deleteEntity)
{
}

RType::HandleMoveSpriteSystem::~HandleMoveSpriteSystem()
{
}

void RType::HandleMoveSpriteSystem::effects(std::vector<std::shared_ptr<RType::Entity>> entities) {
    for (const auto &window: entities) {
        if (window->getComponent<RType::SFWindowComponent>() != nullptr) {
            for (const auto &entity: entities) {
                if (verifyRequiredComponent(entity)) {
                    auto spriteBounds = entity->getComponent<RType::SpriteComponent>()->getSprite()->getGlobalBounds();
                    float windowHeight = window->getComponent<RType::SFWindowComponent>()->getWindow()->getSize().y;
                    float windowWidth = window->getComponent<RType::SFWindowComponent>()->getWindow()->getSize().x;

                    sf::Vector2 position = entity->getComponent<PositionComponent>()->getPositions();
                    entity->getComponent<RType::SpriteComponent>()->getSprite()->setPosition(position);
                    if (entity->getComponent<RType::EntityTypeComponent>()->getEntityType() == RType::E_PLAYER) {
                        if (entity->getComponent<RType::DirectionComponent>()->getDirections(LEFT) == true && spriteBounds.left <= 0) {
                            entity->getComponent<RType::SpriteComponent>()->getSprite()->setPosition(0, position.y);
                            entity->getComponent<RType::PositionComponent>()->setX(0);
                        }
                        if (entity->getComponent<RType::DirectionComponent>()->getDirections(RIGHT) == true && spriteBounds.left + spriteBounds.width >= windowWidth) {
                            entity->getComponent<RType::SpriteComponent>()->getSprite()->setPosition(windowWidth - spriteBounds.width, position.y);
                            entity->getComponent<RType::PositionComponent>()->setX(windowWidth - spriteBounds.width);
                        }
                        if (entity->getComponent<RType::DirectionComponent>()->getDirections(UP) == true && spriteBounds.top <= 0) {
                            entity->getComponent<RType::SpriteComponent>()->getSprite()->setPosition(position.x, 0);
                            entity->getComponent<RType::PositionComponent>()->setY(0);
                        }
                        if (entity->getComponent<RType::DirectionComponent>()->getDirections(DOWN) == true && spriteBounds.top + spriteBounds.height >= windowHeight) {
                            entity->getComponent<RType::SpriteComponent>()->getSprite()->setPosition(position.x, windowHeight - spriteBounds.height);
                            entity->getComponent<RType::PositionComponent>()->setY(windowHeight - spriteBounds.height);
                        }
                    }
                    if(entity->getComponent<DirectionPatternComponent>() != nullptr) {
                        entity->getComponent<RType::SpriteComponent>()->getSprite()->setPosition(position);
                        if ((entity->getComponent<RType::DirectionPatternComponent>()->getPatternType() == RType::STRAIGHT_LEFT
                        || entity->getComponent<RType::DirectionPatternComponent>()->getPatternType() == RType::UP_N_DOWN_LEFT)
                        && spriteBounds.left + spriteBounds.width < -300) {
                            _deleteEntity(entity);
                            continue;
                        }

                        if ((entity->getComponent<RType::DirectionPatternComponent>()->getPatternType() == RType::STRAIGHT_RIGHT
                        || entity->getComponent<RType::DirectionPatternComponent>()->getPatternType() == RType::UP_N_DOWN_RIGHT)
                        && spriteBounds.left + spriteBounds.width > windowWidth + 300) {
                            _deleteEntity(entity);
                            continue;
                        }
                    }

                    if (entity->getComponent<EntityTypeComponent>()->getEntityType() == RType::E_LAYER) {
                        int entityPos = (ENTITY_SPRITE->getGlobalBounds().left + ENTITY_SPRITE->getGlobalBounds().width);
                        if (entityPos < 0) {
                            entity->getComponent<PositionComponent>()->setX(window->getComponent<SFWindowComponent>()->getWindow()->getSize().x - 5);
                            ENTITY_SPRITE->setPosition(sf::Vector2f(window->getComponent<SFWindowComponent>()->getWindow()->getSize().x - 5, 0));
                        }
                    }
                }
            }
        }
    }
}

bool RType::HandleMoveSpriteSystem::verifyRequiredComponent(std::shared_ptr<RType::Entity> entity)
{
    if (entity->getComponent<RType::PositionComponent>() == nullptr ||  entity->getComponent<RType::SpriteComponent>() == nullptr) {
        return false;
    }
    return (true);
}
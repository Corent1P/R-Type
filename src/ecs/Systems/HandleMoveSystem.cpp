/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** handle entity movements methods
*/

#include "HandleMoveSystem.hpp"

RType::HandleMoveSystem::HandleMoveSystem(std::function<std::shared_ptr<Entity>()> addEntity, std::function<void(std::shared_ptr<Entity>)> deleteEntity):
    ASystem(MOVE, addEntity, deleteEntity), _client(nullptr)
{
}

RType::HandleMoveSystem::HandleMoveSystem(std::function<std::shared_ptr<Entity>()> addEntity, std::function<void(std::shared_ptr<Entity>)> deleteEntity, std::shared_ptr<RType::Client> client):
    ASystem(MOVE, addEntity, deleteEntity), _client(client)
{
}

RType::HandleMoveSystem::~HandleMoveSystem()
{
}

void RType::HandleMoveSystem::effects(std::vector<std::shared_ptr<RType::Entity>> entities) {
    std::pair<int, int> movePosition(0, 0);
    for (const auto &entity: entities) {
        if (verifyRequiredComponent(entity)) {
            for (const auto &window: entities) {
                if (window->getComponent<RType::SFWindowComponent>() != nullptr) {
                    auto spriteBounds = entity->getComponent<RType::SpriteComponent>()->getSprite()->getGlobalBounds();
                    float windowHeight = window->getComponent<RType::SFWindowComponent>()->getWindow()->getSize().y;
                    float windowWidth = window->getComponent<RType::SFWindowComponent>()->getWindow()->getSize().x;
                    int speed = entity->getComponent<VelocityComponent>()->getVelocity();;

                    if (entity->getComponent<RType::EntityTypeComponent>()->getEntityType() == RType::PLAYER) {
                        if (entity->getComponent<RType::DirectionComponent>()->getDirections(LEFT) == true && spriteBounds.left > 0) {
                            entity->getComponent<RType::SpriteComponent>()->getSprite()->move(-speed, 0);
                            movePosition.first -= speed * 10;
                        }
                        if (entity->getComponent<RType::DirectionComponent>()->getDirections(RIGHT) == true && spriteBounds.left + spriteBounds.width < windowWidth) {
                            entity->getComponent<RType::SpriteComponent>()->getSprite()->move(speed, 0);
                            movePosition.first += speed * 10;
                        }
                        if (entity->getComponent<RType::DirectionComponent>()->getDirections(UP) == true && spriteBounds.top > 0) {
                            entity->getComponent<RType::SpriteComponent>()->getSprite()->move(0, -speed);
                            movePosition.second -= speed * 10;
                        }
                        if (entity->getComponent<RType::DirectionComponent>()->getDirections(DOWN) == true && spriteBounds.top + spriteBounds.height < windowHeight) {
                            entity->getComponent<RType::SpriteComponent>()->getSprite()->move(0, speed);
                            movePosition.second += speed * 10;
                        }
                    }
                    if(entity->getComponent<DirectionPatternComponent>() != nullptr) {
                        auto pattern = entity->getComponent<RType::DirectionPatternComponent>()->getPattern();
                        entity->getComponent<RType::SpriteComponent>()->getSprite()->move(pattern.x * speed / 5., pattern.y * speed / 5.);
                        if ((entity->getComponent<RType::DirectionPatternComponent>()->getPatternType() == RType::STRAIGHT_LEFT
                        || entity->getComponent<RType::DirectionPatternComponent>()->getPatternType() == RType::UP_N_DOWN_LEFT)
                        && spriteBounds.left + spriteBounds.width < 0) {
                            _deleteEntity(entity);
                        }

                        if ((entity->getComponent<RType::DirectionPatternComponent>()->getPatternType() == RType::STRAIGHT_RIGHT
                        || entity->getComponent<RType::DirectionPatternComponent>()->getPatternType() == RType::UP_N_DOWN_RIGHT)
                        && spriteBounds.left + spriteBounds.width > windowWidth) {
                            _deleteEntity(entity);
                        }
                    }

                    if (entity->getComponent<EntityTypeComponent>()->getEntityType() == RType::LAYER) {
                        int entityPos = (ENTITY_SPRITE->getGlobalBounds().left + ENTITY_SPRITE->getGlobalBounds().width);
                        if (entityPos < 0) {
                            ENTITY_SPRITE->setPosition(sf::Vector2f(window->getComponent<SFWindowComponent>()->getWindow()->getSize().x - 5, 0));
                        }
                    }
                    if (_client && entity->getComponent<RType::EntityTypeComponent>()->getEntityType() == PLAYER && (movePosition.first != 0 ||  movePosition.second != 0)) {
                        _client->send(Encoder::movePlayer(movePosition.first, movePosition.second));
                    }
                }
            }
        }
    }
}

bool RType::HandleMoveSystem::verifyRequiredComponent(std::shared_ptr<RType::Entity> entity)
{
    if (entity->getComponent<VelocityComponent>() == nullptr || (entity->getComponent<RType::DirectionComponent>() == nullptr && entity->getComponent<RType::DirectionPatternComponent>() == nullptr) || entity->getComponent<RType::SpriteComponent>() == nullptr)
    {
        return false;
    }
    return (true);
}
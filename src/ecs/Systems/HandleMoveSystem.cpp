/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** handle entity movements methods
*/

#include "HandleMoveSystem.hpp"

RType::HandleMoveSystem::HandleMoveSystem():
    ASystem(MOVE)
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
                    int speed = 0;
                    if (entity->getComponent<RType::DirectionComponent>()->getDirections(LEFT) == true) {
                        speed = entity->getComponent<VelocityComponent>()->getVelocity();
                        entity->getComponent<RType::SpriteComponent>()->getSprite()->move((speed * -1), 0);
                    }
                    if (entity->getComponent<RType::DirectionComponent>()->getDirections(RIGHT) == true && spriteBounds.left + spriteBounds.width < windowWidth) {
                        speed = entity->getComponent<VelocityComponent>()->getVelocity();
                        entity->getComponent<RType::SpriteComponent>()->getSprite()->move(speed, 0);
                    }
                    if (entity->getComponent<RType::DirectionComponent>()->getDirections(UP) == true && spriteBounds.top > 0) {
                        speed = entity->getComponent<VelocityComponent>()->getVelocity();
                        entity->getComponent<RType::SpriteComponent>()->getSprite()->move(0, (speed * -1));
                    }
                    if (entity->getComponent<RType::DirectionComponent>()->getDirections(DOWN) == true && spriteBounds.top + spriteBounds.height < windowHeight) {
                        speed = entity->getComponent<VelocityComponent>()->getVelocity();
                        entity->getComponent<RType::SpriteComponent>()->getSprite()->move(0, speed);
                    }

                    if (entity->getComponent<RType::EntityTypeComponent>()->getEntityType() == RType::WEAPON && entity->getComponent<RType::DirectionComponent>()->getDirections(LEFT) == true && spriteBounds.left > 0) {
                        speed = entity->getComponent<VelocityComponent>()->getVelocity();
                        entity->getComponent<RType::SpriteComponent>()->getSprite()->move((speed * -1), 0);
                    } else if (entity->getComponent<RType::EntityTypeComponent>()->getEntityType() == RType::WEAPON && entity->getComponent<RType::DirectionComponent>()->getDirections(LEFT) == true && spriteBounds.left < 0) {
                        entity->~Entity();
                    }
                    if (entity->getComponent<RType::EntityTypeComponent>()->getEntityType() == RType::WEAPON && entity->getComponent<RType::DirectionComponent>()->getDirections(RIGHT) == true && spriteBounds.left + spriteBounds.width < windowWidth) {
                        speed = entity->getComponent<VelocityComponent>()->getVelocity();
                        entity->getComponent<RType::SpriteComponent>()->getSprite()->move(speed, 0);
                    } else if (entity->getComponent<RType::EntityTypeComponent>()->getEntityType() == RType::WEAPON && entity->getComponent<RType::DirectionComponent>()->getDirections(RIGHT) == true && spriteBounds.left + spriteBounds.width > windowWidth){
                        entity->~Entity();
                    }

                    if (entity->getComponent<EntityTypeComponent>()->getEntityType() == RType::LAYER) {
                        int entityPos = (ENTITY_SPRITE->getGlobalBounds().left + ENTITY_SPRITE->getGlobalBounds().width);
                        if (entityPos < 0) {
                            ENTITY_SPRITE->setPosition(sf::Vector2f(window->getComponent<SFWindowComponent>()->getWindow()->getSize().x - 5, 0));
                        }
                    }
                }
            }
        }
    }
}

void RType::HandleMoveSystem::effect(std::shared_ptr<RType::Entity> entity)
{
    // if (entity->getComponent<RType::DirectionComponent>()->getDirections(LEFT) == true) {
    //     // std::cout << ">>LEFT" << std::endl;
    //     entity->getComponent<RType::SpriteComponent>()->getSprite()->move(-0.1, 0);
    // }
    // if (entity->getComponent<RType::DirectionComponent>()->getDirections(RIGHT) == true) {
    //     //  std::cout << ">>RIGHT" << std::endl;
    //     entity->getComponent<RType::SpriteComponent>()->getSprite()->move(0.1, 0);
    // }
    // if (entity->getComponent<RType::DirectionComponent>()->getDirections(UP) == true) {
    //     //  std::cout << ">>UP" << std::endl;
    //     entity->getComponent<RType::SpriteComponent>()->getSprite()->move(0, -0.1);
    // }
    // if (entity->getComponent<RType::DirectionComponent>()->getDirections(DOWN) == true) {
    //     //  std::cout << ">>DOWN" << std::endl;
    //     entity->getComponent<RType::SpriteComponent>()->getSprite()->move(0, 0.1);
    // }
    (void) entity;
}

bool RType::HandleMoveSystem::verifyRequiredComponent(std::shared_ptr<RType::Entity> entity)
{
    if ( entity->getComponent<VelocityComponent>() == nullptr || entity->getComponent<RType::DirectionComponent>() == nullptr || entity->getComponent<RType::SpriteComponent>() == nullptr)
    {
        return false;
    }
    return (true);
}
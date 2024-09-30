/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** system handling animations methods
*/

#include "HandleAnimationSystem.hpp"

RType::HandleAnimationSystem::HandleAnimationSystem():
    ASystem(ANIMATION)
{
}

RType::HandleAnimationSystem::~HandleAnimationSystem()
{
}

void RType::HandleAnimationSystem::effect(std::shared_ptr<RType::Entity> entity)
{
    if (verifyRequiredComponent(entity)) {
        // if (entity->getComponent<RType::EntityTypeComponent>()->getEntityType() == PLAYER){
            sf::IntRect rect = entity->getComponent<RType::SpriteComponent>()->getSprite()->getTextureRect();  //need to create a component ?
            int maxSpritWidth = entity->getComponent<RType::SpriteComponent>()->getSprite()->getTexture()->getSize().x;
            if (entity->getComponent<RType::ClockComponent>()->getClock().getElapsedTime().asSeconds() > 0.3f) {
                if (rect.left == (maxSpritWidth - rect.width))
                    rect.left = 0;
                else
                    rect.left += rect.width;
                entity->getComponent<RType::SpriteComponent>()->getSprite()->setTextureRect(rect);
                entity->getComponent<RType::ClockComponent>()->getClock().restart();
            }
        // }
    }
}

bool RType::HandleAnimationSystem::verifyRequiredComponent(std::shared_ptr<RType::Entity> entity)
{
    if (entity->getComponent<RType::PositionComponent>() == nullptr
    ||entity->getComponent<RType::SpriteComponent>() == nullptr
    ||entity->getComponent<RType::EntityTypeComponent>() == nullptr
    ||entity->getComponent<RType::ClockComponent>() == nullptr
    ) {
        return false;
    }
    return (true);
}
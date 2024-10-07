/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** system handling animations methods
*/

#include "HandleAnimationSystem.hpp"

RType::HandleAnimationSystem::HandleAnimationSystem(std::function<std::shared_ptr<Entity>()> addEntity, std::function<void(std::shared_ptr<Entity>)> deleteEntity):
    ASystem(ANIMATION, addEntity, deleteEntity)
{
}

RType::HandleAnimationSystem::~HandleAnimationSystem()
{
}

void RType::HandleAnimationSystem::effect(std::shared_ptr<RType::Entity> entity)
{

    if (verifyRequiredComponent(entity)) {
        sf::IntRect rect = entity->getComponent<RType::SpriteComponent>()->getSprite()->getTextureRect();  //need to create a component ?
        int maxSpritWidth = entity->getComponent<RType::SpriteComponent>()->getSprite()->getTexture()->getSize().x;
        if (entity->getComponent<RType::ClockComponent>()->getClock(RType::ClockType::ANIMATION_CLOCK).getElapsedTime().asSeconds() > 0.1f) {
            if (rect.left == (maxSpritWidth - rect.width))
                rect.left = 0;
            else
                rect.left += rect.width;
            entity->getComponent<RType::SpriteComponent>()->getSprite()->setTextureRect(rect);
            entity->getComponent<RType::ClockComponent>()->getClock(RType::ClockType::ANIMATION_CLOCK).restart();
        }
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
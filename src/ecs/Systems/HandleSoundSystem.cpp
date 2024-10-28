/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** system handling direction sound methods
*/

#include "HandleSoundSystem.hpp"

RType::HandleSoundSystem::HandleSoundSystem(std::function<std::shared_ptr<Entity>()> addEntity, std::function<void(std::shared_ptr<Entity>)> deleteEntity):
    ASystem(S_PATTERN, addEntity, deleteEntity)
{
}

RType::HandleSoundSystem::~HandleSoundSystem()
{
}

void RType::HandleSoundSystem::effect(std::shared_ptr<RType::Entity> entity)
{
    entity->getComponent<SoundComponent>()->getSound().play();
}

bool RType::HandleSoundSystem::verifyRequiredComponent(std::shared_ptr<RType::Entity> entity)
{
    return (entity->getComponent<SoundComponent>() && entity->getComponent<SoundComponent>()->getSound().getStatus() != sf::Sound::Status::Playing &&
    entity->getComponent<PositionComponent>()->getPositionX() > 0);
}

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
    entity->getComponent<SoundQueueComponent>()->deleteFinishedSound();
    entity->getComponent<SoundQueueComponent>()->playAllSounds();
}

bool RType::HandleSoundSystem::verifyRequiredComponent(std::shared_ptr<RType::Entity> entity)
{
    return (entity->getComponent<SoundQueueComponent>() != nullptr);
}

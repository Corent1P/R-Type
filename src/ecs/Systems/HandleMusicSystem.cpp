/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** system handling direction sound methods
*/

#include "HandleMusicSystem.hpp"

RType::HandleMusicSystem::HandleMusicSystem(std::function<std::shared_ptr<Entity>()> addEntity, std::function<void(std::shared_ptr<Entity>)> deleteEntity):
    ASystem(S_PATTERN, addEntity, deleteEntity)
{
}

RType::HandleMusicSystem::~HandleMusicSystem()
{
}

void RType::HandleMusicSystem::effect(std::shared_ptr<RType::Entity> entity)
{
    if (entity->getComponent<MusicComponent>()->getMusic().getStatus() != sf::SoundSource::Playing)
        entity->getComponent<MusicComponent>()->getMusic().play();
}

bool RType::HandleMusicSystem::verifyRequiredComponent(std::shared_ptr<RType::Entity> entity)
{
    return (entity->getComponent<MusicComponent>() != nullptr);
}

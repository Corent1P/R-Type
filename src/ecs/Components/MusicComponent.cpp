/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** MusicComponent
*/

#include "MusicComponent.hh"

RType::MusicComponent::MusicComponent(const std::string &musicPath)
{
    if (!_music.openFromFile(musicPath))
        throw EcsError("Music: " + musicPath + " was not found");
    _music.setLoop(true);
    _music.setVolume(50);
}

sf::Music &RType::MusicComponent::getMusic()
{
    return _music;
}

std::string RType::MusicComponent::getOutput() const
{
    std::string output("Music Component");
    return output;
}

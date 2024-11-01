/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** MusicComponent
*/

#include "MusicComponent.hh"

RType::MusicComponent::MusicComponent(const std::string &musicPath):
    _volume(50)
{
    if (!_music.openFromFile(musicPath))
        return;
    _music.setLoop(true);
    _music.setVolume(_volume);
}

sf::Music &RType::MusicComponent::getMusic()
{
    return _music;
}

std::size_t RType::MusicComponent::getVolume() const
{
    return _volume;
}

void RType::MusicComponent::setVolume(int volume)
{
    _volume = volume < 0 ? 0 : volume;
    _volume = _volume > 100 ? 100 : _volume;
    _music.setVolume(volume);
}

std::string RType::MusicComponent::getOutput() const
{
    std::string output("Music Component");
    return output;
}

/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** SoundBufferComponent
*/

#include "SoundBufferComponent.hh"

RType::SoundBufferComponent::SoundBufferComponent(const std::string &path):
    _path(path)
{
    if (!_soundBuffer.loadFromFile(path))
        throw EcsError("Failed Load sound: " + path);
}

const sf::SoundBuffer &RType::SoundBufferComponent::getSoundBuffer() const
{
    return _soundBuffer;
}

std::string RType::SoundBufferComponent::getOutput() const
{
    std::string output("Sound Buffer Component (Sound: " + _path + ")");
    return output;
}

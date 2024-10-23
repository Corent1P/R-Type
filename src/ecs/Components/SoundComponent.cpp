/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** SoundComponent
*/

#include "SoundComponent.hh"

RType::SoundComponent::SoundComponent(const std::string &soundPath):
    _path(soundPath)
{
    _soundBuffer = std::make_shared<sf::SoundBuffer>();

    if (!_soundBuffer->loadFromFile(soundPath))
	_soundBuffer->loadFromFile("");
    _sound = std::make_shared<sf::Sound>();
    _sound->setBuffer(*_soundBuffer);
}

RType::SoundComponent::~SoundComponent()
{
}

std::shared_ptr<sf::Sound> RType::SoundComponent::getSound() const
{
    return _sound;
}

std::shared_ptr<sf::SoundBuffer> RType::SoundComponent::getSoundBuffer() const
{
    return _soundBuffer;
}

std::string RType::SoundComponent::getOutput() const
{
    std::string output("Sound Component (Sound: " + _path  + ")");
    return (output);
}

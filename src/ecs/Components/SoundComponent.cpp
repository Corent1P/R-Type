/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** SoundComponent
*/

#include "SoundComponent.hh"

RType::SoundComponent::SoundComponent(const sf::SoundBuffer &soundBuffer)
{
    _sound.setBuffer(soundBuffer);
}

sf::Sound &RType::SoundComponent::getSound()
{
    return _sound;
}

std::string RType::SoundComponent::getOutput() const
{
    std::string output("Sound Component");
    return output;
}

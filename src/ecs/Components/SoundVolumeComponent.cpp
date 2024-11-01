/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** SoundVolumeComponent
*/

#include "SoundVolumeComponent.hh"

RType::SoundVolumeComponent::SoundVolumeComponent():
    _volume(50)
{}

int RType::SoundVolumeComponent::getVolume() const
{
    return _volume;
}

void RType::SoundVolumeComponent::setVolume(int volume)
{
    _volume = volume < 0 ? 0 : volume;
    _volume = _volume > 100 ? 100 : _volume;
}

std::string RType::SoundVolumeComponent::getOutput() const
{
    std::string output("SoundVolumeComponent");
    return output;
}

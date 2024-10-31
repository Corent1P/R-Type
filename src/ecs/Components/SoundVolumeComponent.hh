/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** SoundVolumeComponent
*/

#include <iostream>

#pragma once

#include "../IComponent.hh"

namespace RType {
    class SoundVolumeComponent : public IComponent{
    public:
        SoundVolumeComponent();
        ~SoundVolumeComponent() = default;

        int getVolume() const;
        void setVolume(int volume);
        std::string getOutput() const;
    private:
        std::size_t _volume;
    };
}

/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** SoundBufferComponent
*/

#pragma once
#include <SFML/Audio.hpp>
#include "../IComponent.hh"

namespace RType {
    class SoundBufferComponent: public RType::IComponent {
        public:
            SoundBufferComponent(const std::string &path);
            ~SoundBufferComponent() = default;
            const sf::SoundBuffer &getSoundBuffer() const;
            std::string getOutput() const;

        private:
            std::string _path;
            sf::SoundBuffer _soundBuffer;
    };
}

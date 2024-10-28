/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** SoundComponent
*/

#pragma once
#include <SFML/Audio.hpp>
#include "../IComponent.hh"
#include "./PositionComponent.hh"

namespace RType {
    class SoundComponent: public RType::IComponent {
        public:
            SoundComponent(const sf::SoundBuffer &soundBuffer);
            ~SoundComponent() = default;
            sf::Sound &getSound();
            std::string getOutput() const;

        private:
            sf::Sound _sound;
    };
}

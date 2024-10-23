/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** SoundComponent
*/

#pragma once
#include <SFML/Audio.hpp>
#include "../IComponent.hh"

namespace RType {
    class SoundComponent: public RType::IComponent {
        public:
            SoundComponent(const std::string &soundPath);
            ~SoundComponent();
            std::shared_ptr<sf::Sound> getSound() const;
            std::shared_ptr<sf::SoundBuffer> getSoundBuffer() const;
            std::string getOutput() const;

        private:
            std::string _path;
            std::shared_ptr<sf::SoundBuffer> _soundBuffer;
            std::shared_ptr<sf::Sound> _sound;
    };
}

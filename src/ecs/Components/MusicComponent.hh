/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** MusicComponent
*/

#pragma once
#include <SFML/Audio.hpp>
#include "../IComponent.hh"
#include "./PositionComponent.hh"

namespace RType {
    class MusicComponent: public RType::IComponent {
        public:
            MusicComponent(const std::string &musicPath);
            ~MusicComponent() = default;
            sf::Music &getMusic();
            std::string getOutput() const;

        private:
            sf::Music _music;
    };
}
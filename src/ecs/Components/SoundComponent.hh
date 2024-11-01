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

    /**
     * @brief Sound component class
     */
    class SoundComponent: public RType::IComponent {
        public:
            /**
             * @brief Construct a new SoundComponent object
             *
             * @param soundBuffer Sound buffer
             */
            SoundComponent(const sf::SoundBuffer &soundBuffer);

            /**
             * @brief Destroy the SoundComponent object
             */
            ~SoundComponent() = default;

            /**
             * @brief Get the sound
             *
             * @return sf::Sound& Sound object
             */
            sf::Sound &getSound();

            /**
             * @brief Get the output as a string
             *
             * @return std::string Output string
             */
            std::string getOutput() const;

        private:
            /**
             * @brief Sound object
             */
            sf::Sound _sound;
    };
}

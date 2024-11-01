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
    /**
     * @brief Music component class
     */
    class MusicComponent: public RType::IComponent {
        public:
            /**
             * @brief Construct a new Music Component object
             *
             * @param musicPath Path to the music file
             */
            MusicComponent(const std::string &musicPath);

            /**
             * @brief Get the Music object
             *
             * @return sf::Music& Reference to the music object
             */
            sf::Music &getMusic();

            /**
             * @brief Get the Volume
             *
             * @return std::size_t Current volume
             */
            std::size_t getVolume() const;

            /**
             * @brief Set the Volume
             *
             * @param volume New volume
             */
            void setVolume(int volume);

            /**
             * @brief Get the Output as a string
             *
             * @return std::string Output string
             */
            std::string getOutput() const;

        private:
            /**
             * @brief Music object
             */
            sf::Music _music;

            /**
             * @brief Volume level
             */
            std::size_t _volume;
    };
}

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

    /**
     * @brief Sound buffer component class
     */
    class SoundBufferComponent: public RType::IComponent {
        public:
            /**
             * @brief Construct a new SoundBufferComponent object
             *
             * @param path Path to the sound file
             */
            SoundBufferComponent(const std::string &path);

            /**
             * @brief Destroy the SoundBufferComponent object
             */
            ~SoundBufferComponent() = default;

            /**
             * @brief Get the sound buffer
             *
             * @return const sf::SoundBuffer & Sound buffer
             */
            const sf::SoundBuffer &getSoundBuffer() const;

            /**
             * @brief Get the output as a string
             *
             * @return std::string Output string
             */
            std::string getOutput() const;

        private:
            /**
             * @brief Path to the sound file
             */
            std::string _path;

            /**
             * @brief Sound buffer
             */
            sf::SoundBuffer _soundBuffer;
    };
}

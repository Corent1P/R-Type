/*
** EPITECH PROJECT, 2024
** rType
** File description:
** SoundQueueComponent
*/

#pragma once
#include <SFML/Audio.hpp>
#include <tuple>
#include <vector>
#include <memory>
#include "../IComponent.hh"

namespace RType {

    /**
     * @brief Sound queue component class
     */
    class SoundQueueComponent : public RType::IComponent {
        public:
            /**
             * @brief Construct a new SoundQueueComponent object
             */
            SoundQueueComponent();

            /**
             * @brief Destroy the SoundQueueComponent object
             */
            ~SoundQueueComponent() = default;

            /**
             * @brief Push a sound to the queue
             *
             * @param soundBuffer Sound buffer
             * @param volume Volume level
             */
            void pushSound(const sf::SoundBuffer &soundBuffer, float volume = 100);

            /**
             * @brief Get the sounds
             *
             * @return const std::vector<std::tuple<std::shared_ptr<sf::Sound>, bool>> & Vector of sounds
             */
            const std::vector<std::tuple<std::shared_ptr<sf::Sound>, bool>> &getSounds() const;

            /**
             * @brief Delete finished sounds
             */
            void deleteFinishedSound();

            /**
             * @brief Play all sounds
             */
            void playAllSounds();

            /**
             * @brief Set the global sound volume
             *
             * @param volume Volume level
             */
            void setGlobalSoundVolume(int volume);

            /**
             * @brief Get the global sound volume
             *
             * @return std::size_t Volume level
             */
            std::size_t getGlobalSoundVolume() const;

            /**
             * @brief Get the output as a string
             *
             * @return std::string Output string
             */
            std::string getOutput() const;

        private:
            /**
             * @brief Vector of sounds
             */
            std::vector<std::tuple<std::shared_ptr<sf::Sound>, bool>> _sounds;

            /**
             * @brief Global sound volume
             */
            std::size_t _globalSoundVolume;
    };
}

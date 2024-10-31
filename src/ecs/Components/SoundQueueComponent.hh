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
    class SoundQueueComponent : public RType::IComponent {
        public:
            SoundQueueComponent();
            ~SoundQueueComponent() = default;

            void pushSound(const sf::SoundBuffer &soundBuffer, float volume = 100);
            const std::vector<std::tuple<std::shared_ptr<sf::Sound>, bool>> &getSounds() const;
            void deleteFinishedSound();
            void playAllSounds();
            void setGlobalSoundVolume(int volume);
            std::size_t getGlobalSoundVolume() const;
            std::string getOutput() const;

        private:
            std::vector<std::tuple<std::shared_ptr<sf::Sound>, bool>> _sounds;
            std::size_t _globalSoundVolume;
    };
}

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

    /**
     * @brief Sound volume component class
     */
    class SoundVolumeComponent : public IComponent {
    public:
        /**
         * @brief Construct a new SoundVolumeComponent object
         */
        SoundVolumeComponent();

        /**
         * @brief Destroy the SoundVolumeComponent object
         */
        ~SoundVolumeComponent() = default;

        /**
         * @brief Get the volume
         *
         * @return int Volume level
         */
        int getVolume() const;

        /**
         * @brief Set the volume
         *
         * @param volume Volume level
         */
        void setVolume(int volume);

        /**
         * @brief Get the output as a string
         *
         * @return std::string Output string
         */
        std::string getOutput() const;

    private:
        /**
         * @brief Volume level
         */
        std::size_t _volume;
    };
}

/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** AutoUpdateTextComponent
*/

#include <iostream>

#pragma once

#include "../IComponent.hh"

namespace RType {
    enum autoUpdateWithValue {
        MUSIC_VOLUME,
        SOUND_VOLUME
    };

    /**
     * @brief AutoUpdateTextComponent class for handling the auto update of text
     *
     */
    class AutoUpdateTextComponent : public RType::IComponent {
    public:
        /**
         * @brief Construct a new AutoUpdateTextComponent object
         *
         * @param value The value to update
         */
        AutoUpdateTextComponent(enum autoUpdateWithValue value);

        /**
         * @brief Destroy the AutoUpdateTextComponent object
         *
         */
        ~AutoUpdateTextComponent() = default;

        /**
         * @brief Get the value of the component
         *
         * @return enum autoUpdateWithValue The value of the component
         */
        enum autoUpdateWithValue getValue() const;

        /**
         * @brief Get the output of the component
         *
         * @return std::string The output of the component
         */
        std::string getOutput() const;
    private:

        /**
         * @brief The value to update
         *
         */
        enum autoUpdateWithValue _value;
    };
}

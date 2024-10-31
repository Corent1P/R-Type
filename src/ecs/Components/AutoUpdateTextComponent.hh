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

    class AutoUpdateTextComponent : public RType::IComponent {
    public:
        AutoUpdateTextComponent(enum autoUpdateWithValue value);
        ~AutoUpdateTextComponent() = default;

        enum autoUpdateWithValue getValue() const;
        std::string getOutput() const;
    private:
        enum autoUpdateWithValue _value;
    };
}

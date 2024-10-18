/*
** EPITECH PROJECT, 2024
** R-type
** File description:
** Interface for Components
*/

#pragma once

#include "Include.hh"

namespace RType {
    class IComponent {
        public:
            virtual ~IComponent() = default;
            virtual std::string getOutput() const = 0;
    };
}

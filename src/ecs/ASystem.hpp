/*
** EPITECH PROJECT, 2024
** R-type
** File description:
** Interface for systems
*/

#ifndef ASYSTEM_HPP_
#define ASYSTEM_HPP_

#include "ISystem.hpp"

class ASystem: public ISystem {
    public:
        ASystem() = default;
        ~ASystem() = default;
        void effect();
        bool verifyRequierdComponent();
};

#endif /* !ASYSTEM_HPP_ */

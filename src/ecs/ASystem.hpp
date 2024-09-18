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
        bool verifyRequiredComponent();
};

std::ostream &operator<<(std::ostream &s, const ASystem &system);
#endif /* !ASYSTEM_HPP_ */

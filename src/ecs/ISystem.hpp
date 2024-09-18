/*
** EPITECH PROJECT, 2024
** R-type
** File description:
** Interface for systems
*/

#ifndef ISYSTEM_HPP_
#define ISYSTEM_HPP_

#include "Include.hh"
#include "ASystem.hpp"

class ISystem {
    public:
        virtual ~ISystem() = default;
        virtual void effect() = 0;
        virtual bool verifyRequiredComponent() = 0;
};

#endif /* !ISYSTEM_HPP_ */

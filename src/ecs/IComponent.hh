/*
** EPITECH PROJECT, 2024
** R-type
** File description:
** Interface for Components
*/

#ifndef ICOMPONENT_HPP_
#define ICOMPONENT_HPP_

#include "Include.hh"

namespace RType {
    class IComponent {
        public:
            virtual ~IComponent() = default;
            virtual std::string getOutput() const = 0;
    };
}

#endif /* !ICOMPONENT_HPP_ */

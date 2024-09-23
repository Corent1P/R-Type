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
    enum ComponentType {
        ComponentBasic = 0,
        ComponentPosition = 1,
        ComponentHealth = 2,
    };

    class IComponent {
        public:
            virtual ~IComponent() = default;
            virtual ComponentType getType() const = 0;
            virtual std::string getOutput() const = 0;
    };
}
std::ostream &operator<<(std::ostream &s, const RType::IComponent &component);

#endif /* !ICOMPONENT_HPP_ */

/*
** EPITECH PROJECT, 2024
** R-type
** File description:
** Interface for systems
*/

#ifndef ISYSTEM_HPP_
#define ISYSTEM_HPP_

#include "Include.hh"
#include "Entity.hpp"

namespace RType {

    enum SystemType {
        SystemBasic
    };

    class ISystem {
        public:
            virtual ~ISystem() = default;
            virtual void effect(std::shared_ptr<Entity> entities) = 0;
            virtual bool verifyRequiredComponent(Entity entity) = 0;
            virtual SystemType getType() const = 0;
    };

}
std::ostream &operator<<(std::ostream &s, const RType::ISystem &system);

#endif /* !ISYSTEM_HPP_ */

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

#define GET_WINDOW entity->getComponent<RType::SFWindowComponent>()->getWindow()

namespace RType {

    enum SystemType {
        BASIC,
        EVENT,
        DRAW,
        MOVE,
        ANIMATION,
        PATTERN,
    };

    class ISystem {
        public:
            virtual ~ISystem() = default;
            virtual void effects(std::vector<std::shared_ptr<RType::Entity>> entities) = 0;
            virtual void effect(std::shared_ptr<RType::Entity> entity) = 0;
            virtual bool verifyRequiredComponent(std::shared_ptr<RType::Entity> entity) = 0;
            virtual SystemType getType() const = 0;
    };

}
std::ostream &operator<<(std::ostream &s, const RType::ISystem &system);

#endif /* !ISYSTEM_HPP_ */

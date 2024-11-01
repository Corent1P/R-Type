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
        S_BASIC,
        S_EVENT,
        S_CLEAR,
        S_DRAW,
        S_DRAWTEXT,
        S_DISPLAY,
        S_MOVE,
        S_ANIMATION,
        S_PATTERN,
        S_SHOOT,
        S_COLISION,
        S_ENTITY_MOB_SYSTEM,
        S_BOSS_ATTACK
    };

    class ISystem {
        public:
            /**
             * @brief Destroy the ISystem object
             *
             */
            virtual ~ISystem() = default;
            /**
             * @brief method looping on each entities in order to check if they have the mendatory Component in order to process the system effect.
             *        Also used to process a system effect if two distincts entites are involved in the procces.
             *
             * @param entities a vector that contains each entity stored in the coordinator.
             */
            virtual void effects(std::vector<std::shared_ptr<RType::Entity>> entities) = 0;
            /**
             * @brief a method to handle the System action on the right entity.
             *
             * @param entity entity required in order to process a action.
             */
            virtual void effect(std::shared_ptr<RType::Entity> entity) = 0;
            /**
             * @brief a method to verify if a entity has the right components to process the system effect.
             *
             * @param entity
             * @return true
             * @return false
             */
            virtual bool verifyRequiredComponent(std::shared_ptr<RType::Entity> entity) = 0;
            /**
             * @brief Get the system type
             *
             * @return SystemType
             */
            virtual SystemType getType() const = 0;
    };

}
std::ostream &operator<<(std::ostream &s, const RType::ISystem &system);

#endif /* !ISYSTEM_HPP_ */

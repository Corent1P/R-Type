/*
** EPITECH PROJECT, 2024
** R-type
** File description:
** Interface for systems
*/

#ifndef ASYSTEM_HPP_
#define ASYSTEM_HPP_

#include "ISystem.hh"
#include "math.h"
#include <functional>

namespace RType {
    class ASystem: public ISystem {
        public:
            /**
             * @brief Construct a new ASystem object
             * 
             * @param type type of the system in use.
             * @param addEntity method used to add a new Entity to the coordinator.
             * @param deleteEntity method used to delete a Entity from the coordinator.
             */
            ASystem(SystemType type = S_BASIC, std::function<std::shared_ptr<Entity>()> addEntity = nullptr, std::function<void(std::shared_ptr<Entity>)> deleteEntity = nullptr);
            ~ASystem() = default;
            void effects(std::vector<std::shared_ptr<RType::Entity>> entities);
            /**
             * @brief amethod to handle the System action on the right entity.
             * 
             * @param entity entity required in order to process an action.
             */
            void effect(std::shared_ptr<RType::Entity> entity);
            /**
             * @brief a method to verify if a entity has the right components to process the system effect.
             * 
             * @param entity
             * @return true 
             * @return false 
             */
            bool verifyRequiredComponent(std::shared_ptr<RType::Entity> entity);
            /**
             * @brief Get the Type of a system.
             * 
             * @return SystemType 
             */
            SystemType getType() const;
        protected:
            SystemType _type;
            std::function<std::shared_ptr<Entity>()> _addEntity;
            std::function<void(std::shared_ptr<Entity>)> _deleteEntity;
    };
}
#endif /* !ASYSTEM_HPP_ */

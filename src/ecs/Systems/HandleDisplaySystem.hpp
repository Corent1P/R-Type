/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** System handling direction display for any entity
*/

#ifndef HANDLEDISPLAYSYSTEM_HPP_
#define HANDLEDISPLAYSYSTEM_HPP_
#include "../ASystem.hh"
#include "../Components/SFWindowComponent.hh"

namespace RType {
    /**
     * @brief a system that set a entity movement direction value based on a display.
     *
     */
    class HandleDisplaySystem: public ASystem {
        public:
            /**
             * @brief Construct a new Handle Display System object
             *
             * @param addEntity method used to add a new Entity to the coordinator.
             * @param deleteEntity method used to delete a Entity from the coordinator.
             */
            HandleDisplaySystem(std::function<std::shared_ptr<Entity>(void)> addEntity, std::function<void(std::shared_ptr<Entity>)> deleteEntity);
            /**
             * @brief Destroy the Handle Display System object
             *
             */
            ~HandleDisplaySystem();
            /**
             * @brief a method to handle the System action on the right entity.
             *
             * @param entity entity required in order to process a action.
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
        protected:
        private:
            /**
             * @brief a vector of all entities.
             *
             */
            std::vector<std::shared_ptr<RType::Entity>> _entities;
    };
}

#endif /* !HANDLEDISPLAYSYSTEM_HPP_ */

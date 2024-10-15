/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** System handling direction clear for any entity
*/

#ifndef HANDLECLEARSYSTEM_HPP_
#define HANDLECLEARSYSTEM_HPP_
#include "../ASystem.hh"
#include "../Components/SFWindowComponent.hh"

namespace RType {
    /**
     * @brief a system that clear the window
     *
     */
    class HandleClearSystem: public ASystem {
        public:
            /**
             * @brief Construct a new Handle Clear System object
             *
             * @param addEntity method used to add a new Entity to the coordinator.
             * @param deleteEntity method used to delete a Entity from the coordinator.
             */
            HandleClearSystem(std::function<std::shared_ptr<Entity>(void)> addEntity, std::function<void(std::shared_ptr<Entity>)> deleteEntity);
            /**
             * @brief Destroy the Handle Clear System object
             *
             */
            ~HandleClearSystem();
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
            std::vector<std::shared_ptr<RType::Entity>> _entities;
    };
}

#endif /* !HANDLECLEARSYSTEM_HPP_ */

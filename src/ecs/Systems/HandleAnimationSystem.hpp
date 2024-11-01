/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** System handling any entity based on their type
*/

#ifndef HANDLEANIMATIONSYSTEM_HPP_
#define HANDLEANIMATIONSYSTEM_HPP_
#include "../ASystem.hh"
#include ".././Components/SFWindowComponent.hh"
#include ".././Components/SpriteComponent.hh"
#include ".././Components/PositionComponent.hh"
#include ".././Components/ClockComponent.hh"
#include ".././Components/EntityTypeComponent.hh"

namespace RType {
    /**
     * @brief a system that handle entities sprites animations.
     *
     */
    class HandleAnimationSystem: public ASystem {
        public:
            /**
             * @brief Construct a new Handle Animation System object.
             *
             * @param addEntity add entity to the coordinator method.
             * @param deleteEntity delete a entity from the coordinator vector.
             */
            HandleAnimationSystem(std::function<std::shared_ptr<Entity>()> addEntity, std::function<void(std::shared_ptr<Entity>)> deleteEntity);
            /**
             * @brief Destroy the Handle Animation System object
             *
             */
            ~HandleAnimationSystem();
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

#endif /* !HANDLEANIMATIONSYSTEM_HPP_ */

/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** System handling direction pattern for any entity
*/

#ifndef HANDLEPATTERNSYSTEM_HPP_
#define HANDLEPATTERNSYSTEM_HPP_
#include "../ASystem.hh"
#include "../Components/SFWindowComponent.hh"
#include "../Components/SpriteComponent.hh"
#include "../Components/PositionComponent.hh"
#include "../Components/ClockComponent.hh"
#include "../Components/EntityTypeComponent.hh"
#include "../Components/DirectionPatternComponent.hh"
#include "../Components/IntRectComponent.hh"
#include "../Components/ScaleComponent.hh"

#define GET_PATTERN getComponent<RType::DirectionPatternComponent>()

namespace RType {
    /**
     * @brief a system that set a entity movement direction value based on a pattern.
     *
     */
    class HandlePatternSystem: public ASystem {
        public:
            /**
             * @brief Construct a new Handle Pattern System object
             *
             * @param addEntity method used to add a new Entity to the coordinator.
             * @param deleteEntity method used to delete a Entity from the coordinator.
             */
            HandlePatternSystem(std::function<std::shared_ptr<Entity>(void)> addEntity, std::function<void(std::shared_ptr<Entity>)> deleteEntity);
            /**
             * @brief Destroy the Handle Pattern System object
             *
             */
            ~HandlePatternSystem();
            /**
             * @brief method looping on each entities in order to check if they have the mendatory Component in order to process the system effect.
             *        Also used to process a system effect if two distincts entites are involved in the procces.
             *
             * @param entities a vector that contains each entity stored in the coordinator.
             */
            void effects(std::vector<std::shared_ptr<RType::Entity>> entities);
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
             * @brief  a vector that contains each entity stored in the coordinator.
             *
             */
            std::vector<std::shared_ptr<RType::Entity>> _entities;
            /**
             * @brief a mehtod handling the FollowEntities Pattern.
             *
             * @param entities a vector that contains each entity stored in the coordinator.
             * @param entity the entity to follow.
             */
            void handlePatternFollowEntities(std::vector<std::shared_ptr<RType::Entity>> &entities, const std::shared_ptr<RType::Entity> &entity);
    };
}

#endif /* !HANDLEPATTERNSYSTEM_HPP_ */

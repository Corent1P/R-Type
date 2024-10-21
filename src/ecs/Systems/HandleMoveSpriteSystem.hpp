/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** system used to handle entity sprite movement
*/

#ifndef HANDLEMOVESPRITESYTEM_HPP_
#define HANDLEMOVESPRITESYTEM_HPP_
#include "../ASystem.hh"
#include ".././Components/SFWindowComponent.hh"
#include ".././Components/EventComponent.hh"
#include ".././Components/DirectionComponent.hh"
#include ".././Components/EntityTypeComponent.hh"
#include ".././Components/SpriteComponent.hh"
#include ".././Components/DirectionPatternComponent.hh"
#include "../Components/VelocityComponent.hh"
#include "../../client/Game.hh"

#define GET_WINDOW_SET_ISOPEN entity->getComponent<RType::SFWindowComponent>()
#define GET_WINDOW_POLL_EVENT e->getComponent<RType::SFWindowComponent>()->getWindow()
#define EVENT_TYPE e->getComponent<RType::EventComponent>()->getEvent().type
#define ENTITY_SPRITE entity->getComponent<SpriteComponent>()->getSprite()
namespace RType {
    /**
     * @brief a system that handle a Entity sprite movement.
     *
     */
    class HandleMoveSpriteSystem: public  RType::ASystem {
        public:
            /**
             * @brief Construct a new Handle Move Sprite System object
             *
             * @param addEntity method used to add a new Entity to the coordinator.
             * @param deleteEntity method used to delete a Entity from the coordinator.
             */
            HandleMoveSpriteSystem(std::function<std::shared_ptr<Entity>()> addEntity, std::function<void(std::shared_ptr<Entity>)> deleteEntity);
            /**
             * @brief Destroy the Handle Move Sprite System object
             *
             */
            ~HandleMoveSpriteSystem();
            /**
             * @brief method looping on each entities in order to check if they have the mendatory Component in order to process the system effect.
             *        Also used to process a system effect if two distincts entites are involved in the procces.
             *
             * @param entities a vector that contains each entity stored in the coordinator.
             */
            void effects(std::vector<std::shared_ptr<RType::Entity>> entities);
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

    };
}
#endif /* !HANDLEMOVESPRITESYTEM_HPP_ */

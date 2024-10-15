/*
** EPITECH PROJECT, 2024
** R-type
** File description:
** handling event system
*/

#ifndef HANDLEEVENTSYTEM_HPP_
#define HANDLEEVENTSYTEM_HPP_

#include "../ASystem.hh"
#include "../Components/SFWindowComponent.hh"
#include "../Components/EventComponent.hh"
#include "../Components/DirectionComponent.hh"
#include "../Components/EntityTypeComponent.hh"
#include "../Components/SpriteComponent.hh"
#include "../Components/ActionComponent.hh"
#include "../Components/ClockComponent.hh"
#include "../Components/MappingInputComponent.hh"
#include "../Components/ClickEffectComponent.hh"
#include "../Components/IntRectComponent.hh"
#include "../Components/PositionComponent.hh"

#define GET_WINDOW_SET_ISOPEN entity->getComponent<RType::SFWindowComponent>()
#define GET_WINDOW_POLL_EVENT e->getComponent<RType::SFWindowComponent>()->getWindow()
#define EVENT_TYPE e->getComponent<RType::EventComponent>()->getEvent().type
#define GET_ENTITY_SPRITE player->getComponent<SpriteComponent>()->getSprite()
#define CLICK_ON_BUTTON player->getComponent<RType::ClickEffectComponent>()->getClickEffect()(e)

namespace RType {
    /**
     * @brief a system handling Event of the game.
     *
     */
    class HandleEventSystem: public  RType::ASystem {
        public:
            /**
             * @brief Construct a new Handle Event System object.
             *
             * @param addEntity method used to add a new Entity to the coordinator.
             * @param deleteEntity method used to delete a Entity from the coordinator.
             */
            HandleEventSystem(std::function<std::shared_ptr<Entity>()> addEntity, std::function<void(std::shared_ptr<Entity>)> deleteEntity);
            /**
             * @brief Destroy the Handle Event System object.
             *
             */
            ~HandleEventSystem();
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
            bool _isShooting;
    };
}
#endif /* !HANDLEEVENTSYTEM_HPP_ */

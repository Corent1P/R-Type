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
#include "../Components/TextComponent.hh"
#include "../Components/MenuComponent.hh"
#include "../Components/SFWindowComponent.hh"

#define GET_WINDOW_SET_ISOPEN entity->getComponent<RType::SFWindowComponent>()
#define GET_WINDOW_POLL_EVENT e->getComponent<RType::SFWindowComponent>()->getWindow()
#define EVENT_TYPE e->getComponent<RType::EventComponent>()->getEvent().type
#define GET_ENTITY_SPRITE player->getComponent<SpriteComponent>()->getSprite()
#define CLICK_ON_BUTTON button->getComponent<RType::ClickEffectComponent>()->getClickEffect()(window)

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
             * @param disconnexion method used to disconnect the client from the server.
             */
            HandleEventSystem(std::function<std::shared_ptr<Entity>()> addEntity, std::function<void(std::shared_ptr<Entity>)> deleteEntity, std::function<void(void)> disconnexion = nullptr);
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
            /**
             * @brief Modify the mapping input map
             *
             * @param entities vector of all the entities
             * @param window window entity
             */
            void modifyInput(std::vector<std::shared_ptr<RType::Entity>> entities, std::shared_ptr<RType::Entity> window);
            /**
             * @brief get input Player to move player
             *
             * @param player player entity
             * @param window window entity
             * @param inputs map of input with <Action, input>
             */
            void handleInputPlayer(std::shared_ptr<RType::Entity> player, std::shared_ptr<RType::Entity> window, std::unordered_map<RType::MappingInput, sf::Keyboard::Key> inputs);
            /**
             * @brief handle the click to apply the effect of the button, exemple: return to home page
             *
             * @param button button entity
             * @param window window entity
             */
            void handleClickOnButton(std::shared_ptr<RType::Entity> button, std::shared_ptr<RType::Entity> window);
            /**
             * @brief boolean for know if player has already shoot
             *
             */
            bool _isShooting;

            std::function<void(void)> _disconnexion;
    };
}
#endif /* !HANDLEEVENTSYTEM_HPP_ */

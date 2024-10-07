/*
** EPITECH PROJECT, 2024
** R-type
** File description:
** handling event system
*/

#ifndef HANDLEEVENTSYTEM_HPP_
#define HANDLEEVENTSYTEM_HPP_

#include "../ASystem.hh"
#include ".././Components/SFWindowComponent.hh"
#include ".././Components/EventComponent.hh"
#include ".././Components/DirectionComponent.hh"
#include ".././Components/EntityTypeComponent.hh"
#include ".././Components/SpriteComponent.hh"
#include ".././Components/ActionComponent.hh"
#include ".././Components/ClockComponent.hh"

#define GET_WINDOW_SET_ISOPEN entity->getComponent<RType::SFWindowComponent>()
#define GET_WINDOW_POLL_EVENT e->getComponent<RType::SFWindowComponent>()->getWindow()
#define EVENT_TYPE e->getComponent<RType::EventComponent>()->getEvent().type
#define GET_ENTITY_SPRITE player->getComponent<SpriteComponent>()->getSprite()

namespace RType {

    class HandleEventSystem: public  RType::ASystem {
        public:
            HandleEventSystem(std::function<std::shared_ptr<Entity>()> addEntity, std::function<void(std::shared_ptr<Entity>)> deleteEntity);
            ~HandleEventSystem();
            void effects(std::vector<std::shared_ptr<RType::Entity>> entities);
            void effect(std::shared_ptr<RType::Entity> entity);
            bool verifyRequiredComponent(std::shared_ptr<RType::Entity> entity);
        protected:
        private:
            bool _isShooting;
    };
}
#endif /* !HANDLEEVENTSYTEM_HPP_ */

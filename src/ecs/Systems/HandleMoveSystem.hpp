/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** system used to handle entity movement
*/

#ifndef HANDLEMOVESYTEM_HPP_
#define HANDLEMOVESYTEM_HPP_
#include "../ASystem.hh"
#include "../Components/SFWindowComponent.hh"
#include "../Components/EventComponent.hh"
#include "../Components/DirectionComponent.hh"
#include "../Components/EntityTypeComponent.hh"
#include "../Components/SpriteComponent.hh"
#include "../Components/VelocityComponent.hh"
#include "../../client/Game.hh"

#define GET_WINDOW_SET_ISOPEN entity->getComponent<RType::SFWindowComponent>()
#define GET_WINDOW_POLL_EVENT e->getComponent<RType::SFWindowComponent>()->getWindow()
#define EVENT_TYPE e->getComponent<RType::EventComponent>()->getEvent().type
#define ENTITY_SPRITE entity->getComponent<SpriteComponent>()->getSprite()
namespace RType {

    class HandleMoveSystem: public  RType::ASystem {
        public:
            HandleMoveSystem();
            HandleMoveSystem(std::shared_ptr<RType::Client> client);
            ~HandleMoveSystem();
            void effects(std::vector<std::shared_ptr<RType::Entity>> entities);
            void effect(std::shared_ptr<RType::Entity> entity);
            bool verifyRequiredComponent(std::shared_ptr<RType::Entity> entity);
        protected:
        private:
            std::shared_ptr<RType::Client> _client;
    };
}
#endif /* !HANDLEMOVESYTEM_HPP_ */

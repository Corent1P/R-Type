/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** system used to handle entity movement
*/

#ifndef HANDLEMOVESYTEM_HPP_
#define HANDLEMOVESYTEM_HPP_
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

    class HandleMoveSystem: public  RType::ASystem {
        public:
            HandleMoveSystem(std::function<std::shared_ptr<Entity>()> addEntity, std::function<void(std::shared_ptr<Entity>)> deleteEntity);
            HandleMoveSystem(std::function<std::shared_ptr<Entity>()> addEntity, std::function<void(std::shared_ptr<Entity>)> deleteEntity, std::shared_ptr<RType::Client> client);
            HandleMoveSystem(std::function<std::shared_ptr<Entity>()> addEntity, std::function<void(std::shared_ptr<Entity>)> deleteEntity, std::function<void(const std::basic_string<unsigned char> &message)> sendMessageToAllClient);
            ~HandleMoveSystem();
            void effects(std::vector<std::shared_ptr<RType::Entity>> entities);
            bool verifyRequiredComponent(std::shared_ptr<RType::Entity> entity);
        protected:
        private:
            std::shared_ptr<RType::Client> _client;
            std::function<void(const std::basic_string<unsigned char> &message)> _sendMessageToAllClient;
    };
}
#endif /* !HANDLEMOVESYTEM_HPP_ */

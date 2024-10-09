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
    /**
     * @brief a system that move a entity based on his type and direction.
     *
     */
    class HandleMoveSystem: public  RType::ASystem {
        public:
            /**
             * @brief Construct a new Handle Move System object
             *
             * @param addEntity method used to add a new Entity to the coordinator.
             * @param deleteEntity method used to delete a Entity from the coordinator.
             */
            HandleMoveSystem(std::function<std::shared_ptr<Entity>()> addEntity, std::function<void(std::shared_ptr<Entity>)> deleteEntity);
            /**
             * @brief Construct a new Handle Move System object
             *
             * @param addEntity method used to add a new Entity to the coordinator.
             * @param deleteEntity method used to delete a Entity from the coordinator.
             * @param client class that send information from client to server.
             */
            HandleMoveSystem(std::function<std::shared_ptr<Entity>()> addEntity, std::function<void(std::shared_ptr<Entity>)> deleteEntity, std::shared_ptr<RType::Client> client);
            /**
             * @brief Construct a new Handle Move System object
             *
             * @param addEntity method used to add a new Entity to the coordinator.
             * @param deleteEntity method used to delete a Entity from the coordinator.
             * @param client class that send information from client to server.
             * @param sendMessageToAllClient methods that send to all clients the message in parameter.
             */
            HandleMoveSystem(std::function<std::shared_ptr<Entity>()> addEntity, std::function<void(std::shared_ptr<Entity>)> deleteEntity, std::function<void(const std::basic_string<unsigned char> &message)> sendMessageToAllClient);
            /**
             * @brief Destroy the Handle Move System object
             *
             */
            ~HandleMoveSystem();
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
            std::shared_ptr<RType::Client> _client;
            std::function<void(const std::basic_string<unsigned char> &message)> _sendMessageToAllClient;
    };
}
#endif /* !HANDLEMOVESYTEM_HPP_ */

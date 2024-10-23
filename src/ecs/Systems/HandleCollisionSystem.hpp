/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** system used to handle entity collision
*/

#ifndef HANDLECOLISIONSYTEM_HPP_
#define HANDLECOLISIONSYTEM_HPP_
#include "../ASystem.hh"
#include ".././Components/SFWindowComponent.hh"
#include ".././Components/EventComponent.hh"
#include ".././Components/DirectionComponent.hh"
#include ".././Components/EntityTypeComponent.hh"
#include ".././Components/SpriteComponent.hh"
#include ".././Components/ActionComponent.hh"
#include ".././Components/PositionComponent.hh"
#include ".././Components/DirectionPatternComponent.hh"
#include ".././Components/TextureComponent.hh"
#include ".././Components/ClockComponent.hh"
#include ".././Components/VelocityComponent.hh"
#include ".././Components/IntRectComponent.hh"
#include "../../client/Game.hh"

namespace RType {

    class HandleCollisionSystem: public  RType::ASystem {
        public:
            /**
             * @brief Construct a new Handle Collision System object
             *
             * @param addEntity The function to add an entity into the coordinator
             * @param deleteEntity The function to delete an entity from the coordinator
             */
            HandleCollisionSystem(std::function<std::shared_ptr<Entity>()> addEntity, std::function<void(std::shared_ptr<Entity>)> deleteEntity);
            /**
             * @brief Construct a new Handle Collision System object
             *
             * @param addEntity The function to add an entity into the coordinator
             * @param deleteEntity The function to delete an entity from the coordinator
             * @param sendMessageToAllClient The function to send a message to all clients connected
             */
            HandleCollisionSystem(std::function<std::shared_ptr<Entity>()> addEntity, std::function<void(std::shared_ptr<Entity>)> deleteEntity, std::function<void(const std::basic_string<unsigned char> &message)> sendMessageToAllClient);
            /**
             * @brief Destroy the Handle Collision System object
             *
             */
            ~HandleCollisionSystem();
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
             * @brief a method to handle the System action on the right entity.
             *
             * @param entity entity required in order to process a action.
             */
            bool verifyRequiredComponent(std::shared_ptr<RType::Entity> entity);

        private:
            /**
             * @brief a function to send a message to all clients connected (only for the server side)
             *
             */
            std::function<void(const std::basic_string<unsigned char> &message)> _sendMessageToAllClient;
            /**
             * @brief A vector containing all the entities that are colliding
             *
             */
            std::vector<std::pair<std::shared_ptr<RType::Entity>, std::shared_ptr<RType::Entity>>> _entitiesColiding;
            /**
             * @brief A vector containing all the entities that were colliding the loop before
             *
             */
            std::vector<std::pair<std::shared_ptr<RType::Entity>, std::shared_ptr<RType::Entity>>> _entitiesColidingBefore;
            /**
             * @brief A vector containing all the entities that are going to be destroyed
             *
             */
            std::vector<std::shared_ptr<RType::Entity>> _entitiesToDestroy;

            /**
             * @brief a method to check if two entities are colliding
             *
             * @param entity1 the first entity
             * @param entity2 the second entity
             * @return if the entities are colliding
             */
            bool collides(std::shared_ptr<RType::Entity> entity1, std::shared_ptr<RType::Entity> entity2);
            /**
             * @brief a method to handle the collision between two entities
             *
             */
            void handleEntityCollision(const std::pair<std::shared_ptr<RType::Entity>, std::shared_ptr<RType::Entity>> &entitiesColliding);
            /**
             * @brief a method to handle the collision between all entities
             *
             */
            void handleEntityCollisions(void);
            /**
             * @brief a method to check if the collision was already here in the previous loop
             *
             * @param colidingPair the entities that are colliding
             * @return if the collision is in the past
             */
            bool isInPastCollision(const std::pair<std::shared_ptr<RType::Entity>, std::shared_ptr<RType::Entity>> &colidingPair);

            void decreaseHealth(std::shared_ptr<RType::Entity> entity, int damage);
    };
}
#endif /* !HANDLECOLISIONSYTEM_HPP_ */

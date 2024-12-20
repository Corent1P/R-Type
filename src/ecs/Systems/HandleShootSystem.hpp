/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** system used to handle entity shoot
*/

#ifndef HANDLESHOOTSYTEM_HPP_
#define HANDLESHOOTSYTEM_HPP_
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
#include "../Components/ShootIntervalComponent.hh"
#include "../../client/Game.hh"

#define GET_CLOCK getComponent<ClockComponent>()
#define GET_SHOOTING_CLOCK GET_CLOCK->getClock(SHOOTING_CLOCK)
namespace RType {
    /**
     * @brief a system that handle entities to shoot a bullet by creating a new entity of type weapon to the coordinator.
     *
     */
    class HandleShootSystem: public  RType::ASystem {
        public:
            /**
             * @brief Construct a new Handle Shoot System object
             *
             * @param addEntity method used to add a new Entity to the coordinator.
             * @param deleteEntity method used to delete a Entity from the coordinator.
             * @param sendMessageToServer method that send information from client to server.
             * @param sendMessageToAllClient methods that send to all clients the message in parameter.
             */
            HandleShootSystem(std::function<std::shared_ptr<Entity>()> addEntity, std::function<void(std::shared_ptr<Entity>)> deleteEntity, std::function<void(const std::basic_string<unsigned char> &message)> sendMessageToServer = nullptr, std::function<void(const std::basic_string<unsigned char> &message)> sendMessageToAllClient = nullptr);
            /**
             * @brief Destroy the Handle Shoot System object
             *
             */
            ~HandleShootSystem();
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
             * @brief a method creating a enemy bullet entity.
             *
             * @param entity the entity shooting a enemy bullet.
             */
            void createEnnemyBullet(const std::shared_ptr<RType::Entity> &entity);
            /**
             * @brief a method creating a forcepod bullet entity.
             *
             * @param entitythe a entity of type forcepod shooting a bullet.
             */
            void createForcePodBullet(const std::shared_ptr<RType::Entity> &entity);
            /**
             * @brief a method sending a message to the server.
             *
             */
            std::function<void(const std::basic_string<unsigned char> &message)> _sendMessageToServer;
            /**
             * @brief a method sending a message to all clients.
             *
             */
            std::function<void(const std::basic_string<unsigned char> &message)> _sendMessageToAllClient;

    };
}
#endif /* !HANDLESHOOTSYTEM_HPP_ */

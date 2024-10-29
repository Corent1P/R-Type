/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** System handling any entity based on their type
*/

#ifndef HANDLEBOSSATTACKSYSTEM_HPP_
#define HANDLEBOSSATTACKSYSTEM_HPP_
#include "../ASystem.hh"

#include ".././Components/ClockComponent.hh"
#include ".././Components/EntityTypeComponent.hh"
#include ".././Components/AttackComponent.hh"
#include ".././Components/ShootIntervalComponent.hh"
#include ".././Components/HealthComponent.hh"

namespace RType {
    /**
     * @brief a system that handle entities sprites BossAttacks.
     *
     */
    class HandleBossAttackSystem: public ASystem {
        public:
            /**
             * @brief Construct a new Handle Boss Attack System object.
             *
             * @param addEntity add entity to the coordinator method.
             * @param deleteEntity delete a entity from the coordinator vector.
             * @param sendMessageToAllClient The function to send a message to all clients connected
             */
            HandleBossAttackSystem(std::function<std::shared_ptr<Entity>()> addEntity, std::function<void(std::shared_ptr<Entity>)> deleteEntity,  std::function<void(const std::basic_string<unsigned char> &message)> sendMessageToAllClient = nullptr);
            /**
             * @brief Destroy the Handle BossAttack System object
             *
             */
            ~HandleBossAttackSystem();
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
            std::function<void(const std::basic_string<unsigned char> &message)> _sendMessageToAllClient;
    };
}

#endif /* !HANDLEBOSSATTACKSYSTEM_HPP_ */

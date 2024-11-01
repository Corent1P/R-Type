/*
** EPITECH PROJECT, 2024
** rType
** File description:
** IAttackPattern
*/

#pragma once

#include "../../Entity.hpp"
#include <functional>
#include "../EntityTypeComponent.hh"
#include <json/json.h>
#include <json/reader.h>
#include <fstream>

#include "../PositionComponent.hh"
#include "../HealthComponent.hh"
#include "../EntityTypeComponent.hh"
#include "../SFWindowComponent.hh"
#include "../EventComponent.hh"
#include "../ClockComponent.hh"
#include "../ActionComponent.hh"
#include "../DirectionPatternComponent.hh"
#include "../VelocityComponent.hh"
#include "../ScaleComponent.hh"
#include "../IntRectComponent.hh"
#include "../MappingInputComponent.hh"
#include "../MenuComponent.hh"
#include "../ClickEffectComponent.hh"
#include "../ShootIntervalComponent.hh"
#include "../DamageComponent.hh"
#include "../PowerUpComponent.hh"
#include "../AttackComponent.hh"
#include "../ScoreComponent.hh"

#define PUSH_POS_E(x, y) pushComponent(std::make_shared<RType::PositionComponent>(x, y))
#define PUSH_ACTION_E() pushComponent(std::make_shared<RType::ActionComponent>())
#define PUSH_TYPE_E(type) pushComponent(std::make_shared<RType::EntityTypeComponent>(type))
#define PUSH_SCALE_E(x, y) pushComponent(std::make_shared<RType::ScaleComponent>(x, y))
#define PUSH_RECT_E(x, y, w, h) pushComponent(std::make_shared<RType::IntRectComponent>(x, y, w, h))
#define PUSH_HEALTH_E(hp) pushComponent(std::make_shared<RType::HealthComponent>(hp))
#define PUSH_DAMAGE_E(dmg) pushComponent(std::make_shared<RType::DamageComponent>(dmg))
#define PUSH_VELOCITY_E(speed) pushComponent(std::make_shared<RType::VelocityComponent>(speed))
#define PUSH_PATTERN_E(pattern) pushComponent(std::make_shared<RType::DirectionPatternComponent>(pattern))
#define PUSH_CLOCK_E() pushComponent(std::make_shared<RType::ClockComponent>())
#define PUSH_INTERVALSHOOT_E(interval) pushComponent(std::make_shared<RType::ShootIntervalComponent>(interval))
#define PUSH_ATTACK_E() pushComponent(std::make_shared<RType::AttackComponent>())

namespace RType {
    /**
     * @brief AttackPatterns class for handling the attack patterns of the bosses
     *
     */
    class AttackPatterns {
        public:

            /**
             * @brief Spawn a vertical line of 5 baby flies
             *
             * @param boss The boss entity
             * @param addEntity The function to add an entity
             * @param sendMessageToAllClient The function to send a message to all clients
             */
            static void spawnBabyFly(std::shared_ptr<RType::Entity> boss, std::function<std::shared_ptr<Entity>()> addEntity, std::function<void(const std::basic_string<unsigned char> &message)> sendMessageToAllClient);

            /**
             * @brief Spawn a vertical line of 6 stings
             *
             * @param boss The boss entity
             * @param addEntity The function to add an entity
             * @param sendMessageToAllClient The function to send a message to all clients
             */
            static void spawnSting(std::shared_ptr<RType::Entity> boss, std::function<std::shared_ptr<Entity>()> addEntity, std::function<void(const std::basic_string<unsigned char> &message)> sendMessageToAllClient);

            /**
             * @brief Shoot a bullet
             *
             * @param boss The boss entity
             * @param addEntity The function to add an entity
             * @param sendMessageToAllClient The function to send a message to all clients
             */
            static void spaceShipShoot(std::shared_ptr<RType::Entity> boss, std::function<std::shared_ptr<Entity>()> addEntity, std::function<void(const std::basic_string<unsigned char> &message)> sendMessageToAllClient);

            /**
             * @brief Shoot a wave of bullets
             *
             * @param boss The boss entity
             * @param addEntity The function to add an entity
             * @param sendMessageToAllClient The function to send a message to all clients
             */
            static void waveShoot(std::shared_ptr<RType::Entity> boss, std::function<std::shared_ptr<Entity>()> addEntity, std::function<void(const std::basic_string<unsigned char> &message)> sendMessageToAllClient);

            /**
             * @brief Spawn a < pattern of baby octopus
             *
             * @param boss The boss entity
             * @param addEntity The function to add an entity
             * @param sendMessageToAllClient The function to send a message to all clients
             */
            static void spawnBabyOctopus(std::shared_ptr<RType::Entity> boss, std::function<std::shared_ptr<Entity>()> addEntity, std::function<void(const std::basic_string<unsigned char> &message)> sendMessageToAllClient);

            /**
             * @brief Spawn a > pattern of baby octopus
             *
             * @param boss The boss entity
             * @param addEntity The function to add an entity
             * @param sendMessageToAllClient The function to send a message to all clients
             */
            static void spawnKamikazeOctopus(std::shared_ptr<RType::Entity> boss, std::function<std::shared_ptr<Entity>()> addEntity, std::function<void(const std::basic_string<unsigned char> &message)> sendMessageToAllClient);

            /**
             * @brief Spawn a wall of static bombs with a random bomb missing in the wall
             *
             * @param boss The boss entity
             * @param addEntity The function to add an entity
             * @param sendMessageToAllClient The function to send a message to all clients
             */
            static void spawnWallStaticBomb(std::shared_ptr<RType::Entity> boss, std::function<std::shared_ptr<Entity>()> addEntity, std::function<void(const std::basic_string<unsigned char> &message)> sendMessageToAllClient);

            /**
             * @brief Spawn a wall of zigzag bombs
             *
             * @param boss The boss entity
             * @param addEntity The function to add an entity
             * @param sendMessageToAllClient The function to send a message to all clients
             */
            static void spawnWallZigZagBomb(std::shared_ptr<RType::Entity> boss, std::function<std::shared_ptr<Entity>()> addEntity, std::function<void(const std::basic_string<unsigned char> &message)> sendMessageToAllClient);

        private:

            /**
             * @brief Create a game entity with specific parameters
             *
             * @param type The entity type
             * @param posX X-coordinate position
             * @param posY Y-coordinate position
             * @param addEntity The function to add an entity
             * @param sendMessageToAllClient The function to send a message to all clients
             */
            static void createEntity(const RType::EntityType &type, const int &posX, const int &posY, std::function<std::shared_ptr<Entity>()> addEntity, std::function<void(const std::basic_string<unsigned char> &message)> sendMessageToAllClient);
    };
};
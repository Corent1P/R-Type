/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** HandleMobSpawnSystem
*/

#pragma once

#include <fstream>
#include <json/json.h>
#include <iostream>
#include <lua.hpp>

#include "../ASystem.hh"
#include "../Components/ClockComponent.hh"
#include "../Components/EntityTypeComponent.hh"
#include "../Components/PositionComponent.hh"
#include "../Components/IntRectComponent.hh"
#include "../Components/HealthComponent.hh"
#include "../Components/VelocityComponent.hh"
#include "../Components/DirectionComponent.hh"
#include "../Components/DirectionPatternComponent.hh"
#include "../Components/ScaleComponent.hh"
#include "../Components/ActionComponent.hh"
#include "../Components/ShootIntervalComponent.hh"
#include "../Components/MenuComponent.hh"
#include "../Components/PowerUpComponent.hh"
#include "../Components/DamageComponent.hh"
#include "../Components/ParseLevelInfoComponent.hh"
#include "../Components/AttackComponent.hh"
#include "../Components/ScoreComponent.hh"

#define POS_COMPONENT std::shared_ptr<RType::PositionComponent>

#define PUSH_TYPE_E(type) pushComponent(std::make_shared<RType::EntityTypeComponent>(type))
#define PUSH_POS_E(x, y) pushComponent(std::make_shared<RType::PositionComponent>(x, y))
#define PUSH_SCALE_E(x, y) pushComponent(std::make_shared<RType::ScaleComponent>(x, y))
#define PUSH_RECT_E(x, y, w, h) pushComponent(std::make_shared<RType::IntRectComponent>(x, y, w, h))
#define PUSH_CLOCK_E() pushComponent(std::make_shared<RType::ClockComponent>())
#define PUSH_HEALTH_E(hp) pushComponent(std::make_shared<RType::HealthComponent>(hp))
#define PUSH_DAMAGE_E(dmg) pushComponent(std::make_shared<RType::DamageComponent>(dmg))
#define PUSH_VELOCITY_E(speed) pushComponent(std::make_shared<RType::VelocityComponent>(speed))
#define PUSH_PATTERN_E(pattern) pushComponent(std::make_shared<RType::DirectionPatternComponent>(pattern))
#define PUSH_ACTION_E() pushComponent(std::make_shared<RType::ActionComponent>())
#define PUSH_INTERVALSHOOT_E(interval) pushComponent(std::make_shared<RType::ShootIntervalComponent>(interval))
#define SET_ENTITY_TO_FOLLOW_E(entity) getComponent<RType::DirectionPatternComponent>()->setEntityToFollow(entity->getId())
#define PUSH_ATTACK_E() pushComponent(std::make_shared<RType::AttackComponent>())

namespace RType {
    /**
     * @brief a system handling Entity Spawn.
     *
     */
    class HandleEntitySpawnSystem : public ASystem {
        public:
            /**
             * @brief Construct a new Handle Entity Spawn System object.
             *
             * @param addEntity method used to add a new Entity to the coordinator.
             * @param deleteEntity method used to delete a Entity from the coordinator.
             */
            HandleEntitySpawnSystem(std::function<std::shared_ptr<Entity>()> addEntity, std::function<void(std::shared_ptr<Entity>)> deleteEntity);
            /**
             * @brief Construct a new Handle Entity Spawn System object
             *
             * @param addEntity The function to add an entity into the coordinator
             * @param deleteEntity The function to delete an entity from the coordinator
             * @param sendToAllClient The function to send a message to all clients connected
             */
            HandleEntitySpawnSystem(std::function<std::shared_ptr<Entity>()> addEntity, std::function<void(std::shared_ptr<Entity>)> deleteEntity, std::function<void(const std::basic_string<unsigned char> &message)> sendToAllClient);
            /**
             * @brief Destroy the Handle Entity Spawn System object.
             *
             */
            ~HandleEntitySpawnSystem();
            /**
             * @brief method looping on each entities in order to check if they have the mendatory Component in order to process the system effect.
             *        Also used to process a system effect if two distincts entities are involved in the procces.
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

        private:
            static int luaTrampolineCreateEntity(lua_State *luaState);
            /**
             * @brief a method creating a new entity.
             *
             * @param LuaState
             */
            void createEntity(lua_State *LuaState);
            /**
             * @brief a method creating a new entity.
             *
             * @param type the entity type.
             * @param toFollow the entity to follow if the directionPatternComponent need to follow another entity.
             * @param offset the position offset with the entity to follow.
             */
            void createEntity(EntityType type, std::shared_ptr<RType::Entity> toFollow,
                              std::pair<int, int> offset);
            /**
             * @brief Create a Entity Map object
             *
             */
            void createEntityMap(void);
            /**
             * @brief a method sending a message to all client.
             *
             */
            std::function<void(const std::basic_string<unsigned char> &message)> _sendToAllClient;
            std::unordered_map<EntityType, std::string> _entityTypeMap;
            float _prevTime;
    };
}

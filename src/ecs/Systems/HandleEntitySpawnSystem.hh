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
#include "../ASystem.hh"
#include "../Components/ClockComponent.hh"
#include "../Components/EntityTypeComponent.hh"
#include "../Components/PositionComponent.hh"
#include "../Components/IntRectComponent.hh"
#include "../Components/HealthComponent.hh"
#include "../Components/VelocityComponent.hh"
#include "../Components/DirectionPatternComponent.hh"
#include "../Components/ScaleComponent.hh"
#include "../Components/ActionComponent.hh"
#include "../Components/ShootIntervalComponent.hh"

#define POS_COMPONENT std::shared_ptr<RType::PositionComponent>

#define PUSH_TYPE_E(type) pushComponent(std::make_shared<RType::EntityTypeComponent>(type))
#define PUSH_POS_E(x, y) pushComponent(std::make_shared<RType::PositionComponent>(x, y))
#define PUSH_SCALE_E(x, y) pushComponent(std::make_shared<RType::ScaleComponent>(x, y))
#define PUSH_RECT_E(x, y, w, h) pushComponent(std::make_shared<RType::IntRectComponent>(x, y, w, h))
#define PUSH_CLOCK_E() pushComponent(std::make_shared<RType::ClockComponent>())
#define PUSH_HEALTH_E(hp) pushComponent(std::make_shared<RType::HealthComponent>(hp))
#define PUSH_VELOCITY_E(speed) pushComponent(std::make_shared<RType::VelocityComponent>(speed))
#define PUSH_PATTERN_E(pattern) pushComponent(std::make_shared<RType::DirectionPatternComponent>(pattern))
#define PUSH_ACTION_E() pushComponent(std::make_shared<RType::ActionComponent>())
#define PUSH_INTERVALSHOOT_E(interval) pushComponent(std::make_shared<RType::ShootIntervalComponent>(interval))

namespace RType {
    class HandleEntitySpawnSystem : public ASystem {
        public:
            HandleEntitySpawnSystem(std::function<std::shared_ptr<Entity>()> addEntity, std::function<void(std::shared_ptr<Entity>)> deleteEntity);
            HandleEntitySpawnSystem(std::function<std::shared_ptr<Entity>()> addEntity, std::function<void(std::shared_ptr<Entity>)> deleteEntity, std::function<void(const std::basic_string<unsigned char> &message)> sendToAllClient);
            ~HandleEntitySpawnSystem();
            void effect(std::shared_ptr<RType::Entity> entity);
            bool verifyRequiredComponent(std::shared_ptr<RType::Entity> entity);

        private:
            void createEntity(int posX, int posY, EntityType type);

            std::function<void(const std::basic_string<unsigned char> &message)> _sendToAllClient;
            int _y_spawn = 700;
            short _sign = -1;
    };
}

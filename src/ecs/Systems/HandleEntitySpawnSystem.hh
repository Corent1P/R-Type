/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** HandleMobSpawnSystem
*/

#pragma once

#include "../ASystem.hh"
#include "../Components/ClockComponent.hh"
#include "../Components/EntityTypeComponent.hh"
#include "../Components/PositionComponent.hh"
#include "../Components/IntRectComponent.hh"
#include "../Components/HealthComponent.hh"
#include "../Components/VelocityComponent.hh"
#include "../Components/DirectionPatternComponent.hh"
#include "../Components/ScaleComponent.hh"

namespace RType {
    class HandleEntitySpawnSystem : public ASystem {
        public:
            HandleEntitySpawnSystem(std::function<std::shared_ptr<Entity>()> addEntity, std::function<void(std::shared_ptr<Entity>)> deleteEntity);
            HandleEntitySpawnSystem(std::function<std::shared_ptr<Entity>()> addEntity, std::function<void(std::shared_ptr<Entity>)> deleteEntity, std::function<void(const std::basic_string<unsigned char> &message)> sendToAllClient);
            ~HandleEntitySpawnSystem();
            void effect(std::shared_ptr<RType::Entity> entity);
            bool verifyRequiredComponent(std::shared_ptr<RType::Entity> entity);

        private:
            void createMobOctopus(int x, int y);
            void createMobFly(int x, int y);
            void createMobSpaceShip(int x, int y);

            std::function<void(const std::basic_string<unsigned char> &message)> _sendToAllClient;
            int _y_spawn = 700;
            char _sign = -1;
    };
}

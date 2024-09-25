/*
** EPITECH PROJECT, 2024
** rType
** File description:
** Game
*/

#pragma once

#include "../ecs/Coordinator.hh"
#include "../ecs/Components/PositionComponent.hh"
#include "../ecs/Components/HealthComponent.hh"
#include "../ecs/Components/EntityTypeComponent.hh"
#include "../ecs/Components/SFWindowComponent.hh"
#include "../ecs/Components/EventComponent.hh"
#include "../ecs/Components/TextureComponent.hh"
#include "../ecs/Components/SpriteComponent.hh"

#include "../ecs/Systems/HandleEventSystem.hpp"

namespace RType {
    class Game {
        public:
            Game();
            ~Game();
            void gameLoop();
            Coordinator getCoordinator() const;
        private:
            void createPlayer();
            void createMob();
            void createBoss();
            void createWindow();
            void createGameSystem();
            RType::Coordinator _coord;
            bool _stopLoop;
    };
}

std::ostream &operator<<(std::ostream &s, const RType::Game &game);

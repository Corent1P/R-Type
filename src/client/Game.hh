/*
** EPITECH PROJECT, 2024
** rType
** File description:
** Game
*/

#pragma once

#include "./communication/Client.hh"

#include "../ecs/Coordinator.hh"
#include "../ecs/Components/PositionComponent.hh"
#include "../ecs/Components/HealthComponent.hh"
#include "../ecs/Components/EntityTypeComponent.hh"
#include "../ecs/Components/SFWindowComponent.hh"
#include "../ecs/Components/EventComponent.hh"
#include "../ecs/Components/TextureComponent.hh"
#include "../ecs/Components/SpriteComponent.hh"
#include "../ecs//Components/DirectionComponent.hh"
#include "../ecs//Components/ClockComponent.hh"

#include "../ecs/Systems/HandleEventSystem.hpp"
#include "../ecs/Systems/HandleDrawSystem.hpp"
#include "../ecs/Systems/HandleMoveSystem.hpp"
#include "../ecs/Systems/HandleAnimationSystem.hpp"
#include <thread>

#include "../protocolHandler/Encoder.hh"
#include "../protocolHandler/Decoder.hh"


namespace RType {
    class Game {
        public:
            Game(boost::asio::io_context &ioContext, const std::string &host, const std::string &port);
            ~Game();
            void gameLoop();
            Coordinator getCoordinator() const;
        private:
            void loopReceive();
            void createPlayer();
            void createMob();
            void createBoss();
            void createWindow();
            void createGameSystem();
            RType::Coordinator _coord;
            std::shared_ptr<RType::Client> _client;
            bool _stopLoop;
            std::jthread _receipter;
    };
}

std::ostream &operator<<(std::ostream &s, const RType::Game &game);

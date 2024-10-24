/*
** EPITECH PROJECT, 2024
** rType
** File description:
** Game
*/

#pragma once

#include <unordered_map>
#include <vector>
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
#include "../ecs/Components/ActionComponent.hh"
#include "../ecs/Components/DirectionPatternComponent.hh"
#include "../ecs/Components/VelocityComponent.hh"
#include "../ecs/Components/ScaleComponent.hh"
#include "../ecs/Components/IntRectComponent.hh"

#include "../ecs/Systems/HandleEventSystem.hpp"
#include "../ecs/Systems/HandleDrawSystem.hpp"
#include "../ecs/Systems/HandleMoveSystem.hpp"
#include "../ecs/Systems/HandleMoveSpriteSystem.hpp"
#include "../ecs/Systems/HandleAnimationSystem.hpp"
#include "../ecs/Systems/HandlePatternSystem.hpp"
#include "../ecs/Systems/HandleShootSystem.hpp"
#include "../ecs/Systems/HandleColisionSystem.hpp"
#include <thread>
#include "../protocolHandler/Encoder.hh"
#include "../protocolHandler/Decoder.hh"

#define MAX_FPS 60.0

#define FRAME_TIME_LOGIC 1.0 / 60.0
#define RENDER_FRAME_TIME 1.0 / MAX_FPS


#define CREATE_TEXTURE std::make_shared<RType::TextureComponent>
#define CREATE_ENTITY_TYPE std::make_shared<RType::EntityTypeComponent>
#define CREATE_POS_COMPONENT std::make_shared<RType::PositionComponent>

namespace RType {

    enum Backgrounds{
        PURPLEBG,
        BLUEBG,
        REDBG,
        SATURNBG,
        GREENBG
    };
    class Game {
        public:
            Game(boost::asio::io_context &ioContext, const std::string &host, const std::string &port);
            ~Game();
            void gameLoop();
            const Coordinator &getCoordinator() const;
            bool getGameHasStarted(void) const;
            void connectToServer(void);
        private:
            void loopReceive();
            void createPlayer();
            void createPlayer(long serverId, long posX, long posY);
            void createMobOctopus(long serverId, long posX, long posY);
            void createMobFly(long serverId, long posX, long posY);
            void createMobSpaceShip(long serverId, long posX, long posY);
            void createEffect(long posX, long posY, EntityType type, std::string path, sf::IntRect rect);
            void createBullet(long serverId, long posX, long posY);
            void createWindow();
            void createGameSystem();
            void createParallaxBackground(std::shared_ptr<RType::Entity> window);
            void createParallaxEntity(const std::string &path, const int &posX, const int &posY,
                const int &winMaxX, const int &winMaxY, const int &index, const int &level);
            std::shared_ptr<RType::TextureComponent> getTextureComponent(const std::string &path);
            std::size_t getMaxClientId(void);

            std::mutex _mtx;
            RType::Coordinator _coord;
            RType::Client _client;
            bool _stopLoop;
            std::thread _receipter;
            bool _initConnection;
            std::unordered_map<std::string, std::shared_ptr<RType::TextureComponent>> _texturesMap;

    };
}

std::ostream &operator<<(std::ostream &s, const RType::Game &game);

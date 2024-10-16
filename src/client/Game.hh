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
    /**
     * @brief Client Game Class who manage ECS
     * 
     */
    class Game {
        public:
            /**
             * @brief Construct a new Game object
             * 
             * @param ioContext 
             * @param host 
             * @param port 
             */
            Game(boost::asio::io_context &ioContext, const std::string &host, const std::string &port);
            /**
             * @brief Destroy the Game object
             * 
             */
            ~Game();
            /**
             * @brief Method containing the game loop
             * 
             */
            void gameLoop();
            /**
             * @brief Get the Coordinator object
             * 
             * @return const Coordinator& (ECS Core)
             */
            const Coordinator &getCoordinator() const;
            /**
             * @brief Get the Game Has Started object
             * 
             * @return true if the game has started, false otherwise
             * @return false 
             */
            bool getGameHasStarted(void) const;
            /**
             * @brief Try connection to the server
             * 
             */
            void connectToServer(void);
        private:
            /**
             * @brief Method containing the receive loop for get server message
             * 
             */
            void loopReceive();
            /**
             * @brief Create a Player object
             * 
             */
            void createPlayer();
            void createPlayer(long serverId, long posX, long posY);
            void createMobOctopus(long serverId, long posX, long posY);
            void createMobFly(long serverId, long posX, long posY);
            void createMobSpaceShip(long serverId, long posX, long posY);
            void createEffect(long posX, long posY, EntityType type, std::string path, sf::IntRect rect);
            void createBullet(long serverId, long posX, long posY);
            /**
             * @brief Create a Window object
             * 
             */
            void createWindow();
            /**
             * @brief Create a Game System object
             * 
             */
            void createGameSystem();
            /**
             * @brief Create a Parallax Background object
             * 
             * @param window 
             */
            void createParallaxBackground(std::shared_ptr<RType::Entity> window);
            /**
             * @brief Create a Parallax Entity object
             * 
             * @param path 
             * @param posX 
             * @param posY 
             * @param winMaxX 
             * @param winMaxY 
             * @param index 
             * @param level 
             */
            void createParallaxEntity(const std::string &path, const int &posX, const int &posY,
                const int &winMaxX, const int &winMaxY, const int &index, const int &level);
            /**
             * @brief Get the Texture Component object
             * 
             * @param path 
             * @return std::shared_ptr<RType::TextureComponent> 
             */
            std::shared_ptr<RType::TextureComponent> getTextureComponent(const std::string &path);
            /**
             * @brief Get the Max Client Id object
             * 
             * @return Size_t: Next client id free
             */
            std::size_t getMaxClientId(void);
            /**
             * @brief Mutex who block the coordinator
             * 
             */
            std::mutex _mtx;
            /**
             * @brief Coordinator of ECS
             * 
             */
            RType::Coordinator _coord;
            /**
             * @brief Client who send and receipt message from server
             * 
             */
            RType::Client _client;
            /**
             * @brief Boolean who stop game and receive loop
             * 
             */
            bool _stopLoop;
            /**
             * @brief Thread of receive loop
             * 
             */
            std::thread _receipter;
            /**
             * @brief Boolean who init connection, if the server send a response to the connection message
             * 
             */
            bool _initConnection;
            /**
             * @brief Map of textures already loaded
             * 
             */
            std::unordered_map<std::string, std::shared_ptr<RType::TextureComponent>> _texturesMap;

    };
}
/**
 * @brief Print the game Component with the coordinator
 * 
 * @param s 
 * @param game 
 * @return std::ostream& 
 */
std::ostream &operator<<(std::ostream &s, const RType::Game &game);

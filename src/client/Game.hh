/*
** EPITECH PROJECT, 2024
** rType
** File description:
** Game
*/

#pragma once

#include <SFML/Graphics/Rect.hpp>
#include <unordered_map>
#include <vector>
#include <string>
#include <charconv>
#include <cstdlib>
#include <fstream>
#include <json/json.h>
#include <json/reader.h>
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
#include "../ecs/Components/MappingInputComponent.hh"
#include "../ecs/Components/MenuComponent.hh"
#include "../ecs/Components/ClickEffectComponent.hh"
#include "../ecs/Components/ShootIntervalComponent.hh"
#include "../ecs/Components/DamageComponent.hh"
#include "../ecs/Components/PowerUpComponent.hh"
#include "../ecs/Components/AttackComponent.hh"
#include "../ecs/Components/MusicComponent.hh"
#include "../ecs/Components/ScoreComponent.hh"
#include "../ecs/Components/SoundComponent.hh"
#include "../ecs/Components/SoundBufferComponent.hh"
#include "../ecs/Components/SoundQueueComponent.hh"
#include "../ecs/Components/HoverEffectComponent.hh"
#include "../ecs/Components/AutoUpdateTextComponent.hh"
#include "../ecs/Components/SoundVolumeComponent.hh"

#include "../ecs/Systems/HandleEventSystem.hpp"
#include "../ecs/Systems/HandleClearSystem.hpp"
#include "../ecs/Systems/HandleDrawSystem.hpp"
#include "../ecs/Systems/HandleDrawTextSystem.hpp"
#include "../ecs/Systems/HandleDisplaySystem.hpp"
#include "../ecs/Systems/HandleMoveSystem.hpp"
#include "../ecs/Systems/HandleMoveSpriteSystem.hpp"
#include "../ecs/Systems/HandleAnimationSystem.hpp"
#include "../ecs/Systems/HandlePatternSystem.hpp"
#include "../ecs/Systems/HandleShootSystem.hpp"
#include "../ecs/Systems/HandleBossAttackSystem.hh"
#include "../ecs/Systems/HandleCollisionSystem.hpp"
#include "../ecs/Systems/HandleSoundSystem.hpp"
#include "../ecs/Systems/HandleMusicSystem.hpp"

#include <thread>
#include "../protocolHandler/Encoder.hh"
#include "../protocolHandler/Decoder.hh"

#define MAX_FPS 90.0

#define FRAME_TIME_LOGIC 1.0 / 60.0
#define RENDER_FRAME_TIME 1.0 / MAX_FPS

#define CREATE_TEXTURE std::make_shared<RType::TextureComponent>
#define CREATE_ENTITY_TYPE std::make_shared<RType::EntityTypeComponent>
#define CREATE_POS_COMPONENT std::make_shared<RType::PositionComponent>
#define CREATE_SPRITE_COMPONENT std::make_shared<RType::SpriteComponent>
#define GET_POSITION_X getComponent<RType::PositionComponent>()->getPositionX()
#define GET_POSITION_Y getComponent<RType::PositionComponent>()->getPositionY()
#define GET_RECT_WIDTH getComponent<RType::IntRectComponent>()->getIntRectWidth()
#define GET_RECT_HEIGHT getComponent<RType::IntRectComponent>()->getIntRectHeight()
#define GET_SCALE_X getComponent<RType::ScaleComponent>()->getScaleX()
#define GET_SCALE_Y getComponent<RType::ScaleComponent>()->getScaleY()

#define SET_BUTTON_TYPE(type) getComponent<EntityTypeComponent>()->setButtonType(type)

#define POS_COMPONENT std::shared_ptr<RType::PositionComponent>
#define SCALE_COMPONENT std::shared_ptr<RType::ScaleComponent>
#define RECT_COMPONENT std::shared_ptr<RType::IntRectComponent>
#define TEXTURE_COMPONENT std::shared_ptr<RType::TextureComponent>
#define SOUND_COMPONENT std::shared_ptr<RType::SoundComponent>
#define SOUND_BUFFER_COMPONENT std::shared_ptr<RType::SoundBufferComponent>

#define PUSH_POS_E(x, y) pushComponent(std::make_shared<RType::PositionComponent>(x, y))
#define PUSH_ACTION_E() pushComponent(std::make_shared<RType::ActionComponent>())
#define PUSH_TYPE_E(type) pushComponent(std::make_shared<RType::EntityTypeComponent>(type))
#define PUSH_SCALE_E(x, y) pushComponent(std::make_shared<RType::ScaleComponent>(x, y))
#define PUSH_RECT_E(x, y, w, h) pushComponent(std::make_shared<RType::IntRectComponent>(x, y, w, h))
#define PUSH_TEXTURE_E(path) pushComponent(std::make_shared<RType::TextureComponent>(path))
#define PUSH_HEALTH_E(hp) pushComponent(std::make_shared<RType::HealthComponent>(hp))
#define PUSH_DAMAGE_E(dmg) pushComponent(std::make_shared<RType::DamageComponent>(dmg))
#define PUSH_VELOCITY_E(speed) pushComponent(std::make_shared<RType::VelocityComponent>(speed))
#define PUSH_PATTERN_E(pattern) pushComponent(std::make_shared<RType::DirectionPatternComponent>(pattern))
#define PUSH_CLOCK_E() pushComponent(std::make_shared<RType::ClockComponent>())
#define PUSH_MENU_COMPONENT_E(menu) pushComponent(std::make_shared<RType::MenuComponent>(menu))
#define PUSH_INTERVALSHOOT_E(interval) pushComponent(std::make_shared<RType::ShootIntervalComponent>(interval))
#define PUSH_ATTACK_E() pushComponent(std::make_shared<RType::AttackComponent>())
#define PUSH_SOUND_E(soundBuffer) pushComponent(std::make_shared<RType::SoundComponent>(soundBuffer));

namespace RType {

    /**
     * @brief Backgrounds enum
     *
     */
    enum Backgrounds{
        PURPLEBG,
        BLUEBG,
        REDBG,
        SATURNBG,
        GREENBG
    };

    /**
     * @brief Game class who handle the ecs and the game loop
     *
     */
    class Game {
        public:
            /**
             * @brief Construct a new Game object
             *
             * @param ioContext The boost io_context for asynchronous operations
             * @param host The server host address
             * @param port The server port
             */
            Game(boost::asio::io_context &ioContext, const std::string &host, const std::string &port);

            /**
             * @brief Destroy the Game object
             *
             */
            ~Game();

            /**
             * @brief Main game loop
             *
             */
            void gameLoop();

            /**
             * @brief Get the Coordinator object
             *
             * @return const Coordinator& Reference to the Coordinator
             */
            const Coordinator &getCoordinator() const;

            /**
             * @brief Check if the game has started
             *
             * @return true If the game has started
             * @return false Otherwise
             */
            bool getGameHasStarted() const;

        private:
            /**
             * @brief Connect to the server
             *
             */
            void connectToServer();

            /**
             * @brief Loop to receive messages from the server
             *
             */
            void loopReceive();

            /**
             * @brief Create a player entity
             *
             */
            void createPlayer();

            /**
             * @brief Create sound entities
             *
             */
            void createSound();

            /**
             * @brief Create a game entity with specific parameters
             *
             * @param type The entity type
             * @param posX X-coordinate position
             * @param posY Y-coordinate position
             * @param idToFollow ID of the entity to follow (optional)
             */
            void createEntity(const RType::EntityType &type, const int &posX, const int &posY, const int &idToFollow = -1);

            /**
             * @brief Create a game entity from server data
             *
             * @param serverId The server-assigned entity ID
             * @param type The entity type
             * @param posX X-coordinate position
             * @param posY Y-coordinate position
             * @param idToFollow ID of the entity to follow (optional)
             */
            void createEntity(const long &serverId, const RType::EntityType &type, const int &posX, const int &posY, const int &idToFollow = -1);

            /**
             * @brief Create the game window
             *
             */
            void createWindow();

            /**
             * @brief Create the main menu
             *
             */
            void createMenu();

            /**
             * @brief Create the options menu
             *
             */
            void createOptionMenu();

            /**
             * @brief Create the death menu
             *
             */
            void createDeathMenu();

            /**
             * @brief Create the win menu
             *
             */
            void createWinMenu();

            /**
             * @brief Map input buttons to actions
             *
             * @param mappingInput The mapping input component
             */
            void createMappingInputButton(std::shared_ptr<RType::MappingInputComponent> mappingInput);

            /**
             * @brief Create a button entity
             *
             * @param x X-coordinate position
             * @param y Y-coordinate position
             * @param text The button text
             *
             * @return std::shared_ptr<RType::Entity> The created button entity
             */
            std::shared_ptr<RType::Entity> createButton(int x, int y, std::string text);

            /**
             * @brief Create a button entity with only Y-coordinate
             *
             * @param y Y-coordinate position
             * @param text The button text
             *
             * @return std::shared_ptr<RType::Entity> The created button entity
             */
            std::shared_ptr<RType::Entity> createButton(int y, std::string text);

            /**
             * @brief Create a text entity
             *
             * @param x X-coordinate position
             * @param y Y-coordinate position
             * @param texthe T text content
             *
             * @return std::shared_ptr<RType::Entity> The created text entity
             */
            std::shared_ptr<RType::Entity> createText(int x, int y, std::string text);

            /**
             * @brief Create a text entity with only Y-coordinate
             *
             * @param y Y-coordinate position
             * @param text The text content
             *
             * @return std::shared_ptr<RType::Entity> The created text entity
             */
            std::shared_ptr<RType::Entity> createText(int y, std::string text);

            /**
             * @brief Create a text entity with specified font size
             *
             * @param y Y-coordinate position
             * @param text The text content
             * @param fontSize The font size
             *
             * @return std::shared_ptr<RType::Entity> The created text entity
             */
            std::shared_ptr<RType::Entity> createText(int y, std::string text, std::size_t fontSize);

            /**
             * @brief Create game systems for the ECS
             *
             */
            void createGameSystem();

            /**
             * @brief Create parallax background
             *
             * @param window The window entity
             */
            void createParallaxBackground(std::shared_ptr<RType::Entity> window);

            /**
             * @brief Create a parallax entity with specified parameters
             *
             * @param path The texture path
             * @param posX X-coordinate position
             * @param posY Y-coordinate position
             * @param winMaxX Maximum X-coordinate of the window
             * @param winMaxY Maximum Y-coordinate of the window
             * @param index Parallax layer index
             * @param level Parallax level
             */
            void createParallaxEntity(const std::string &path, const int &posX, const int &posY, const int &winMaxX, const int &winMaxY, const int &index, const int &level);

            /**
             * @brief Get the player entity
             *
             * @return std::shared_ptr<RType::Entity> The player entity
             */
            std::shared_ptr<RType::Entity> getPlayerEntity();

            /**
             * @brief Get a texture component from the path
             *
             * @param path The texture path
             *
             * @return std::shared_ptr<RType::TextureComponent> The texture component
             */
            std::shared_ptr<RType::TextureComponent> getTextureComponent(const std::string &path);

            /**
             * @brief Get a sound buffer component from the path
             *
             * @param path The sound buffer path
             *
             * @return std::shared_ptr<RType::SoundBufferComponent> The sound buffer component
             */
            std::shared_ptr<RType::SoundBufferComponent> getSoundBufferComponent(const std::string &path);

            /**
             * @brief Get the maximum client ID
             *
             * @return std::size_t The maximum client ID
             */
            std::size_t getMaxClientId();

            /**
             * @brief Calculate bullet position
             *
             * @param type The bullet type
             * @param posX X-coordinate of the shooter
             * @param posY Y-coordinate of the shooter
             *
             * @return sf::Vector2f The bullet position
             */
            sf::Vector2f getBulletPosition(int type, int posX, int posY);

            /**
             * @brief Get an entity by server ID
             *
             * @param entities The list of entities
             * @param serverId The server ID
             *
             * @return std::shared_ptr<RType::Entity> The found entity
             */
            std::shared_ptr<RType::Entity> getEntityByServerId(std::vector<std::shared_ptr<RType::Entity>> entities, int serverId);

            /**
             * @brief Try to send a message to the server
             *
             * @param message The message to send
             */
            void trySendMessageToServer(const std::basic_string<unsigned char> &message);

            /**
             * @brief Disconnect from the server
             *
             */
            void disconnexion();

            /**
             * @brief Create the entity type map
             *
             */
            void createEntityMap();


            /**
             * @brief Std::mutex for thread safety
             *
             */
            std::mutex _mtx;

            /**
             * @brief Coordinator for ECS
             *
             */
            RType::Coordinator _coord;

            /**
             * @brief The client for communication
             *
             */
            RType::Client _client;

            /**
             * @brief The bool to stop the game loop
             *
             */
            bool _stopLoop;

            /**
             * @brief The thread to receive messages
             *
             */
            std::thread _receipter;

            /**
             * @brief Bool to check if the connection has been initialized
             *
             */
            bool _initConnection;

            /**
             * @brief Map of textures
             *
             */
            std::unordered_map<std::string, std::shared_ptr<RType::TextureComponent>> _texturesMap;

            /**
             * @brief Map of sound buffers
             *
             */
            std::unordered_map<std::string, std::shared_ptr<RType::SoundBufferComponent>> _soundBufferMap;

            /**
             * @brief Map of entity types
             *
             */
            std::unordered_map<EntityType, std::string> _entityTypeMap;

            /**
             * @brief Sounds entity
             *
             */
            std::shared_ptr<Entity> _soundsEntity;

            /**
             * @brief Font for text
             *
             */
            std::shared_ptr<sf::Font> _font;
    };
}

/**
 * @brief Overload of the << operator to print the game
 *
 * @param s The output stream
 * @param game The game to print
 *
 * @return std::ostream& The output stream
 */
std::ostream &operator<<(std::ostream &s, const RType::Game &game);

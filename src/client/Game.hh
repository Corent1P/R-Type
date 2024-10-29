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
            void createSound();
            void createEntity(const RType::EntityType &type, const int &posX,
                              const int &posY, const int &idToFollow = -1);
            void createEntity(const long &serverId, const RType::EntityType &type,
                              const int &posX, const int &posY, const int &idToFollow = -1);
            void createWindow();
            void createMenu();
            void createDeathMenu();
            void createWinMenu();
            void createMappingInputButton(std::shared_ptr<RType::MappingInputComponent> mappingInput);
            std::shared_ptr<RType::Entity> createButton(int x, int y, std::string text);
            std::shared_ptr<RType::Entity> createButton(int y, std::string text);
            std::shared_ptr<RType::Entity> createText(int x, int y, std::string text);
            std::shared_ptr<RType::Entity> createText(int y, std::string text);
            void createGameSystem();
            void createParallaxBackground(std::shared_ptr<RType::Entity> window);
            void createParallaxEntity(const std::string &path, const int &posX, const int &posY,
                const int &winMaxX, const int &winMaxY, const int &index, const int &level);
            std::shared_ptr<RType::Entity> getPlayerEntity(void);

            std::shared_ptr<RType::TextureComponent> getTextureComponent(const std::string &path);
            std::shared_ptr<RType::SoundBufferComponent> getSoundBufferComponent(const std::string &path);

            std::size_t getMaxClientId(void);

            sf::Vector2f getBulletPosition(int type, int posX, int posY);

            std::shared_ptr<RType::Entity> getEntityByServerId(std::vector<std::shared_ptr<RType::Entity>> entities, int serverId);

            void trySendMessageToServer(const std::basic_string<unsigned char> &message);
            void disconnexion(void);
            void createEntityMap(void);

            std::mutex _mtx;
            RType::Coordinator _coord;
            RType::Client _client;
            bool _stopLoop;
            std::thread _receipter;
            bool _initConnection;
            std::unordered_map<std::string, std::shared_ptr<RType::TextureComponent>> _texturesMap;
            std::unordered_map<std::string, std::shared_ptr<RType::SoundBufferComponent>> _soundBufferMap;
            std::unordered_map<EntityType, std::string> _entityTypeMap;
            std::shared_ptr<Entity> _soundsEntity;
            std::shared_ptr<sf::Font> _font;
    };
}

std::ostream &operator<<(std::ostream &s, const RType::Game &game);

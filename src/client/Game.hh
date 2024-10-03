/*
** EPITECH PROJECT, 2024
** rType
** File description:
** Game
*/

#pragma once

#include <unordered_map>
#include <vector>
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
#include "../ecs/Components/VelocityComponent.hh"

#include "../ecs/Systems/HandleEventSystem.hpp"
#include "../ecs/Systems/HandleDrawSystem.hpp"
#include "../ecs/Systems/HandleMoveSystem.hpp"
#include "../ecs/Systems/HandleAnimationSystem.hpp"

#define CREATE_TEXTURE std::make_shared<RType::TextureComponent>
#define CREATE_ENTITY_TYPE std::make_shared<RType::EntityTypeComponent>
#define CREATE_POS_COMPONENT std::make_shared<RType::PositionComponent>

namespace RType {

    enum Backgrounds{
        REDBG,
        BLUEBG,
        PURPLEBG,
        BROWNBG,
        GREENBG,
        SATURNBG
    };
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
            void createParallaxBackground(std::shared_ptr<RType::Entity> window);
            void createParallaxEntity(const std::string &path, const int &posX, const int &posY, const int &winMaxX,const int &winMaxY,const int &index);
            void handleShot();
            RType::Coordinator _coord;
            bool _stopLoop;
    };
}

std::ostream &operator<<(std::ostream &s, const RType::Game &game);

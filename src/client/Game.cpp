/*
** EPITECH PROJECT, 2024
** rType
** File description:
** Game
*/

#include "Game.hh"

RType::Game::Game()
{
    createPlayer();
    createWindow();
    createGameSystem();
    _stopLoop = false;
}

RType::Game::~Game()
{
}

RType::Coordinator RType::Game::getCoordinator() const
{
	return _coord;
}

void RType::Game::gameLoop()
{
    while (!_stopLoop) {
        for (auto sys: _coord.getSystems()) {
            sys->effect(_coord.getEntities());
        }
        for (auto entity : _coord.getEntities()) {
            if (entity->getComponent<RType::SFWindowComponent>() != nullptr) {
                if (entity->getComponent<RType::SFWindowComponent>()->getIsOpen() == false) {
                    _stopLoop = true;
                }
            }
        }
    }
}

void RType::Game::createPlayer()
{
    std::shared_ptr<RType::Entity> player = _coord.generateNewEntity();

    player->pushComponent(std::make_shared<RType::EntityTypeComponent>(RType::PLAYER));
    player->pushComponent(std::make_shared<RType::PositionComponent>(10, 10));
    player->pushComponent(std::make_shared<RType::HealthComponent>(25));
    player->pushComponent(std::make_shared<RType::TextureComponent>("./ressources/player.png"));
}

void RType::Game::createWindow()
{
    std::shared_ptr<RType::Entity> window = _coord.generateNewEntity();

    window->pushComponent(std::make_shared<RType::EntityTypeComponent>(RType::WINDOW));
    window->pushComponent(std::make_shared<RType::SFWindowComponent>(1920, 1080));
    window->pushComponent(std::make_shared<RType::EventComponent>());
}

void RType::Game::createMob()
{
    std::shared_ptr<RType::Entity> player = _coord.generateNewEntity();

    player->pushComponent(std::make_shared<RType::EntityTypeComponent>(RType::MOB));
    player->pushComponent(std::make_shared<RType::PositionComponent>(2000, 800));
    player->pushComponent(std::make_shared<RType::HealthComponent>(5));
}

void RType::Game::createBoss()
{
    std::shared_ptr<RType::Entity> player = _coord.generateNewEntity();

    player->pushComponent(std::make_shared<RType::EntityTypeComponent>(RType::BOSS));
    player->pushComponent(std::make_shared<RType::PositionComponent>(2000, 545));
    player->pushComponent(std::make_shared<RType::HealthComponent>(250));
}

void RType::Game::createGameSystem()
{
    _coord.generateNewSystem(std::make_shared<HandleEventSystem>());
}

std::ostream &operator<<(std::ostream &s, const RType::Game &game)
{
    s << game.getCoordinator();
    return s;
}

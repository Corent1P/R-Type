/*
** EPITECH PROJECT, 2024
** rType
** File description:
** Game
*/

#include "Game.hh"

RType::Game::Game(boost::asio::io_context &ioContext, const std::string &host, const std::string &port)
{
    _client = std::make_shared<RType::Client> (ioContext, host, port);
    createWindow();
    createPlayer();
    createMob();
    createGameSystem();
    _stopLoop = false;
    _client->send("Hello world");
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
            sys->effects(_coord.getEntities());
        }
        for (auto entity : _coord.getEntities()) {
            if (entity->getComponent<RType::SFWindowComponent>() && !entity->getComponent<RType::SFWindowComponent>()->getIsOpen()) {
                _stopLoop = true;
            }
        }
    }
}

void RType::Game::createPlayer()
{
    std::shared_ptr<RType::Entity> player = _coord.generateNewEntity();

    player->pushComponent(std::make_shared<RType::EntityTypeComponent>(RType::PLAYER));
    std::shared_ptr<RType::PositionComponent> position = player->pushComponent(std::make_shared<RType::PositionComponent>(10, 10));
    player->pushComponent(std::make_shared<RType::HealthComponent>(25));
    std::shared_ptr<RType::TextureComponent> texture = player->pushComponent(std::make_shared<RType::TextureComponent>("./ressources/player-sheet.png"));

    player->pushComponent(std::make_shared<RType::SpriteComponent>(texture->getTexture(), position->getPositions(), sf::Vector2f(2, 2), sf::IntRect(0, 0, 26, 21)));
    player->pushComponent(std::make_shared<RType::DirectionComponent>());
    player->pushComponent(std::make_shared<RType::ClockComponent>());
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

    std::shared_ptr<RType::PositionComponent> position = player->pushComponent(std::make_shared<RType::PositionComponent>(500, 500));
    std::shared_ptr<RType::TextureComponent> texture = player->pushComponent(std::make_shared<RType::TextureComponent>("./ressources/enemy-sheet.png"));
    player->pushComponent(std::make_shared<RType::SpriteComponent>(texture->getTexture(), position->getPositions(), sf::Vector2f(2, 2), sf::IntRect(0, 0, 29, 29)));
    player->pushComponent(std::make_shared<RType::DirectionComponent>());
    player->pushComponent(std::make_shared<RType::ClockComponent>());

    std::shared_ptr<RType::Entity> player2 = _coord.generateNewEntity();

    player2->pushComponent(std::make_shared<RType::EntityTypeComponent>(RType::MOB));
    player2->pushComponent(std::make_shared<RType::PositionComponent>(2000, 800));
    player2->pushComponent(std::make_shared<RType::HealthComponent>(5));

    std::shared_ptr<RType::PositionComponent> position2 = player2->pushComponent(std::make_shared<RType::PositionComponent>(300, 700));
    std::shared_ptr<RType::TextureComponent> texture2 = player2->pushComponent(std::make_shared<RType::TextureComponent>("./ressources/fly-sheet.png"));
    player2->pushComponent(std::make_shared<RType::SpriteComponent>(texture2->getTexture(), position2->getPositions(), sf::Vector2f(2, 2), sf::IntRect(0, 0, 65, 74)));
    player2->pushComponent(std::make_shared<RType::DirectionComponent>());
    player2->pushComponent(std::make_shared<RType::ClockComponent>());
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
    _coord.generateNewSystem(std::make_shared<HandleEventSystem>(_client));
    _coord.generateNewSystem(std::make_shared<HandleDrawSystem>());
    _coord.generateNewSystem(std::make_shared<HandleMoveSystem>());
    _coord.generateNewSystem(std::make_shared<HandleAnimationSystem>());
}

std::ostream &operator<<(std::ostream &s, const RType::Game &game)
{
    s << game.getCoordinator();
    return s;
}

/*
** EPITECH PROJECT, 2024
** rType
** File description:
** Game
*/

#include "Game.hh"

RType::Game::Game()
{
    createWindow();
    createPlayer();
    createMob();
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
    createParallaxBackground(window);
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
    _coord.generateNewSystem(std::make_shared<HandleEventSystem>());
    _coord.generateNewSystem(std::make_shared<HandleDrawSystem>());
    _coord.generateNewSystem(std::make_shared<HandleMoveSystem>());
    _coord.generateNewSystem(std::make_shared<HandleAnimationSystem>());
}

void RType::Game::createParallaxBackground(std::shared_ptr<RType::Entity> window)
{
    std::vector<std::shared_ptr<RType::Entity>> backgrounds;
    std::shared_ptr<RType::TextureComponent> texture;
    float winMaxX = window->getComponent<RType::SFWindowComponent>()->getWindow()->getSize().x;
    float winMaxY = window->getComponent<RType::SFWindowComponent>()->getWindow()->getSize().y;
    float spriteHeight = 0.;
    float spriteWidth = 0.;
    std::shared_ptr<RType::PositionComponent> position;
    std::unordered_map<Backgrounds, std::vector<std::string>> bgMap =
    {
        // {Backgrounds::REDBG, 6},
        // {Backgrounds::BLUEBG, 3},
        {Backgrounds::PURPLEBG, {"./ressources/parallax/purple/back.png", "./ressources/parallax/purple/front.png"}}
        // {Backgrounds::BROWNBG, 6},
        // {Backgrounds::GREENBG, 4}
    };
    backgrounds.resize(bgMap[Backgrounds::PURPLEBG].size());
    for (std::size_t i = 0; i < bgMap[Backgrounds::PURPLEBG].size(); i++) {
        backgrounds[i] = _coord.generateNewEntity();
        texture = backgrounds[i]->pushComponent(CREATE_TEXTURE(bgMap[Backgrounds::PURPLEBG][i]));
        position = backgrounds[i]->pushComponent(CREATE_POS_COMPONENT(0, 0));
        backgrounds[i]->pushComponent(CREATE_ENTITY_TYPE(RType::LAYER));
        backgrounds[i]->pushComponent(std::make_shared<RType::SpriteComponent>(texture->getTexture(),
            position->getPositions()));
        spriteWidth = backgrounds[i]->getComponent<RType::SpriteComponent>()->getSprite()->getGlobalBounds().width;
        spriteHeight = backgrounds[i]->getComponent<RType::SpriteComponent>()->getSprite()->getGlobalBounds().height;
        backgrounds[i]->getComponent<SpriteComponent>()->getSprite()->setScale(sf::Vector2f(1920 / 272, 1080 / 160));
    }
}

std::ostream &operator<<(std::ostream &s, const RType::Game &game)
{
    s << game.getCoordinator();
    return s;
}

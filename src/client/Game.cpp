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
            handleShot();
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
    std::shared_ptr<RType::PositionComponent> position = player->pushComponent(std::make_shared<RType::PositionComponent>(50, 50));
    player->pushComponent(std::make_shared<RType::HealthComponent>(25));
    std::shared_ptr<RType::TextureComponent> texture = player->pushComponent(std::make_shared<RType::TextureComponent>("./ressources/player-sheet.png"));

    player->pushComponent(std::make_shared<RType::SpriteComponent>(texture->getTexture(), position->getPositions(), sf::Vector2f(2, 2), sf::IntRect(0, 0, 26, 21)));
    player->pushComponent(std::make_shared<RType::DirectionComponent>());
    player->pushComponent(std::make_shared<RType::ClockComponent>());
    player->pushComponent(std::make_shared<RType::ActionComponent>());
    player->pushComponent(std::make_shared<VelocityComponent>(10));
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
    player->pushComponent(std::make_shared<VelocityComponent>(5));

    std::shared_ptr<RType::Entity> player2 = _coord.generateNewEntity();

    player2->pushComponent(std::make_shared<RType::EntityTypeComponent>(RType::MOB));
    player2->pushComponent(std::make_shared<RType::PositionComponent>(2000, 800));
    player2->pushComponent(std::make_shared<RType::HealthComponent>(5));

    std::shared_ptr<RType::PositionComponent> position2 = player2->pushComponent(std::make_shared<RType::PositionComponent>(300, 700));
    std::shared_ptr<RType::TextureComponent> texture2 = player2->pushComponent(std::make_shared<RType::TextureComponent>("./ressources/fly-sheet.png"));
    player2->pushComponent(std::make_shared<RType::SpriteComponent>(texture2->getTexture(), position2->getPositions(), sf::Vector2f(2, 2), sf::IntRect(0, 0, 65, 74)));
    player2->pushComponent(std::make_shared<RType::DirectionComponent>());
    player2->pushComponent(std::make_shared<RType::ClockComponent>());
    player2->pushComponent(std::make_shared<VelocityComponent>(5));
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
    std::shared_ptr<RType::Entity> backgrounds;
    std::shared_ptr<RType::TextureComponent> texture;
    float winMaxX = window->getComponent<RType::SFWindowComponent>()->getWindow()->getSize().x;
    float winMaxY = window->getComponent<RType::SFWindowComponent>()->getWindow()->getSize().y;
    std::shared_ptr<RType::PositionComponent> position;
    std::unordered_map<Backgrounds, std::vector<std::string>> bgMap =
    {
        // {Backgrounds::REDBG, 6},
        {Backgrounds::BLUEBG, {"./ressources/parallax/blue/back.png", "./ressources/parallax/blue/mid.png", "./ressources/parallax/blue/front.png"}},
        {Backgrounds::PURPLEBG, {"./ressources/parallax/purple/back.png", "./ressources/parallax/purple/front.png"}},
        // {Backgrounds::BROWNBG, 6},
        {Backgrounds::GREENBG, {"./ressources/parallax/green/back.png", "./ressources/parallax/green/mid.png", "./ressources/parallax/green/front.png"}}
    };
    for (std::size_t i = 0; i < bgMap[Backgrounds::GREENBG].size(); i++) {
        createParallaxEntity(bgMap[Backgrounds::GREENBG][i], 0, 0, winMaxX, winMaxY, i);
        createParallaxEntity(bgMap[Backgrounds::GREENBG][i], winMaxX, 0, winMaxX, winMaxY, i);
    }
}

void RType::Game::createParallaxEntity(const std::string &path, const int &posX, const int &posY, const int &winMaxX,const int &winMaxY, const int &index)
{
    std::shared_ptr<RType::Entity> backgrounds = _coord.generateNewEntity();
    std::shared_ptr<RType::TextureComponent> texture = backgrounds->pushComponent(CREATE_TEXTURE(path));
    std::shared_ptr<RType::PositionComponent> position = backgrounds->pushComponent(CREATE_POS_COMPONENT(posX, posY));
    float spriteHeight = 0.;
    float spriteWidth = 0.;

    backgrounds->pushComponent(CREATE_ENTITY_TYPE(RType::LAYER));
    backgrounds->pushComponent(std::make_shared<SpriteComponent>(texture->getTexture(),
        position->getPositions()));
    spriteWidth = backgrounds->getComponent<TextureComponent>()->getTexture()->getSize().x;
    spriteHeight = backgrounds->getComponent<TextureComponent>()->getTexture()->getSize().y;
    backgrounds->getComponent<SpriteComponent>()->getSprite()->setScale(sf::Vector2f(float(winMaxX / spriteWidth), float(winMaxY / spriteHeight)));
    auto dir = backgrounds->pushComponent(std::make_shared<RType::DirectionComponent>());
    dir->setDirections(LEFT, true);
    backgrounds->pushComponent(std::make_shared<VelocityComponent>(index + 1));
}

void  RType::Game::handleShot()
{
    for (const auto &entities : _coord.getEntities()) {
        if (entities->getComponent<RType::ActionComponent>() != nullptr
        && entities->getComponent<RType::SpriteComponent>() != nullptr) {
            if (entities->getComponent<RType::ActionComponent>()->getActions(RType::SHOOTING) == true) {
                std::cout << "New shot!" << std::endl;
                entities->getComponent<RType::ActionComponent>()->setActions(RType::SHOOTING, false);
                std::shared_ptr<RType::Entity> shot = _coord.generateNewEntity();

                shot->pushComponent(std::make_shared<RType::EntityTypeComponent>(RType::WEAPON));
                std::shared_ptr<RType::PositionComponent> position = shot->pushComponent(std::make_shared<RType::PositionComponent>(entities->getComponent<SpriteComponent>()->getSprite()->getPosition().x, entities->getComponent<SpriteComponent>()->getSprite()->getPosition().y));
                std::shared_ptr<RType::TextureComponent> texture = shot->pushComponent(std::make_shared<RType::TextureComponent>("./ressources/shoot-spritesheet.png"));
                shot->pushComponent(std::make_shared<RType::SpriteComponent>(texture->getTexture(), position->getPositions(), sf::Vector2f(2, 2), sf::IntRect(0, 0, 19, 6)));
                shot->pushComponent(std::make_shared<RType::DirectionComponent>(RType::RIGHT));
                shot->getComponent<RType::DirectionComponent>()->setDirections(RIGHT, true);
                shot->pushComponent(std::make_shared<RType::ClockComponent>());
                shot->pushComponent(std::make_shared<VelocityComponent>(20));
            }
        }
    }
}

std::ostream &operator<<(std::ostream &s, const RType::Game &game)
{
    s << game.getCoordinator();
    return s;
}

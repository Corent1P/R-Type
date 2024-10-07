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
    _client->send(Encoder::connexion());
    createWindow();
    createPlayer();
    createGameSystem();
    _stopLoop = false;
    _receipter = std::jthread(&Game::loopReceive, this);
    _initConnection = false;
}

RType::Game::~Game()
{
    _client->send(Encoder::disconnexion());
    if (_receipter.joinable()) {
        _receipter.join();
    }
}

RType::Coordinator RType::Game::getCoordinator() const
{
	return _coord;
}

void RType::Game::gameLoop()
{
    std::shared_ptr<RType::ISystem> drawSystem = nullptr;
    std::shared_ptr<RType::Entity> clockEntity = nullptr;
    float logicTime = 0.0;
    float renderTime = 0.0;
    float deltaTime = 0.0;

    for (auto sys : _coord.getSystems()) {
        if (sys->getType() == SystemType::S_DRAW) {
            drawSystem = sys;
            break;
        }
    }

    for (auto entity: _coord.getEntities()) {
        if (entity->getComponent<RType::SFWindowComponent>() != nullptr && entity->getComponent<RType::ClockComponent>() != nullptr) {
            clockEntity = entity;
            break;
        }
    }

    while (!_stopLoop) {
        deltaTime = clockEntity->getComponent<RType::ClockComponent>()->getClock(LOGIC_CLOCK).restart().asSeconds();
        logicTime += deltaTime;
        while (logicTime >= FRAME_TIME_LOGIC) {
            for (auto sys : _coord.getSystems())
                if (sys->getType() != SystemType::S_DRAW)
                    sys->effects(_coord.getEntities());
            logicTime -= FRAME_TIME_LOGIC;
        }

        renderTime += deltaTime;
        if (renderTime >= RENDER_FRAME_TIME) {
            if (drawSystem != nullptr) {
                drawSystem->effects(_coord.getEntities());
            }
            renderTime = 0.0;
        }

        for (auto entity : _coord.getEntities()) {
            auto windowComp = entity->getComponent<RType::SFWindowComponent>();

            if (windowComp != nullptr && !windowComp->getIsOpen()) {
                _client->cancel();
                _stopLoop = true;
                break;
            }
        }
    }
}

void RType::Game::loopReceive()
{
    while (!_stopLoop) {
        std::basic_string<unsigned char> command = _client->receive();
        auto receivInfo = Decoder::getCommandInfo(command);
        if (receivInfo.first == MOVE_PLAYER)
            std::cout << "Message received = " << receivInfo.first << " move with coordinates " << receivInfo.second[0] << ":" << receivInfo.second[1] << std::endl;

        if (receivInfo.first == NEW_ENTITY) {
            if (_initConnection) {
                if (receivInfo.second[0] == E_PLAYER)
                    createPlayer(receivInfo.second[1], receivInfo.second[2], receivInfo.second[3]);
                if (receivInfo.second[0] == E_MOB)
                    createMob(receivInfo.second[1], receivInfo.second[2], receivInfo.second[3]);
            } else {
                _initConnection = true;
                auto entities = _coord.getEntities();
                for (const auto &entity : entities) {
                    if (entity->getComponent<RType::EntityTypeComponent>()->getEntityType() == E_PLAYER)
                        entity->setServerId(receivInfo.second[1]);
                }
            }
        }
        if (receivInfo.first == DELETE_ENTITY) {
            auto entities = _coord.getEntities();
            for (const auto &entity : entities) {
                if (entity->getServerId() == receivInfo.second[0]) {
                    _coord.deleteEntity(entity);
                    std::cout << "deleteEntity" << std::endl;
                }
            }
        }
        if (receivInfo.first == MOVE_ENTITY) {
            auto entities = _coord.getEntities();
            for (const auto &entity : entities) {
                if (entity->getServerId() == receivInfo.second[0]) {
                    entity->getComponent<RType::PositionComponent>()->setPositions(receivInfo.second[1], receivInfo.second[2]);
                    entity->getComponent<RType::SpriteComponent>()->getSprite()->setPosition(receivInfo.second[1], receivInfo.second[2]);
                }
            }
        }
    }
}

void RType::Game::createPlayer()
{
    std::shared_ptr<RType::Entity> player = _coord.generateNewEntity();

    player->pushComponent(std::make_shared<RType::EntityTypeComponent>(RType::E_PLAYER));
    std::shared_ptr<RType::PositionComponent> position = player->pushComponent(std::make_shared<RType::PositionComponent>(10, 10));
    player->pushComponent(std::make_shared<RType::HealthComponent>(25));
    std::shared_ptr<RType::TextureComponent> texture = player->pushComponent(std::make_shared<RType::TextureComponent>("./ressources/player-sheet.png"));

    player->pushComponent(std::make_shared<RType::SpriteComponent>(texture->getTexture(), position->getPositions(), sf::Vector2f(2, 2), sf::IntRect(0, 0, 26, 21)));
    player->pushComponent(std::make_shared<RType::DirectionComponent>());
    player->pushComponent(std::make_shared<RType::ClockComponent>());
    player->pushComponent(std::make_shared<RType::ActionComponent>());
    player->pushComponent(std::make_shared<VelocityComponent>(10));
}

void RType::Game::createPlayer(long serverId, long posX, long posY)
{
    std::shared_ptr<RType::Entity> player = _coord.generateNewEntity(serverId);

    player->pushComponent(std::make_shared<RType::EntityTypeComponent>(RType::E_ALLIES));
    std::shared_ptr<RType::PositionComponent> position = player->pushComponent(std::make_shared<RType::PositionComponent>(posX, posY));
    player->pushComponent(std::make_shared<RType::HealthComponent>(25));
    std::shared_ptr<RType::TextureComponent> texture = player->pushComponent(std::make_shared<RType::TextureComponent>("./ressources/player-sheet.png"));

    player->pushComponent(std::make_shared<RType::SpriteComponent>(texture->getTexture(), position->getPositions(), sf::Vector2f(2, 2), sf::IntRect(0, 0, 26, 21)));
    player->pushComponent(std::make_shared<RType::DirectionComponent>());
    player->pushComponent(std::make_shared<RType::ClockComponent>());
}

void RType::Game::createWindow()
{
    std::shared_ptr<RType::Entity> window = _coord.generateNewEntity();

    window->pushComponent(std::make_shared<RType::EntityTypeComponent>(RType::E_WINDOW));
    window->pushComponent(std::make_shared<RType::SFWindowComponent>(1920, 1080));
    window->pushComponent(std::make_shared<RType::EventComponent>());
    window->pushComponent(std::make_shared<RType::ClockComponent>());
    createParallaxBackground(window);
}

void RType::Game::createMob()
{
    std::shared_ptr<RType::Entity> mob = _coord.generateNewEntity();

    mob->pushComponent(std::make_shared<RType::EntityTypeComponent>(RType::E_MOB));
    auto position = mob->pushComponent(std::make_shared<RType::PositionComponent>(2000, 800));
    mob->pushComponent(std::make_shared<RType::HealthComponent>(5));

    std::shared_ptr<RType::TextureComponent> texture = mob->pushComponent(std::make_shared<RType::TextureComponent>("./ressources/enemy-sheet.png"));
    mob->pushComponent(std::make_shared<RType::SpriteComponent>(texture->getTexture(), position->getPositions(), sf::Vector2f(2, 2), sf::IntRect(0, 0, 29, 29)));
    mob->pushComponent(std::make_shared<RType::ClockComponent>());
    mob->pushComponent(std::make_shared<RType::DirectionPatternComponent>(UP_N_DOWN_LEFT));
    mob->pushComponent(std::make_shared<VelocityComponent>(2));
}

void RType::Game::createMob(long serverId, long posX, long posY)
{
    std::shared_ptr<RType::Entity> mob = _coord.generateNewEntity(serverId);

    mob->pushComponent(std::make_shared<RType::EntityTypeComponent>(RType::E_MOB));
    mob->pushComponent(std::make_shared<RType::HealthComponent>(5));

    std::shared_ptr<RType::PositionComponent> position = mob->pushComponent(std::make_shared<RType::PositionComponent>(posX, posY));
    std::shared_ptr<RType::TextureComponent> texture = mob->pushComponent(std::make_shared<RType::TextureComponent>("./ressources/enemy-sheet.png"));
    mob->pushComponent(std::make_shared<RType::SpriteComponent>(texture->getTexture(), position->getPositions(), sf::Vector2f(2, 2), sf::IntRect(0, 0, 29, 29)));
    mob->pushComponent(std::make_shared<RType::DirectionPatternComponent>(UP_N_DOWN_LEFT));
    mob->pushComponent(std::make_shared<VelocityComponent>(2));
}

void RType::Game::createBoss()
{
    std::shared_ptr<RType::Entity> player = _coord.generateNewEntity();

    player->pushComponent(std::make_shared<RType::EntityTypeComponent>(RType::E_BOSS));
    player->pushComponent(std::make_shared<RType::PositionComponent>(2000, 545));
    player->pushComponent(std::make_shared<RType::HealthComponent>(250));
}

void RType::Game::createGameSystem()
{
    _coord.generateNewSystem(std::make_shared<HandleEventSystem>(
        std::bind(&RType::Coordinator::addEntity, &_coord),
        std::bind(&RType::Coordinator::deleteEntity, &_coord, std::placeholders::_1)
    ));

    _coord.generateNewSystem(std::make_shared<HandleDrawSystem>(
        std::bind(&RType::Coordinator::addEntity, &_coord),
        std::bind(&RType::Coordinator::deleteEntity, &_coord, std::placeholders::_1)
    ));

    _coord.generateNewSystem(std::make_shared<HandleMoveSystem>(
        std::bind(&RType::Coordinator::addEntity, &_coord),
        std::bind(&RType::Coordinator::deleteEntity, &_coord, std::placeholders::_1),
        _client
    ));

    _coord.generateNewSystem(std::make_shared<HandlePatternSystem>(
        std::bind(&RType::Coordinator::addEntity, &_coord),
        std::bind(&RType::Coordinator::deleteEntity, &_coord, std::placeholders::_1)
    ));

    _coord.generateNewSystem(std::make_shared<HandleAnimationSystem>(
        std::bind(&RType::Coordinator::addEntity, &_coord),
        std::bind(&RType::Coordinator::deleteEntity, &_coord, std::placeholders::_1)
    ));

    _coord.generateNewSystem(std::make_shared<HandleShootSystem>(
        std::bind(&RType::Coordinator::addEntity, &_coord),
        std::bind(&RType::Coordinator::deleteEntity, &_coord, std::placeholders::_1)
    ));
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
        {Backgrounds::PURPLEBG, {"./ressources/parallax/purple/back.png", "./ressources/parallax/purple/front.png"}},
        {Backgrounds::BLUEBG, {"./ressources/parallax/blue/back.png", "./ressources/parallax/blue/mid.png", "./ressources/parallax/blue/front.png"}},
        {Backgrounds::REDBG, {"./ressources/parallax/red/back.png", "./ressources/parallax/red/stars.png", "./ressources/parallax/red/mid.png", "./ressources/parallax/red/front.png"}},
        {Backgrounds::SATURNBG, {"./ressources/parallax/saturn/back.png", "./ressources/parallax/blue/mid.png", "./ressources/parallax/saturn/front.png"}},
        // {Backgrounds::BROWNBG, 6},
        {Backgrounds::GREENBG, {"./ressources/parallax/green/back.png", "./ressources/parallax/green/mid.png", "./ressources/parallax/green/front.png"}}
    };
    for (std::size_t i = 0; i < bgMap.size(); i++) {
        for (std::size_t j = 0; j < bgMap[static_cast<Backgrounds>(i)].size(); j++) {
            createParallaxEntity(bgMap[static_cast<Backgrounds>(i)][j], 0, 0, winMaxX, winMaxY, j, i + 1);
            createParallaxEntity(bgMap[static_cast<Backgrounds>(i)][j], winMaxX, 0, winMaxX, winMaxY, j, i + 1);
        }
    }
}

void RType::Game::createParallaxEntity(const std::string &path, const int &posX, const int &posY,
    const int &winMaxX,const int &winMaxY, const int &index, const int &level)
{
    std::shared_ptr<RType::Entity> backgrounds = _coord.generateNewEntity();
    std::shared_ptr<RType::TextureComponent> texture = backgrounds->pushComponent(CREATE_TEXTURE(path));
    std::shared_ptr<RType::PositionComponent> position = backgrounds->pushComponent(CREATE_POS_COMPONENT(posX, posY));
    float spriteHeight = 0.;
    float spriteWidth = 0.;

    backgrounds->pushComponent(CREATE_ENTITY_TYPE(RType::E_LAYER));
    backgrounds->pushComponent(std::make_shared<SpriteComponent>(texture->getTexture(),
        position->getPositions()));
    spriteWidth = backgrounds->getComponent<TextureComponent>()->getTexture()->getSize().x;
    spriteHeight = backgrounds->getComponent<TextureComponent>()->getTexture()->getSize().y;
    backgrounds->getComponent<SpriteComponent>()->getSprite()->setScale(sf::Vector2f(float(winMaxX / spriteWidth), float(winMaxY / spriteHeight)));
    backgrounds->pushComponent(std::make_shared<RType::DirectionPatternComponent>(STRAIGHT_LEFT));
    backgrounds->pushComponent(std::make_shared<VelocityComponent>((index + 1)));
    backgrounds->pushComponent(std::make_shared<LevelComponent>(level));
}

std::ostream &operator<<(std::ostream &s, const RType::Game &game)
{
    s << game.getCoordinator();
    return s;
}

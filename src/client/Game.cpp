/*
** EPITECH PROJECT, 2024
** rType
** File description:
** Game
*/

#include "Game.hh"

RType::Game::Game(boost::asio::io_context &ioContext, const std::string &host, const std::string &port):
    _client(ioContext, host, port)
{
    createWindow();
    createPlayer();
    createGameSystem();
    _stopLoop = false;
    _receipter = std::thread(&Game::loopReceive, this);
    _initConnection = false;
}

RType::Game::~Game()
{
    _client.send(Encoder::disconnexion());
    if (_receipter.joinable()) {
        _receipter.join();
    }
}

const RType::Coordinator &RType::Game::getCoordinator() const
{
	return _coord;
}

void RType::Game::gameLoop()
{
    std::shared_ptr<RType::ISystem> drawSystem = nullptr;
    std::shared_ptr<RType::Entity> clockEntity = nullptr;
    std::shared_ptr<RType::SFWindowComponent> windowComponent = nullptr;
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
            windowComponent = entity->getComponent<RType::SFWindowComponent>();
            break;
        }
    }

    while (!_stopLoop && clockEntity && clockEntity->getComponent<RType::ClockComponent>()) {
        deltaTime = clockEntity->getComponent<RType::ClockComponent>()->getClock(LOGIC_CLOCK).restart().asSeconds();
        logicTime += deltaTime;
        while (logicTime >= FRAME_TIME_LOGIC) {
            std::unique_lock<std::mutex> lock(_mtx);
            for (auto sys : _coord.getSystems())
                if (sys->getType() != SystemType::S_DRAW)
                    sys->effects(_coord.getEntities());
            logicTime -= FRAME_TIME_LOGIC;
        }

        renderTime += deltaTime;
        if (renderTime >= RENDER_FRAME_TIME) {
            if (drawSystem != nullptr) {
                std::unique_lock<std::mutex> lock(_mtx);
                drawSystem->effects(_coord.getEntities());
            }
            renderTime = 0.0;
            std::unique_lock<std::mutex> lock(_mtx);
            if (windowComponent != nullptr && !windowComponent->getIsOpen()) {
                _client.cancel();
                _stopLoop = true;
                break;
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }
}

void RType::Game::loopReceive()
{
    while (!_stopLoop) {
        std::basic_string<unsigned char> command = _client.receive();
        auto receivInfo = Decoder::getCommandInfo(command);
        if (receivInfo.first == MOVE_PLAYER)
            std::cout << "Message received = " << receivInfo.first << " move with coordinates " << receivInfo.second[0] << ":" << receivInfo.second[1] << std::endl;

        if (receivInfo.first == NEW_ENTITY) {
            if (_initConnection) {
                std::unique_lock<std::mutex> lock(_mtx);

                if (receivInfo.second[0] == E_PLAYER)
                    createPlayer(receivInfo.second[1], static_cast<short>(receivInfo.second[2]), static_cast<short> (receivInfo.second[3]));
                if (receivInfo.second[0] == E_OCTOPUS)
                    createMobOctopus(receivInfo.second[1], static_cast<short> (receivInfo.second[2]), static_cast<short> (receivInfo.second[3]));
                if (receivInfo.second[0] == E_SMALL_SPACESHIP)
                    createMobSpaceShip(receivInfo.second[1], static_cast<short> (receivInfo.second[2]), static_cast<short> (receivInfo.second[3]));
                if (receivInfo.second[0] == E_FLY)
                    createMobFly(receivInfo.second[1], static_cast<short> (receivInfo.second[2]), static_cast<short> (receivInfo.second[3]));
                if (receivInfo.second[0] == E_BULLET) {
                    createBullet(receivInfo.second[1], static_cast<short> (receivInfo.second[2]), static_cast<short> (receivInfo.second[3]));
                    createEffect(static_cast<short> (receivInfo.second[2]), static_cast<short> (receivInfo.second[3]),  RType::E_BULLET_EFFECT, "./ressources/effects/flash.png", sf::IntRect(0, 0, 11, 19));
                }
            } else {
                if (receivInfo.second[0] != E_PLAYER)
                    continue;
                std::unique_lock<std::mutex> lock(_mtx);
                _initConnection = true;
                auto entities = _coord.getEntities();
                for (const auto &entity : entities) {
                    if (entity->getComponent<RType::EntityTypeComponent>()->getEntityType() == E_PLAYER)
                        entity->setServerId(receivInfo.second[1]);
                }
            }
        }
        if (receivInfo.first == DELETE_ENTITY) {

            std::unique_lock<std::mutex> lock(_mtx);
            auto entities = _coord.getEntities();
            for (const auto &entity : entities) {
                if (entity->getServerId() == receivInfo.second[0]) {
                    if (entity->getComponent<RType::EntityTypeComponent>() == nullptr)
                        continue;
                    switch (entity->getComponent<RType::EntityTypeComponent>()->getEntityType())
                    {
                    case RType::E_BULLET:
                        createEffect(entity->getComponent<RType::PositionComponent>()->getPositionX(), entity->getComponent<RType::PositionComponent>()->getPositionY(),
                        RType::E_HIT_EFFECT, "./ressources/effects/hit.png", sf::IntRect(0, 0, 16, 16));
                        _coord.deleteEntity(entity);
                        break;
                    case RType::E_OCTOPUS:
                        createEffect(entity->getComponent<RType::PositionComponent>()->getPositionX(), entity->getComponent<RType::PositionComponent>()->getPositionY(),
                        RType::E_EXPLOSION_EFFECT, "./ressources/effects/explosion.png", sf::IntRect(0, 0, 32, 32));
                        _coord.deleteEntity(entity);
                        break;
                    case RType::E_FLY:
                        createEffect(entity->getComponent<RType::PositionComponent>()->getPositionX(), entity->getComponent<RType::PositionComponent>()->getPositionY(),
                        RType::E_EXPLOSION_EFFECT, "./ressources/effects/explosion.png", sf::IntRect(0, 0, 32, 32));
                        _coord.deleteEntity(entity);
                        break;
                    case RType::E_SMALL_SPACESHIP:
                        createEffect(entity->getComponent<RType::PositionComponent>()->getPositionX(), entity->getComponent<RType::PositionComponent>()->getPositionY(),
                        RType::E_EXPLOSION_EFFECT, "./ressources/effects/explosion.png", sf::IntRect(0, 0, 32, 32));
                        _coord.deleteEntity(entity);
                        break;
                    case RType::E_PLAYER:
                        _coord.deleteEntity(entity);
                        break;
                    default:
                        break;
                    }
                    break;
                }
            }
        }
        if (receivInfo.first == MOVE_ENTITY) {

            std::unique_lock<std::mutex> lock(_mtx);
            auto entities = _coord.getEntities();
            for (const auto &entity : entities) {
                if (entity->getServerId() == receivInfo.second[0] && entity->getComponent<RType::PositionComponent>() && entity->getComponent<RType::SpriteComponent>()) {
                    entity->getComponent<RType::PositionComponent>()->setPositions(static_cast<short>(receivInfo.second[1]), static_cast<short> (receivInfo.second[2]));
                    entity->getComponent<RType::SpriteComponent>()->getSprite()->setPosition(static_cast<short>(receivInfo.second[1]), static_cast<short> (receivInfo.second[2]));
                    break;
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
    std::shared_ptr<RType::ScaleComponent> scale = player->pushComponent(std::make_shared<RType::ScaleComponent>(2.0, 2.0));
    std::shared_ptr<RType::IntRectComponent> intRect = player->pushComponent(std::make_shared<RType::IntRectComponent>(0, 0, 26, 21));
    player->pushComponent(std::make_shared<RType::HealthComponent>(25));
    std::shared_ptr<RType::TextureComponent> texture = getTextureComponent("./ressources/player-sheet.png");

    player->pushComponent(std::make_shared<RType::SpriteComponent>(texture->getTexture(), position->getPositions(),
    sf::Vector2f(scale->getScaleX(), scale->getScaleY()),
    sf::IntRect(intRect->getIntRectLeft(),intRect->getIntRectTop(), intRect->getIntRectWidth(), intRect->getIntRectHeight())));
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
    std::shared_ptr<RType::ScaleComponent> scale = player->pushComponent(std::make_shared<RType::ScaleComponent>(2.0, 2.0));
    std::shared_ptr<RType::IntRectComponent> intRect = player->pushComponent(std::make_shared<RType::IntRectComponent>(0, 0, 26, 21));
    player->pushComponent(std::make_shared<RType::HealthComponent>(25));
    std::shared_ptr<RType::TextureComponent> texture = getTextureComponent("./ressources/player-sheet.png");

    player->pushComponent(std::make_shared<RType::SpriteComponent>(texture->getTexture(), position->getPositions(),
    sf::Vector2f(scale->getScaleX(), scale->getScaleY()),
    sf::IntRect(intRect->getIntRectLeft(),intRect->getIntRectTop(), intRect->getIntRectWidth(), intRect->getIntRectHeight())));
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

void RType::Game::createMobOctopus(long serverId, long posX, long posY)
{
    std::shared_ptr<RType::Entity> mob = _coord.generateNewEntity(serverId);

    mob->pushComponent(std::make_shared<RType::EntityTypeComponent>(RType::E_OCTOPUS));
    mob->pushComponent(std::make_shared<RType::HealthComponent>(3));
    std::shared_ptr<RType::PositionComponent> position = mob->pushComponent(std::make_shared<RType::PositionComponent>(posX, posY));
    std::shared_ptr<RType::ScaleComponent> scale = mob->pushComponent(std::make_shared<RType::ScaleComponent>(2.0, 2.0));
    std::shared_ptr<RType::IntRectComponent> intRect = mob->pushComponent(std::make_shared<RType::IntRectComponent>(0, 0, 41, 46));
    std::shared_ptr<RType::TextureComponent> texture = getTextureComponent("./ressources/octopus-sheet.png");
    mob->pushComponent(std::make_shared<RType::SpriteComponent>(texture->getTexture(), position->getPositions(),
    sf::Vector2f(scale->getScaleX(), scale->getScaleY()),
    sf::IntRect(intRect->getIntRectLeft(),intRect->getIntRectTop(), intRect->getIntRectWidth(), intRect->getIntRectHeight())));
    mob->pushComponent(std::make_shared<RType::DirectionPatternComponent>(UP_N_DOWN_LEFT));
    mob->pushComponent(std::make_shared<VelocityComponent>(OCTOPUS_SPEED));
    mob->pushComponent(std::make_shared<ClockComponent>());
}

void RType::Game::createMobFly(long serverId, long posX, long posY)
{
    std::shared_ptr<RType::Entity> mob = _coord.generateNewEntity(serverId);

    mob->pushComponent(std::make_shared<RType::EntityTypeComponent>(RType::E_FLY));
    mob->pushComponent(std::make_shared<RType::HealthComponent>(5));
    std::shared_ptr<RType::PositionComponent> position = mob->pushComponent(std::make_shared<RType::PositionComponent>(posX, posY));
    std::shared_ptr<RType::ScaleComponent> scale = mob->pushComponent(std::make_shared<RType::ScaleComponent>(2.0, 2.0));
    std::shared_ptr<RType::IntRectComponent> intRect = mob->pushComponent(std::make_shared<RType::IntRectComponent>(0, 0, 65, 74));
    std::shared_ptr<RType::TextureComponent> texture = getTextureComponent("./ressources/fly-sheet.png");
    mob->pushComponent(std::make_shared<RType::SpriteComponent>(texture->getTexture(), position->getPositions(),
    sf::Vector2f(scale->getScaleX(), scale->getScaleY()),
    sf::IntRect(intRect->getIntRectLeft(),intRect->getIntRectTop(), intRect->getIntRectWidth(), intRect->getIntRectHeight())));
    mob->pushComponent(std::make_shared<RType::DirectionPatternComponent>(UP_N_DOWN_LEFT));
    mob->pushComponent(std::make_shared<VelocityComponent>(FLY_SPEED));
    mob->pushComponent(std::make_shared<ClockComponent>());
}

void RType::Game::createMobSpaceShip(long serverId, long posX, long posY)
{
    std::shared_ptr<RType::Entity> mob = _coord.generateNewEntity(serverId);

    mob->pushComponent(std::make_shared<RType::EntityTypeComponent>(RType::E_SMALL_SPACESHIP));
    mob->pushComponent(std::make_shared<RType::HealthComponent>(2));
    std::shared_ptr<RType::PositionComponent> position = mob->pushComponent(std::make_shared<RType::PositionComponent>(posX, posY));
    std::shared_ptr<RType::ScaleComponent> scale = mob->pushComponent(std::make_shared<RType::ScaleComponent>(2.0, 2.0));
    std::shared_ptr<RType::IntRectComponent> intRect = mob->pushComponent(std::make_shared<RType::IntRectComponent>(0, 0, 29, 29));
    std::shared_ptr<RType::TextureComponent> texture = getTextureComponent("./ressources/enemy-sheet.png");
    mob->pushComponent(std::make_shared<RType::SpriteComponent>(texture->getTexture(), position->getPositions(),
    sf::Vector2f(scale->getScaleX(), scale->getScaleY()),
    sf::IntRect(intRect->getIntRectLeft(),intRect->getIntRectTop(), intRect->getIntRectWidth(), intRect->getIntRectHeight())));
    mob->pushComponent(std::make_shared<RType::DirectionPatternComponent>(STRAIGHT_LEFT));
    mob->pushComponent(std::make_shared<VelocityComponent>(SPACESHIP_SPEED));
    mob->pushComponent(std::make_shared<ClockComponent>());
}

void RType::Game::createBullet(long serverId, long posX, long posY)
{
    std::shared_ptr<RType::Entity> bullet = _coord.generateNewEntity(serverId);

    bullet->pushComponent(std::make_shared<RType::EntityTypeComponent>(RType::E_BULLET));

    std::shared_ptr<RType::PositionComponent> position = bullet->pushComponent(std::make_shared<RType::PositionComponent>(posX, posY));
    std::shared_ptr<RType::ScaleComponent> scale = bullet->pushComponent(std::make_shared<RType::ScaleComponent>(2.0, 2.0));
    std::shared_ptr<RType::IntRectComponent> intRect = bullet->pushComponent(std::make_shared<RType::IntRectComponent>(0, 0, 19, 6));
    std::shared_ptr<RType::TextureComponent> texture = getTextureComponent("./ressources/shoot-spritesheet.png");
    bullet->pushComponent(std::make_shared<RType::SpriteComponent>(texture->getTexture(), position->getPositions(),
    sf::Vector2f(scale->getScaleX(), scale->getScaleY()),
    sf::IntRect(intRect->getIntRectLeft(),intRect->getIntRectTop(), intRect->getIntRectWidth(), intRect->getIntRectHeight())));
    bullet->pushComponent(std::make_shared<RType::DirectionPatternComponent>(RType::STRAIGHT_RIGHT));
    bullet->pushComponent(std::make_shared<RType::VelocityComponent>(7));
    bullet->pushComponent(std::make_shared<RType::ClockComponent>());
}

void RType::Game::createGameSystem()
{
    std::unique_lock<std::mutex> lock(_mtx);
    _coord.generateNewSystem(std::make_shared<HandleEventSystem>(
        std::bind(&RType::Coordinator::addEntity, &_coord),
        std::bind(&RType::Coordinator::deleteEntity, &_coord, std::placeholders::_1)
    ));

    _coord.generateNewSystem(std::make_shared<HandlePatternSystem>(
        std::bind(&RType::Coordinator::addEntity, &_coord),
        std::bind(&RType::Coordinator::deleteEntity, &_coord, std::placeholders::_1)
    ));

    _coord.generateNewSystem(std::make_shared<HandleMoveSystem>(
        std::bind(&RType::Coordinator::addEntity, &_coord),
        std::bind(&RType::Coordinator::deleteEntity, &_coord, std::placeholders::_1),
        std::bind(&RType::Client::send, &_client, std::placeholders::_1)
    ));

    _coord.generateNewSystem(std::make_shared<HandleMoveSpriteSystem>(
        std::bind(&RType::Coordinator::addEntity, &_coord),
        std::bind(&RType::Coordinator::deleteEntity, &_coord, std::placeholders::_1)
    ));

    _coord.generateNewSystem(std::make_shared<HandleShootSystem>(
        std::bind(&RType::Coordinator::addEntity, &_coord),
        std::bind(&RType::Coordinator::deleteEntity, &_coord, std::placeholders::_1),
        std::bind(&RType::Client::send, &_client, std::placeholders::_1)
    ));

    _coord.generateNewSystem(std::make_shared<HandleColisionSystem>(
        std::bind(&RType::Coordinator::addEntity, &_coord),
        std::bind(&RType::Coordinator::deleteEntity, &_coord, std::placeholders::_1)
    ));

    _coord.generateNewSystem(std::make_shared<HandleAnimationSystem>(
        std::bind(&RType::Coordinator::addEntity, &_coord),
        std::bind(&RType::Coordinator::deleteEntity, &_coord, std::placeholders::_1)
    ));

    _coord.generateNewSystem(std::make_shared<HandleDrawSystem>(
        std::bind(&RType::Coordinator::addEntity, &_coord),
        std::bind(&RType::Coordinator::deleteEntity, &_coord, std::placeholders::_1)
    ));
}

void RType::Game::createParallaxBackground(std::shared_ptr<RType::Entity> window)
{
    float winMaxX = window->getComponent<RType::SFWindowComponent>()->getWindow()->getSize().x;
    float winMaxY = window->getComponent<RType::SFWindowComponent>()->getWindow()->getSize().y;
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
    std::shared_ptr<RType::TextureComponent> texture = getTextureComponent(path);
    std::shared_ptr<RType::PositionComponent> position = backgrounds->pushComponent(CREATE_POS_COMPONENT(posX, posY));
    float spriteHeight = 0.;
    float spriteWidth = 0.;

    backgrounds->pushComponent(CREATE_ENTITY_TYPE(RType::E_LAYER));
    backgrounds->pushComponent(std::make_shared<SpriteComponent>(texture->getTexture(),
        position->getPositions()));
    spriteWidth = texture->getTexture()->getSize().x;
    spriteHeight = texture->getTexture()->getSize().y;
    backgrounds->getComponent<SpriteComponent>()->getSprite()->setScale(sf::Vector2f(float(winMaxX / spriteWidth), float(winMaxY / spriteHeight)));
    backgrounds->pushComponent(std::make_shared<RType::DirectionPatternComponent>(STRAIGHT_LEFT));
    backgrounds->pushComponent(std::make_shared<VelocityComponent>((index + 1)));
    backgrounds->pushComponent(std::make_shared<LevelComponent>(level));
}

std::shared_ptr<RType::TextureComponent> RType::Game::getTextureComponent(const std::string &path)
{
    if (_texturesMap.find(path) != _texturesMap.end()) {
        return _texturesMap[path];
    }

    auto texture = std::make_shared<RType::TextureComponent>(path);
    _texturesMap[path] = texture;

    return texture;
}

void RType::Game::createEffect(long posX, long posY, EntityType type, std::string path, sf::IntRect rect)
{
    std::shared_ptr<RType::Entity> shotEffect = _coord.generateNewEntity();
    shotEffect->pushComponent(std::make_shared<RType::EntityTypeComponent>(type));
    std::shared_ptr<RType::PositionComponent> position = shotEffect->pushComponent(std::make_shared<RType::PositionComponent>(posX, posY - 20));
    std::shared_ptr<RType::TextureComponent> texture = shotEffect->pushComponent(std::make_shared<RType::TextureComponent>(path));
    shotEffect->pushComponent(std::make_shared<RType::SpriteComponent>(texture->getTexture(), position->getPositions(), sf::Vector2f(2, 2), rect));
    shotEffect->pushComponent(std::make_shared<RType::VelocityComponent>(7));
    shotEffect->pushComponent(std::make_shared<RType::ClockComponent>());
}

bool RType::Game::getGameHasStarted(void) const
{
    return _initConnection;
}

void RType::Game::connectToServer(void)
{
    _client.send(Encoder::connexion());
}

std::ostream &operator<<(std::ostream &s, const RType::Game &game)
{
    s << game.getCoordinator();
    return s;
}

/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Server
*/

#include "Server.hh"

RType::Server::Server(boost::asio::io_context &ioContext, int port):
    _stopLoop(false), _socket(ioContext, udp::endpoint(udp::v4(), port)), _gameHasStarted(false)
{
    std::cout << "Server listening on port " << port << std::endl;
    initSystem();
    _gameLoop = std::thread(&Server::gameLoop, this);
    _cliThread = std::thread(&Server::runCli, this);
    startReceive();
}

RType::Server::~Server()
{
    if (_gameLoop.joinable()) {
        _gameLoop.join();
    }
    if (_cliThread.joinable()) {
        _cliThread.join();
    }
}

void RType::Server::startReceive(void)
{
    _socket.async_receive_from(
        boost::asio::buffer(_recvBuffer), _remoteEndpoint,
        [this](const boost::system::error_code& error, std::size_t bytesTransferred) {
            this->handleReceive(error, bytesTransferred);
        }
    );
}

void RType::Server::handleReceive(const boost::system::error_code& error, std::size_t bytesTransferred)
{
    if (error) {
        std::cout << "There was an error during receival" << std::endl;
        return;
    }
    std::basic_string<unsigned char> command(_recvBuffer.data(), bytesTransferred);
    auto receivInfo = Decoder::getCommandInfo(command);
    std::shared_ptr<ClientServer> connectedClient = getConnectedClient();

    if (!connectedClient) {
        connectedClient = createClient();
        if (_clients.size() == 1 && !_gameHasStarted) {
            _coord.generateNewSystem(std::make_shared<HandleEntitySpawnSystem>(
                std::bind(&RType::Coordinator::addEntity, &_coord),
                std::bind(&RType::Coordinator::deleteEntity, &_coord, std::placeholders::_1, true),
                std::bind(&RType::Server::sendToAllClient, this, std::placeholders::_1)
            ));
            _gameHasStarted = true;
        }

        if (receivInfo.first == CONNEXION) {
            std::unique_lock<std::mutex> lock(_mtx);
            handleConnection(connectedClient);
            return startReceive();
        } else {
            std::unique_lock<std::mutex> lock(_mtx);
            connectedClient->sendMessage(_socket, Encoder::header(0, RType::PACKET_ERROR));
            removeClient(connectedClient);
            return startReceive();
        }
    }
    if (receivInfo.first == DISCONNEXION) {
        std::unique_lock<std::mutex> lock(_mtx);
        handleDisconnection(connectedClient);
    } else {
        handleCommand(receivInfo, connectedClient);
    }
    startReceive();
}

std::shared_ptr<RType::ClientServer> RType::Server::createClient(void)
{
    std::shared_ptr<ClientServer> newClient(new ClientServer(_remoteEndpoint));

    _clients.push_back(newClient);
    return newClient;
}

void RType::Server::removeClient(std::shared_ptr<ClientServer> client)
{
    for (std::size_t i = 0; i < _clients.size(); i++) {
        if (_clients[i]->getPortNumber() == client->getPortNumber() && _clients[i]->getAddress() == client->getAddress()) {
            _clients.erase(std::next(_clients.begin(), i));
            break;
        }
    }
}

std::shared_ptr<RType::ClientServer> RType::Server::getConnectedClient(void)
{
    std::unique_lock<std::mutex> lock(_mtx);
    for (auto client: _clients)
        if (client->getAddress() == _remoteEndpoint.address() && client->getPortNumber() == _remoteEndpoint.port() && client->getIsConnected())
            return client;
    return nullptr;
}

void RType::Server::sendToAllClient(const std::basic_string<unsigned char> &message)
{
    for (auto client: _clients)
        client->sendMessage(_socket, message);
}

void RType::Server::handleConnection(std::shared_ptr<ClientServer> connectedClient)
{
    std::shared_ptr<RType::Entity> player = _coord.generateNewEntity();

    player->pushComponent(std::make_shared<RType::EntityTypeComponent>(RType::E_PLAYER));
    player->getComponent<RType::EntityTypeComponent>()->setWeaponType(RType::LVL_1);
    std::shared_ptr<RType::PositionComponent> position = player->pushComponent(std::make_shared<RType::PositionComponent>(10, 10));
    player->pushComponent(std::make_shared<RType::IntRectComponent>(0, 0, 26, 21));
    player->pushComponent(std::make_shared<RType::ScaleComponent>(2.0, 2.0));
    player->pushComponent(std::make_shared<RType::HealthComponent>(50));
    player->pushComponent(std::make_shared<RType::ClockComponent>());
    player->pushComponent(std::make_shared<RType::DamageComponent>(1));
    player->pushComponent(std::make_shared<RType::PowerUpComponent>());
    connectedClient->setEntity(player);

    sendToAllClient(Encoder::newEntity(E_PLAYER, connectedClient->getEntity()->getId(), position->getPositionX(), position->getPositionY()));
    sendAllEntity(connectedClient);
}

void RType::Server::handleDisconnection(std::shared_ptr<ClientServer> connectedClient)
{
    std::shared_ptr<RType::Entity> clientEntity = connectedClient->getEntity();
    for (std::size_t i = 0; i < _clients.size(); i++) {
        if (_clients[i] == connectedClient) {
            removeFollowingObjects(_clients[i]->getEntity()->getId());
            sendToAllClient(Encoder::deleteEntity(_clients[i]->getEntity()->getId()));
            _coord.deleteEntity(_clients[i]->getEntity());
            _clients.erase(std::next(_clients.begin(), i));
            continue;
        }
    }
}

void RType::Server::removeFollowingObjects(long id)
{
    auto entities = _coord.getEntities();
    for (auto entity: entities) {
        if (entity->getComponent<RType::DirectionPatternComponent>() != nullptr && entity->getComponent<RType::DirectionPatternComponent>()->getEntityToFollow() == id) {
            sendToAllClient(Encoder::deleteEntity(entity->getId()));
            _coord.deleteEntity(entity);
        }
    }
}

void RType::Server::handleCommand(std::pair<RType::PacketType, std::vector<long>> receivInfo, std::shared_ptr<ClientServer> connectedClient)
{
    std::unique_lock<std::mutex> lock(_mtx);
    std::shared_ptr<ICommand> com = _commandFactory.createCommand(receivInfo);
    if (!com) {
        connectedClient->sendMessage(_socket, Encoder::header(0, RType::PACKET_ERROR));
    } else {
        com->execute(connectedClient,
            [this, &connectedClient](const std::basic_string<unsigned char>& message) { connectedClient->sendMessage(_socket, message); },
            [this](const std::basic_string<unsigned char>& message) { sendToAllClient(message); },
            _coord);
    }
}

void RType::Server::gameLoop(void)
{
    std::shared_ptr<RType::Entity> clockEntity = nullptr;
    float logicTime = 0.0;
    float deltaTime = 0.0;

    for (auto entity: _coord.getEntities()) {
        if (entity->getComponent<EntityTypeComponent>()->getEntityType() == E_WINDOW && entity->getComponent<RType::ClockComponent>() != nullptr) {
            clockEntity = entity;
            break;
        }
    }
    while (!_stopLoop) {
        deltaTime = clockEntity->getComponent<RType::ClockComponent>()->getClock(LOGIC_CLOCK).restart().asSeconds();
        logicTime += deltaTime;
        while (logicTime >= FRAME_SERVER_TIME_LOGIC) {
            std::unique_lock<std::mutex> lock(_mtx);
            for (auto sys : _coord.getSystems())
                sys->effects(_coord.getEntities());
            logicTime -= FRAME_SERVER_TIME_LOGIC;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }
}

void RType::Server::initSystem(void)
{
    _coord.generateNewSystem(std::make_shared<HandlePatternSystem>(
        std::bind(&RType::Coordinator::addEntity, &_coord),
        std::bind(&RType::Coordinator::deleteEntity, &_coord, std::placeholders::_1, true)
    ));

    _coord.generateNewSystem(std::make_shared<HandleMoveSystem>(
        std::bind(&RType::Coordinator::addEntity, &_coord),
        std::bind(&RType::Coordinator::deleteEntity, &_coord, std::placeholders::_1, true),
        nullptr,
        std::bind(&RType::Server::sendToAllClient, this, std::placeholders::_1)
    ));

    _coord.generateNewSystem(std::make_shared<HandleBossAttackSystem>(
        std::bind(&RType::Coordinator::addEntity, &_coord),
        std::bind(&RType::Coordinator::deleteEntity, &_coord, std::placeholders::_1, true),
        std::bind(&RType::Server::sendToAllClient, this, std::placeholders::_1)
    ));

    _coord.generateNewSystem(std::make_shared<HandleShootSystem>(
        std::bind(&RType::Coordinator::addEntity, &_coord),
        std::bind(&RType::Coordinator::deleteEntity, &_coord, std::placeholders::_1, true),
        nullptr,
        std::bind(&RType::Server::sendToAllClient, this, std::placeholders::_1)
    ));

    _coord.generateNewSystem(std::make_shared<HandleCollisionSystem>(
        std::bind(&RType::Coordinator::addEntity, &_coord),
        std::bind(&RType::Coordinator::deleteEntity, &_coord, std::placeholders::_1, true),
        std::bind(&RType::Server::sendToAllClient, this, std::placeholders::_1)
    ));

    std::shared_ptr<RType::Entity> window = _coord.generateNewEntity();
    window->pushComponent(std::make_shared<RType::EntityTypeComponent>(RType::E_WINDOW));
    window->pushComponent(std::make_shared<RType::ClockComponent>());
    window->pushComponent(std::make_shared<RType::ParseLevelInfoComponent>(1));
    window->pushComponent(std::make_shared<RType::LevelComponent>(1));
    window->pushComponent(std::make_shared<RType::DifficultyComponent>(EASY));
    window->pushComponent(std::make_shared<RType::ScoreComponent>(0));
}

void RType::Server::sendAllEntity(std::shared_ptr<RType::ClientServer> client)
{
    for (auto entity: _coord.getEntities()) {
        if (client->getEntity()->getId() != entity->getId() && entity->getComponent<EntityTypeComponent>() &&
            (entity->getComponent<EntityTypeComponent>()->getEntityType() == E_PLAYER ||
            EntityTypeComponent::isMob(entity->getComponent<EntityTypeComponent>()->getEntityType()) ||
            EntityTypeComponent::isItem(entity->getComponent<EntityTypeComponent>()->getEntityType()) ||
            EntityTypeComponent::isPowerUp(entity->getComponent<EntityTypeComponent>()->getEntityType()))) {
            if (entity->getComponent<RType::DirectionPatternComponent>() != nullptr && entity->getComponent<RType::DirectionPatternComponent>()->getEntityToFollow() != 0)
                continue;
            else
                client->sendMessage(_socket,
                    Encoder::newEntity(entity->getComponent<EntityTypeComponent>()->getEntityType(),
                        entity->getId(),
                        entity->getComponent<RType::PositionComponent>()->getPositionX(),
                        entity->getComponent<RType::PositionComponent>()->getPositionY()));
        }
    }
    for (auto entity: _coord.getEntities()) {
        if (client->getEntity()->getId() != entity->getId() && entity->getComponent<EntityTypeComponent>() &&
            (entity->getComponent<EntityTypeComponent>()->getEntityType() == E_PLAYER ||
            EntityTypeComponent::isMob(entity->getComponent<EntityTypeComponent>()->getEntityType()) ||
            EntityTypeComponent::isItem(entity->getComponent<EntityTypeComponent>()->getEntityType()) ||
            EntityTypeComponent::isPowerUp(entity->getComponent<EntityTypeComponent>()->getEntityType()))) {
            if (entity->getComponent<RType::DirectionPatternComponent>() != nullptr && entity->getComponent<RType::DirectionPatternComponent>()->getEntityToFollow() != 0) {
                client->sendMessage(_socket,
                        Encoder::newEntity(entity->getComponent<EntityTypeComponent>()->getEntityType(),
                            entity->getId(),
                            entity->getComponent<RType::PositionComponent>()->getPositionX(),
                            entity->getComponent<RType::PositionComponent>()->getPositionY(),
                            entity->getComponent<RType::DirectionPatternComponent>()->getEntityToFollow()));
            }
        }

    }
}

void RType::Server::stop(bool fromCli)
{
    if (_stopLoop)
        return;
    if (fromCli)
        raise(SIGINT);
    _stopLoop = true;
    for (auto client: _clients) {
        client->sendMessage(_socket, Encoder::disconnexion());
    }
    std::cout << "Server stopped" << std::endl;
}

void RType::Server::runCli(void)
{
    std::string command;
    std::string firstWord;

    std::cout << "Welcome to the R-Type server CLI" << std::endl;
    std::cout << "Type /help to see the available commands" << std::endl;
    std::cout << "> " << std::flush;
    while (!_stopLoop) {
        command = customGetLine();
        if (command == "")
            continue;
        if (command.find(' ') == std::string::npos)
            firstWord = command;
        else
            firstWord = command.substr(0, command.find(' '));
        std::unique_lock<std::mutex> lock(_mtx);
        if (firstWord == "/list") {
            listPlayers();
        } else if (firstWord == "/help") {
            printCliHelp();
        } else if (firstWord == "/difficulty") {
            changeDifficulty(command);
        } else if (firstWord == "/kick") {
            kickPlayer(command);
        } else if (firstWord == "/level") {
            changeLevel(command);
        } else if (firstWord == "/friendyFire") {
            std::cout << "Changing friendly fire" << std::endl;
        } else if (firstWord == "/exit") {
            stop(true);
            return;
        } else {
            std::cout << "Unvalid command" << std::endl;
        }
        std::cout << "> " << std::flush;
    }
}

std::string RType::Server::customGetLine(void)
{
    fd_set rfds;
    std::string ret;
    struct timeval timeout = {0, 500000};

    FD_ZERO(&rfds);
    FD_SET(STDIN_FILENO, &rfds);

    int ready = select(1, &rfds, NULL, NULL, &timeout);

    if (ready) {
        if (!std::getline(std::cin, ret)) {
            stop(true);
            return "";
        }
        return ret;
    }
    return "";
}

void RType::Server::listPlayers(void)
{
    if (_clients.empty()) {
        std::cout << "No player connected" << std::endl;
        return;
    }
    std::cout << "Players connected:" << std::endl;
    for (auto client: _clients) {
        if (client->getEntity() != nullptr)
            std::cout << " - Player " << client->getEntity()->getId() << " : " << client->getAddress().to_string() << ":" << client->getPortNumber() << std::endl;
    }
}

void RType::Server::changeDifficulty(std::string difficulty)
{
    std::string commandInfo = difficulty.substr(difficulty.find(' ') + 1);
    RType::Difficulty difficultyEnum;

    if (commandInfo == "fabien") {
        difficultyEnum = FABIEN;
        std::cout << "Changing difficulty to fabien" << std::endl;
    } else if (commandInfo == "easy") {
        difficultyEnum = EASY;
        std::cout << "Changing difficulty to easy" << std::endl;
    } else if (commandInfo == "normal") {
        difficultyEnum = NORMAL;
        std::cout << "Changing difficulty to normal" << std::endl;
    } else if (commandInfo == "hard") {
        difficultyEnum = HARD;
        std::cout << "Changing difficulty to hard" << std::endl;
    } else if (commandInfo == "alien") {
        difficultyEnum = ALIEN;
        std::cout << "Changing difficulty to alien" << std::endl;
    } else {
        std::cout << "Unvalid difficulty, the valid ones are in increasing order : fabien < easy < normal < hard < alien" << std::endl;
        return;
    }
    for (auto entity: _coord.getEntities()) {
        if (entity->getComponent<EntityTypeComponent>() != nullptr && entity->getComponent<EntityTypeComponent>()->getEntityType() == E_WINDOW) {
            if (entity->getComponent<DifficultyComponent>() != nullptr)
                entity->getComponent<DifficultyComponent>()->setDifficulty(difficultyEnum);
            std::cout << "Difficulty changed to " << commandInfo << std::endl;
            return;
        }
    }
}

void RType::Server::kickPlayer(std::string player)
{
    std::string playerToKick = player.substr(player.find(' ') + 1);
    for (auto client: _clients) {
        if (client->getEntity() != nullptr && std::to_string(client->getEntity()->getId()) == playerToKick) {
            client->sendMessage(_socket, Encoder::disconnexion());
            std::cout << "The player " << playerToKick << " has been kicked" << std::endl;
            return;
        }
    }
    std::cout << "Player not found" << std::endl;
}

void RType::Server::changeLevel(std::string level)
{
    std::string levelNumber = level.substr(level.find(' ') + 1);
    int levelInt = std::stoi(levelNumber);

    if (levelInt < 1 || levelInt > 4) {
        std::cout << "Unvalid level, the valid ones are between 1 and 4" << std::endl;
        return;
    }
    for (auto entity: _coord.getEntities()) {
        if (entity->getComponent<EntityTypeComponent>() != nullptr && entity->getComponent<EntityTypeComponent>()->getEntityType() == E_WINDOW) {
            if (entity->getComponent<LevelComponent>() != nullptr && entity->getComponent<ParseLevelInfoComponent>() != nullptr) {
                entity->getComponent<LevelComponent>()->setLevel(levelInt);
                entity->getComponent<ParseLevelInfoComponent>()->setLevel(levelInt);
                removeAllEnnemies();
            }
            sendToAllClient(Encoder::infoLevel(levelInt));
            std::cout << "Changing level to " << levelInt << std::endl;
            return;
        }
    }
}

void RType::Server::printCliHelp(void)
{
    std::cout << "Commands available:" << std::endl;
    std::cout << "  /list : list all the connected players" << std::endl;
    std::cout << "  /difficulty [difficulty] : change the difficulty of the game" << std::endl;
    std::cout << "  /kick [playerID] : disconnect a player with its id" << std::endl;
    std::cout << "  /level [levelNumber] : change the level of the game" << std::endl;
    std::cout << "  /friendyFire [on - off] : activate - desactivate the friendly fire" << std::endl;
    std::cout << "  /exit : close the server and disconnect everyone connected to it" << std::endl;
}

void RType::Server::removeAllEnnemies(void)
{
    auto entities = _coord.getEntities();
    for (auto entity: entities) {
        if (entity == nullptr)
            continue;
        if (entity->getComponent<EntityTypeComponent>() != nullptr &&
            (EntityTypeComponent::isMob(entity->getComponent<EntityTypeComponent>()->getEntityType()) ||
            EntityTypeComponent::isBoss(entity->getComponent<EntityTypeComponent>()->getEntityType()))) {
            sendToAllClient(Encoder::deleteEntity(entity->getId()));
            _coord.deleteEntity(entity);
        }
    }
}

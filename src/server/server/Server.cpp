/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Server
*/

#include "Server.hh"

RType::Server::Server(boost::asio::io_context &ioContext, int port):
    _stopLoop(false), _socket(ioContext, udp::endpoint(udp::v4(), port))
{
    std::cout << "Server listening on port " << port << std::endl;
    initSystem();
    _gameLoop = std::thread(&Server::gameLoop, this);
    startReceive();
}

RType::Server::~Server()
{
    if (_gameLoop.joinable()) {
        _gameLoop.join();
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

void RType::Server::handleSend(std::string, const boost::system::error_code &error, std::size_t bytesTransferred)
{
    if (!error) {
        std::cout << "Sent response to client, bytes transferred: " << bytesTransferred << std::endl;
    } else {
        std::cout << "Error on send: " << error.message() << std::endl;
    }
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
            std::cout << "remove client" << std::endl;
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
    player->pushComponent(std::make_shared<RType::HealthComponent>(25));
    player->pushComponent(std::make_shared<RType::ClockComponent>());
    player->pushComponent(std::make_shared<RType::DamageComponent>(1));
    player->pushComponent(std::make_shared<RType::PowerUpComponent>());
    connectedClient->setEntity(player);

    sendToAllClient(Encoder::newEntity(E_PLAYER, connectedClient->getEntity()->getId(), position->getPositionX(), position->getPositionY()));
    sendAllEntity(connectedClient);
}

void RType::Server::handleDisconnection(std::shared_ptr<ClientServer> connectedClient)
{
    for (std::size_t i = 0; i < _clients.size(); i++) {
        if (_clients[i] == connectedClient) {
            sendToAllClient(Encoder::deleteEntity(_clients[i]->getEntity()->getId()));
            _coord.deleteEntity(_clients[i]->getEntity());
            _clients.erase(std::next(_clients.begin(), i));
        }
    }
}

void RType::Server::handleCommand(std::pair<RType::PacketType, std::vector<long>> receivInfo, std::shared_ptr<ClientServer> connectedClient)
{
    std::unique_lock<std::mutex> lock(_mtx);
    std::shared_ptr<ICommand> com = _commandFactory.createCommand(receivInfo);
    if (!com) {
        connectedClient->sendMessage(_socket, Encoder::header(0, RType::PACKET_ERROR));
        std::cout << "unvalid command sent by client" << std::endl;
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
        std::bind(&RType::Coordinator::deleteEntity, &_coord, std::placeholders::_1)
    ));

    _coord.generateNewSystem(std::make_shared<HandleMoveSystem>(
        std::bind(&RType::Coordinator::addEntity, &_coord),
        std::bind(&RType::Coordinator::deleteEntity, &_coord, std::placeholders::_1),
        nullptr,
        std::bind(&RType::Server::sendToAllClient, this, std::placeholders::_1)
    ));

    _coord.generateNewSystem(std::make_shared<HandleColisionSystem>(
        std::bind(&RType::Coordinator::addEntity, &_coord),
        std::bind(&RType::Coordinator::deleteEntity, &_coord, std::placeholders::_1),
        std::bind(&RType::Server::sendToAllClient, this, std::placeholders::_1)
    ));

    _coord.generateNewSystem(std::make_shared<HandleEntitySpawnSystem>(
        std::bind(&RType::Coordinator::addEntity, &_coord),
        std::bind(&RType::Coordinator::deleteEntity, &_coord, std::placeholders::_1),
        std::bind(&RType::Server::sendToAllClient, this, std::placeholders::_1)
    ));

    std::shared_ptr<RType::Entity> window = _coord.generateNewEntity();
    window->pushComponent(std::make_shared<RType::EntityTypeComponent>(RType::E_WINDOW));
    window->pushComponent(std::make_shared<RType::ClockComponent>());
}

void RType::Server::sendAllEntity(std::shared_ptr<RType::ClientServer> client)
{
    for (auto entity: _coord.getEntities()) {
        if (client->getEntity()->getId() != entity->getId() &&
            (entity->getComponent<EntityTypeComponent>()->getEntityType() == E_PLAYER ||
            EntityTypeComponent::isMob(entity->getComponent<EntityTypeComponent>()->getEntityType()) ||
            EntityTypeComponent::isItem(entity->getComponent<EntityTypeComponent>()->getEntityType()))) {
            client->sendMessage(_socket, Encoder::newEntity(entity->getComponent<EntityTypeComponent>()->getEntityType(), entity->getId(), entity->getComponent<RType::PositionComponent>()->getPositionX(), entity->getComponent<RType::PositionComponent>()->getPositionY()));
        }
    }
}

void RType::Server::stop(void)
{
    _stopLoop = true;
    for (auto client: _clients) {
        client->sendMessage(_socket, Encoder::disconnexion());
    }
    std::cout << "Server stopped" << std::endl;
}

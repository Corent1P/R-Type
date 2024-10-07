/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Server
*/

#include "Server.hh"

std::string RType::Server::makeDaytimeString(void)
{
    std::time_t now = std::time(0);
    return std::ctime(&now);
}

RType::Server::Server(boost::asio::io_context &ioContext, int port):
    _stopLoop(false), _socket(ioContext, udp::endpoint(udp::v4(), port))
{
    std::cout << "Server listening on port " << port << std::endl;
    initSystem();
    _gameLoop = std::jthread(&Server::gameLoop, this);
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
    if (!connectedClient)
        connectedClient = createClient();

    std::shared_ptr<ICommand> com = _commandFactory.createCommand(receivInfo);
    if (!com) {
        connectedClient->sendMessage(_socket, Encoder::header(0, RType::ERROR)); //TODO: create an error in the encoder and decoder
        std::cout << "unvalid command sent by client" << std::endl;
    } else {
        com->execute(connectedClient,
            [this, &connectedClient](const std::basic_string<unsigned char>& message) { connectedClient->sendMessage(_socket, message); },
            [this](const std::basic_string<unsigned char>& message) { sendToAllClient(message); });
    }
    // TODO: handle player disconection (for the moment, no disconnection because _clients are not accessible in the command execution)
    startReceive();
}

void RType::Server::handleSend(std::string message, const boost::system::error_code &error, std::size_t bytesTransferred)
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

    std::shared_ptr<RType::Entity> player = _coord.generateNewEntity();

    player->pushComponent(std::make_shared<RType::EntityTypeComponent>(RType::E_PLAYER));
    std::shared_ptr<RType::PositionComponent> position = player->pushComponent(std::make_shared<RType::PositionComponent>(10, 10));
    player->pushComponent(std::make_shared<RType::HealthComponent>(25));
    player->pushComponent(std::make_shared<RType::ClockComponent>());

    newClient->setEntity(player);
    _clients.push_back(newClient);
    sendToAllClient(Encoder::newEntity(E_PLAYER, newClient->getEntity()->getId(), position->getPositionX(), position->getPositionY()));
    sendAllEntity(newClient);
    createMob();
    return newClient;
}

void RType::Server::createMob(void)
{

    std::shared_ptr<RType::Entity> mob = _coord.generateNewEntity();

    mob->pushComponent(std::make_shared<RType::EntityTypeComponent>(RType::E_MOB));
    std::shared_ptr<RType::PositionComponent> position = mob->pushComponent(std::make_shared<RType::PositionComponent>(420, 420));
    mob->pushComponent(std::make_shared<RType::HealthComponent>(25));
    mob->pushComponent(std::make_shared<RType::ClockComponent>());
    mob->pushComponent(std::make_shared<RType::VelocityComponent>(3));

    auto direction = mob->pushComponent(std::make_shared<RType::DirectionComponent>());
    direction->setDirections(LEFT, true);
    sendToAllClient(Encoder::newEntity(E_MOB, mob->getId(), position->getPositionX(), position->getPositionY()));
}

std::shared_ptr<RType::ClientServer> RType::Server::getConnectedClient(void)
{
    for (auto client: _clients)
        if (client->getAddress() == _remoteEndpoint.address() && client->getPortNumber() == _remoteEndpoint.port() && client->getIsConnected())
            return client;
    return nullptr;
}

std::size_t RType::Server::getMaxClientId(void)
{
    std::size_t max = 0;

    if (_clients.empty())
        return 0;
    for (auto client: _clients)
        if (client->getEntity()->getId() > max)
            max = client->getEntity()->getId();
    return max + 1;
}

bool RType::Server::removeClient(void)
{
    for (auto it = _clients.begin(); it != _clients.end(); it++) {
        if (*it == getConnectedClient()) {
            std::cout << "remove client with id: " << (*it)->getEntity()->getId() << std::endl;
            sendToAllClient(Encoder::deleteEntity((*it)->getEntity()->getId()));
            _coord.deleteEntity((*it)->getEntity());
            _clients.erase(it);
            return true;
        }
    }
    return false;
}

void RType::Server::sendToAllClient(const std::basic_string<unsigned char> &message)
{
    for (auto client: _clients)
        client->sendMessage(_socket, message);
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
        while (logicTime >= FRAME_TIME_LOGIC) {
            for (auto sys : _coord.getSystems())
                sys->effects(_coord.getEntities());
            logicTime -= FRAME_TIME_LOGIC;
        }
    }
}

void RType::Server::initSystem(void)
{
    _coord.generateNewSystem(std::make_shared<HandleMoveSystem>(std::bind(&RType::Server::sendToAllClient, this, std::placeholders::_1)));

    std::shared_ptr<RType::Entity> window = _coord.generateNewEntity();
    window->pushComponent(std::make_shared<RType::EntityTypeComponent>(RType::E_WINDOW));
    window->pushComponent(std::make_shared<RType::ClockComponent>());
}

void RType::Server::sendAllEntity(std::shared_ptr<RType::ClientServer> client)
{
    for (auto entity: _coord.getEntities()) {
        if (client->getEntity()->getId() != entity->getId() && (entity->getComponent<EntityTypeComponent>()->getEntityType() == E_PLAYER || entity->getComponent<EntityTypeComponent>()->getEntityType() == E_MOB)) {
            client->sendMessage(_socket, Encoder::newEntity(entity->getComponent<EntityTypeComponent>()->getEntityType(), entity->getId(), entity->getComponent<RType::PositionComponent>()->getPositionX(), entity->getComponent<RType::PositionComponent>()->getPositionY()));
        }
    }

}

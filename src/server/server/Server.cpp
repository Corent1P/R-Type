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
    // initSystem();
    // _gameLoop = std::jthread(&Server::gameLoop, this);
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

void RType::Server::handleReceive(const boost::system::error_code &error, std::size_t bytesTransferred)
{
    if (error) {
        std::cout << "There was an error during receival" << std::endl;
        return;
    }
    std::basic_string<unsigned char> command(_recvBuffer.data(), bytesTransferred);
    auto receivInfo = Decoder::getCommandInfo(command);
    // std::cout << "Message received = " << receivInfo.first << " with coordinates " << receivInfo.second[0] << ":" << receivInfo.second[1] << std::endl;
    std::shared_ptr<ClientServer> connectedClient = getConnectedClient();
    if (!connectedClient)
        connectedClient = createClient();

    // ! TO REORGANISE {
    // connectedClient->sendMessage(_socket, Encoder::movePlayer(receivInfo.second[0], receivInfo.second[1]));
    if (receivInfo.first == MOVE_PLAYER) {
        std::pair<double, double> position = {connectedClient->getEntity()->getComponent<PositionComponent>()->getPositionX(), connectedClient->getEntity()->getComponent<PositionComponent>()->getPositionY()};
        position.first += ((double)receivInfo.second[0]) / 10.;
        position.second += ((double)receivInfo.second[1]) / 10.;
        if (position.first < 0.)
            position.first = 0.;
        if (position.first > 1920.)
            position.first = 1920.;
        if (position.second < 0.)
            position.second = 0.;
        if (position.second > 1080.)
            position.second = 1080.;
        connectedClient->getEntity()->getComponent<PositionComponent>()->setPositions(position.first, position.second);
        sendToAllClient(Encoder::moveEntity(connectedClient->getEntity()->getId(), position.first, position.second, 0));
    } else if (receivInfo.first == DISCONNEXION) {
        removeClient();
    }
    // std::shared_ptr<ICommand> com = _commandFactory.createCommand(command);
    // std::string response;
    // if (!com)
    //     response = "Unvalid Command\n";
    // else {
    //     com->execute(_socket, connectedClient);
    //     response = makeDaytimeString();
    // }
    // connectedClient->sendMessage(_socket, response);
    // ! }
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

    std::shared_ptr<RType::Entity> player = _coord.generateNewEntity();

    player->pushComponent(std::make_shared<RType::EntityTypeComponent>(RType::E_PLAYER));
    std::shared_ptr<RType::PositionComponent> position = player->pushComponent(std::make_shared<RType::PositionComponent>(10, 10));
    player->pushComponent(std::make_shared<RType::HealthComponent>(25));
    player->pushComponent(std::make_shared<RType::ClockComponent>());

    newClient->setEntity(player);
    std::cout << _coord << std::endl;
    _clients.push_back(newClient);
    sendToAllClient(Encoder::newEntity(NEW_ENTITY, newClient->getEntity()->getId(), position->getPositionX(), position->getPositionY())); //TODO: change this (when including the ecs in the server)
    for (auto client: _clients)
        if (client != newClient)
            newClient->sendMessage(_socket, Encoder::newEntity(2, client->getEntity()->getId(), client->getEntity()->getComponent<RType::PositionComponent>()->getPositionX(), client->getEntity()->getComponent<RType::PositionComponent>()->getPositionY()));
    return newClient;
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
    std::cout << "loop" << std::endl;
    while (!_stopLoop) {
        deltaTime = clockEntity->getComponent<RType::ClockComponent>()->getClock(LOGIC_CLOCK).restart().asSeconds();
        logicTime += deltaTime;
        while (logicTime >= FRAME_TIME_LOGIC) {
            std::cout << logicTime << std::endl;
            for (auto sys : _coord.getSystems())
                sys->effects(_coord.getEntities());
            logicTime -= FRAME_TIME_LOGIC;
        }
    }
}

void RType::Server::initSystem(void)
{
    // _coord.generateNewSystem(std::make_shared<HandleMoveSystem>());

    std::shared_ptr<RType::Entity> window = _coord.generateNewEntity();
    window->pushComponent(std::make_shared<RType::EntityTypeComponent>(RType::E_WINDOW));
    window->pushComponent(std::make_shared<RType::ClockComponent>());
}

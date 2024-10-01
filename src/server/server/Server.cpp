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
    _socket(ioContext, udp::endpoint(udp::v4(), port))
{
    std::cout << "Server listening on port " << port << std::endl;
    startReceive();
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
    std::cout << "Message received = " << receivInfo.first << " with coordinates " << receivInfo.second[0] << ":" << receivInfo.second[1] << std::endl;
    std::shared_ptr<Client> connectedClient = getConnectedClient();
    if (!connectedClient)
        connectedClient = createClient();

    // ! TO REORGANISE {
    connectedClient->sendMessage(_socket, Encoder::movePlayer(receivInfo.second[0], receivInfo.second[1]));
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

std::shared_ptr<RType::Client> RType::Server::createClient(void)
{
    std::shared_ptr<Client> newClient(new Client(_remoteEndpoint));
    _clients.push_back(newClient);
    return newClient;
}

std::shared_ptr<RType::Client> RType::Server::getConnectedClient(void)
{
    for (auto client: _clients)
        if (client->getAddress() == _remoteEndpoint.address() && client->getPortNumber() == _remoteEndpoint.port() && client->getIsConnected())
            return client;
    return nullptr;
}

bool RType::Server::removeClient(void)
{
    for (auto it = _clients.begin(); it != _clients.end(); it++) {
        if ((*it)->getAddress() == _remoteEndpoint.address() || (*it)->getPortNumber() == _remoteEndpoint.port()) {
            _clients.erase(it);
            return true;
        }
    }
    return false;
}

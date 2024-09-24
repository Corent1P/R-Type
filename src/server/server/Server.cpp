/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Server
*/

#include "Server.hh"

std::string RType::Server::makeDaytimeString(void)
{
    using namespace std; // For time_t, time and ctime;
    time_t now = time(0);
    return ctime(&now);
}

RType::Server::Server(boost::asio::io_context &ioContext, int port):
    _socket(ioContext, udp::endpoint(udp::v4(), port))
{
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
    std::cout << "Message received = " << std::string(_recvBuffer.data(), bytesTransferred) << std::endl;
    std::shared_ptr<Client> connectedClient = getConnectedClient();
    if (!connectedClient)
        connectedClient = createClient();

    // TODO: implement the logic with the client and the message
    std::string message = makeDaytimeString();
    _socket.async_send_to(boost::asio::buffer(message), _remoteEndpoint,
        [this, message](const boost::system::error_code &error, std::size_t bytes_transferred) {
            this->handleSend(message, error, bytes_transferred);
        }
    );
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
    std::shared_ptr<Client> newClient(new Client(_remoteEndpoint.port(), _remoteEndpoint.address()));
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

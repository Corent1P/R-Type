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
            std::cout << "Connection established" << std::endl;
            std::cout << "Message received = " << std::string(_recvBuffer.data(), bytesTransferred) << std::endl;
            this->handleReceive(error, bytesTransferred);
        }
    );
}

void RType::Server::handleReceive(const boost::system::error_code &error, std::size_t)
{
    // TODO: faire une meilleure gestion d'erreur
    if (!error) {
        std::shared_ptr<std::string> message(new std::string(makeDaytimeString()));

        _socket.async_send_to(boost::asio::buffer(*message), _remoteEndpoint,
            [this, message](const boost::system::error_code &error, std::size_t bytes_transferred) {
                this->handleSend(message, error, bytes_transferred);
            }
        );
        startReceive();
    } else {
        std::cout << "There was an error during receival" << std::endl;
    }
}

void RType::Server::handleSend(std::shared_ptr<std::string> message, const boost::system::error_code &error, std::size_t bytesTransferred)
{
    if (!error) {
        std::cout << "Sent response to client, bytes transferred: " << bytesTransferred << std::endl;
    } else {
        std::cout << "Error on send: " << error.message() << std::endl;
    }
}

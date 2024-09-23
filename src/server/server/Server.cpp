/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Server
*/

#include "Server.hh"

RType::Server::Server(boost::asio::io_context &ioContext, int port):
    _socket(ioContext, udp::endpoint(udp::v4(), port))
{
    startReceive();
}

void RType::Server::startReceive(void)
{
    _socket.async_receive_from(
        boost::asio::buffer(_recvBuffer, MAX_SIZE),
        _remoteEndpoint,
        boost::bind(&Server::handleReceive, this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred)
    );
}

void RType::Server::handleReceive(const boost::system::error_code& error, std::size_t byteTransferred)
{
    // TODO/ faire une meilleure gestion d'erreur
    if (!error) {
        std::cout << "Connection established with client" << std::endl;
        std::string message("Hello from server");
        _socket.async_send_to(boost::asio::buffer(message),
            _remoteEndpoint,
            boost::bind(&Server::handleSend, this, message,
                boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred));
        startReceive();
    }
}

void RType::Server::handleSend(std::string string, const boost::system::error_code &error, std::size_t byteTransferred)
{
    // TODO: send something to the client
}

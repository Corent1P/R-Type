/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Server
*/

#pragma once

#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>

#define MAX_SIZE 1024

using boost::asio::ip::udp;

namespace RType {
    class Server {
        public:
            Server(boost::asio::io_context &ioContext, int port);
            ~Server() = default;

        private:
            void startReceive(void);
            void handleReceive(const boost::system::error_code& error, std::size_t byteTransferred);
            void handleSend(std::string string, const boost::system::error_code &error, std::size_t byteTransferred);

            udp::socket _socket;
            udp::endpoint _remoteEndpoint;
            std::string _recvBuffer;
    };
}

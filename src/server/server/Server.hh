/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Server
*/

#pragma once

#include <array>
#include <ctime>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <boost/asio.hpp>

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
            void handleSend(std::shared_ptr<std::string> message, const boost::system::error_code &error, std::size_t byteTransferred);
            std::string makeDaytimeString(void);

            udp::socket _socket;
            udp::endpoint _remoteEndpoint;
            std::array<char, MAX_SIZE> _recvBuffer;
    };
}

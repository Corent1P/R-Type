/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Client
*/

#pragma once

#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>

using boost::asio::ip::udp;

namespace RType {
    class Client {
        public:
            Client(int ip);
            ~Client() = default;

        private:
            boost::asio::io_context _ioContext;
            udp::endpoint _receiverEndpoint;
    };
}

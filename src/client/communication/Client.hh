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
#include "../ClientError.hh"

using boost::asio::ip::udp;

namespace RType {
    class Client {
        public:
            Client(boost::asio::io_context &ioContext, const std::string &host, const std::string &port);
            ~Client();
            void send(const std::string &message);
            std::string receive(void);

        private:
            boost::asio::io_context &_ioContext;
            udp::endpoint _endpoint;
            udp::socket _socket;
    };
}

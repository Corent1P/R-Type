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
            /**
             * @brief send a message to the endpoint
             *
             * @deprecated
             * @param message (std::string) the message to send
             */
            void send(const std::string &message);
            void send(const std::basic_string<unsigned char> &message);
            void cancel(void);
            std::basic_string<unsigned char> receive(void);

        private:
            boost::asio::io_context &_ioContext;
            udp::endpoint _endpoint;
            udp::socket _socket;
    };
}

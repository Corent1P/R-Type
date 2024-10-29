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
#include "../../protocolHandler/Decoder.hh"

using boost::asio::ip::udp;

namespace RType {
    class Client {
        public:
            Client(boost::asio::io_context &ioContext, const std::string &host, const std::string &port);
            ~Client();
            /**
             * @brief send a message to the endpoint
             *
             * @param message (const std::basic_string<unsigned char> ) the message to send
             */
            void send(const std::basic_string<unsigned char> &message);
            /**
             * @brief cancel the socket
             *
             */
            void cancel(void);
            /**
             * @brief receive a message from the endpoint
             *
             * @return std::basic_string<unsigned char> the message received
             */
            std::basic_string<unsigned char> receive(void);
            /**
             * @brief Log the command received
             *
             * @param command The command to log
             */
            void logCommand(const PACKET &command);
            /**
             * @brief ask to the server to resend the lost packet
             *
             */
            void askForLostPackets(void);

        private:
            /**
             * @brief The io context
             *
             */
            boost::asio::io_context &_ioContext;
            /**
             * @brief The endpoint of the client
             *
             */
            udp::endpoint _endpoint;
            /**
             * @brief The socket of the client
             *
             */
            udp::socket _socket;
            /**
             * @brief The packets received
             *
             */
            std::vector<u_int16_t> _packetsReceived;
    };
}

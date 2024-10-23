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
    /**
     * @brief The Client class representing a client in the R-Type project
     *
     */
    class Client {
        public:
            /**
             * @brief Construct a new Client object
             *
             * @param ioContext the boost io_context
             * @param host the host to connect to
             * @param port the port to connect to
             */
            Client(boost::asio::io_context &ioContext, const std::string &host, const std::string &port);
            /**
             * @brief Destroy the Client object
             *
             */
            ~Client();
            /**
             * @brief send a message to the endpoint
             *
             * @deprecated
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
            boost::asio::io_context &_ioContext;
            udp::endpoint _endpoint;
            udp::socket _socket;
            std::vector<u_int16_t> _packetsReceived;
    };
}

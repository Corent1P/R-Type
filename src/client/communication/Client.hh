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
    /**
     * @brief Client class for sending and receiving messages from a server
     *
     */
    class Client {
        public:
            /**
             * @brief Construct a new Client object with the given host and port
             *
             * @param ioContext The boost io_context for asynchronous operations
             * @param host The server host address
             * @param port The server port
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

        private:
            /**
             * @brief the io context
             *
             */
            boost::asio::io_context &_ioContext;

            /**
             * @brief the endpoint of the server
             *
             */
            udp::endpoint _endpoint;

            /**
             * @brief the socket to the server
             *
             */
            udp::socket _socket;
    };
}

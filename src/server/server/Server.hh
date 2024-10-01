/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Server
*/

#pragma once

#include "../includes.hh"
#include "../client/Client.hh"
#include "../command/factory/CommandFactory.hh"
#include "../../protocolHandler/Decoder.hh"
#include "../../protocolHandler/Encoder.hh"

#define MAX_SIZE 1024

namespace RType {
    class Server {
        public:
            Server(boost::asio::io_context &ioContext, int port);
            ~Server() = default;

        private:
            void startReceive(void);
            void handleReceive(const boost::system::error_code& error, std::size_t byteTransferred);
            void handleSend(std::string message, const boost::system::error_code &error, std::size_t byteTransferred);
            std::string makeDaytimeString(void);
            std::shared_ptr<Client> createClient(void);
            std::shared_ptr<Client> getConnectedClient(void);
            bool removeClient(void);
            void sendToAllClient(const std::basic_string<unsigned char> &message);

            udp::socket _socket;
            udp::endpoint _remoteEndpoint;
            std::array<unsigned char, MAX_SIZE> _recvBuffer;
            std::vector<std::shared_ptr<Client>> _clients;
            CommandFactory _commandFactory;
    };
}

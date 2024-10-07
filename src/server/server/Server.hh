/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Server
*/

#pragma once

#include "../includes.hh"
#include "../clientServer/ClientServer.hh"
#include "../command/factory/CommandFactory.hh"
#include "../../protocolHandler/Decoder.hh"
#include "../../protocolHandler/Encoder.hh"

#define MAX_SIZE 1024

namespace RType {
    class Server {
        public:
            Server(boost::asio::io_context &ioContext, int port);
            ~Server();
            void gameLoop(void);
        private:
            void initSystem(void);
            void startReceive(void);
            void handleReceive(const boost::system::error_code& error, std::size_t bytesTransferred);
            void handleSend(std::string message, const boost::system::error_code &error, std::size_t bytesTransferred);
            std::string makeDaytimeString(void);
            std::shared_ptr<RType::ClientServer> createClient(void);
            void createMob(void);

            std::shared_ptr<RType::ClientServer> getConnectedClient(void);
            std::size_t getMaxClientId(void);
            bool removeClient(void);
            void sendToAllClient(const std::basic_string<unsigned char> &message);
            void sendAllEntity(std::shared_ptr<RType::ClientServer> client);

            bool _stopLoop;
            std::jthread _gameLoop;
            udp::socket _socket;
            udp::endpoint _remoteEndpoint;
            std::array<unsigned char, MAX_SIZE> _recvBuffer;
            std::vector<std::shared_ptr<ClientServer>> _clients;
            CommandFactory _commandFactory;
            RType::Coordinator _coord;
    };
}

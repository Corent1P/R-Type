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

        private:
            // Communication handling
            void startReceive(void);
            void handleReceive(const boost::system::error_code& error, std::size_t bytesTransferred);
            void handleSend(std::string message, const boost::system::error_code &error, std::size_t bytesTransferred);
            std::shared_ptr<RType::ClientServer> createClient(void);
            std::shared_ptr<RType::ClientServer> getConnectedClient(void);
            void sendToAllClient(const std::basic_string<unsigned char> &message);

            // Command handling
            void handleConnection(std::shared_ptr<ClientServer> connectedClient);
            void handleDisconnection(std::shared_ptr<ClientServer> connectedClient);
            void handleCommand(std::pair<RType::PacketType, std::vector<long>> receivInfo, std::shared_ptr<ClientServer> connectedClient);

            // Game handling
            void gameLoop(void);
            void initSystem(void);
            void sendAllEntity(std::shared_ptr<RType::ClientServer> client);
            void createMob(void);

            bool _stopLoop;
            std::mutex _mtx;
            std::jthread _gameLoop;
            udp::socket _socket;
            udp::endpoint _remoteEndpoint;
            std::array<unsigned char, MAX_SIZE> _recvBuffer;
            std::vector<std::shared_ptr<ClientServer>> _clients;
            CommandFactory _commandFactory;
            RType::Coordinator _coord;
    };
}

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
            // *Communication handling
            /**
             * @brief Start to receive messages
             *
             */
            void startReceive(void);
            /**
             * @brief Handle the received message
             *
             * @param error the error code
             * @param bytesTransferred the number of bytes transferred
             */
            void handleReceive(const boost::system::error_code& error, std::size_t bytesTransferred);
            /**
             * @brief Handle the sending of a message
             *
             * @param message the message to send
             * @param error the error code
             * @param bytesTransferred the number of bytes transferred
             */
            void handleSend(std::string message, const boost::system::error_code &error, std::size_t bytesTransferred);
            /**
             * @brief Create a client object and add it to the clients vector
             *
             * @return std::shared_ptr<RType::ClientServer> the created client object
             */
            std::shared_ptr<RType::ClientServer> createClient(void);
            /**
             * @brief Get the connected client object
             *
             * @return std::shared_ptr<RType::ClientServer> the connected client object
             */
            std::shared_ptr<RType::ClientServer> getConnectedClient(void);
            /**
             * @brief Send a message to all the clients
             *
             * @param message the message to send
             */
            void sendToAllClient(const std::basic_string<unsigned char> &message);

            // *Command handling
            /**
             * @brief Handle the connection of a client
             *
             * @param connectedClient the connected client object
             */
            void handleConnection(std::shared_ptr<ClientServer> connectedClient);
            /**
             * @brief Handle the disconnection of a client
             *
             * @param connectedClient the disconnected client object
             */
            void handleDisconnection(std::shared_ptr<ClientServer> connectedClient);
            /**
             * @brief Handle a command
             *
             * @param receivInfo the received information
             * @param connectedClient the connected client object
             */
            void handleCommand(std::pair<RType::PacketType, std::vector<long>> receivInfo, std::shared_ptr<ClientServer> connectedClient);

            // *Game handling
            /**
             * @brief Start the game loop
             *
             */
            void gameLoop(void);
            /**
             * @brief Initialize the system of the ECS
             *
             */
            void initSystem(void);
            /**
             * @brief Send all the entities to the client
             *
             * @param client the client object that will receive the entities
             */
            void sendAllEntity(std::shared_ptr<RType::ClientServer> client);
            /**
             * @brief Create a Mob object and add it to the ECS
             * @warning temporary method
             */
            void createMob(void);

            /**
             * @brief Stop the game loop when true
             *
             */
            bool _stopLoop;
            /**
             * @brief The mutex to protect the read of the entity in the ECS
             *
             */
            std::mutex _mtx;
            /**
             * @brief The thread that will run the game loop
             *
             */
            std::jthread _gameLoop;
            /**
             * @brief The socket of the Server
             *
             */
            udp::socket _socket;
            /**
             * @brief The endpoint of the remote client
             *
             */
            udp::endpoint _remoteEndpoint;
            /**
             * @brief The buffer that will receive the message
             *
             */
            std::array<unsigned char, MAX_SIZE> _recvBuffer;
            /**
             * @brief The vector of all the connected clients
             *
             */
            std::vector<std::shared_ptr<ClientServer>> _clients;
            /**
             * @brief The command factory that will create the command objects
             *
             */
            CommandFactory _commandFactory;
            /**
             * @brief The ECS coordinator
             *
             */
            RType::Coordinator _coord;
    };
}

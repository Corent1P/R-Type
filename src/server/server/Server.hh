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
#define FRAME_SERVER_TIME_LOGIC 1.0 / 20.0
namespace RType {
    class Server {
        public:
            /**
             * @brief Construct a new Server object
             *
             * @param ioContext the boost io_context
             * @param port the port to listen to
             */
            Server(boost::asio::io_context &ioContext, int port);
            /**
             * @brief Destroy the Server object
             *
             */
            ~Server();

        private:
            // Communication handling
            /**
             * @brief Start the reception of messages
             *
             */
            void startReceive(void);
            /**
             * @brief The callback method for the reception of messages
             *
             * @param error the error code
             * @param bytesTransferred the number of bytes transferred
             */
            void handleReceive(const boost::system::error_code& error, std::size_t bytesTransferred);
            /**
             * @brief The callback method for the sending of messages
             *
             * @param message the message sent
             * @param error the error code
             * @param bytesTransferred the number of bytes transferred
             */
            void handleSend(std::string message, const boost::system::error_code &error, std::size_t bytesTransferred);
            /**
             * @brief Create a new client
             *
             * @return std::shared_ptr<RType::ClientServer> the created client
             */
            std::shared_ptr<RType::ClientServer> createClient(void);
            /**
             * @brief Get the connected client
             *
             * @return std::shared_ptr<RType::ClientServer> the connected client
             */
            std::shared_ptr<RType::ClientServer> getConnectedClient(void);
            /**
             * @brief Send a message to all connected clients
             *
             * @param message the message to send
             */
            void sendToAllClient(const std::basic_string<unsigned char> &message);

            // Command handling
            /**
             * @brief Handle the connection of a client
             *
             * @param connectedClient the connected client
             */
            void handleConnection(std::shared_ptr<ClientServer> connectedClient);
            /**
             * @brief Handle the disconnection of a client
             *
             * @param connectedClient the connected client
             */
            void handleDisconnection(std::shared_ptr<ClientServer> connectedClient);
            /**
             * @brief Handle the command received by the client
             *
             * @param receivInfo the received command
             * @param connectedClient the connected client
             */
            void handleCommand(PACKET receivInfo, std::shared_ptr<ClientServer> connectedClient);

            // Game handling
            /**
             * @brief The game loop
             *
             */
            void gameLoop(void);
            /**
             * @brief Initialize the systems in the ECS
             *
             */
            void initSystem(void);
            /**
             * @brief Send all entities to a client
             *
             * @param client the client to send the entities to
             */
            void sendAllEntity(std::shared_ptr<RType::ClientServer> client);

            // Attributes
            /**
             * @brief The bool to stop the game loop
             *
             */
            bool _stopLoop;
            /**
             * @brief The mutex to lock the access to the coordinator
             *
             */
            std::mutex _mtx;
            /**
             * @brief The thread to run the game loop
             *
             */
            std::thread _gameLoop;
            /**
             * @brief The boost udp socket to send and receive messages from clients
             *
             */
            udp::socket _socket;
            /**
             * @brief The boost udp endpoint to store the remote endpoint
             *
             */
            udp::endpoint _remoteEndpoint;
            /**
             * @brief The buffer to store the received messages
             *
             */
            std::array<unsigned char, MAX_SIZE> _recvBuffer;
            /**
             * @brief The vector to store all the connected clients
             *
             */
            std::vector<std::shared_ptr<ClientServer>> _clients;
            /**
             * @brief The command factory to create commands
             *
             */
            CommandFactory _commandFactory;
            /**
             * @brief The coordinator to handle the ECS
             *
             */
            RType::Coordinator _coord;
    };
}

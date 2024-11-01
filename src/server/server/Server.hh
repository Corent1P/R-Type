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
            /**
             * @brief Stop the server
             *
             */
            void stop(bool fromCli = false);

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
             * @brief Create a new client
             *
             * @return std::shared_ptr<RType::ClientServer> the created client
             */
            std::shared_ptr<RType::ClientServer> createClient(void);
            /**
             * @brief Remove a client
             *
             * @param client the client to remove
             */
            void removeClient(std::shared_ptr<RType::ClientServer> client);
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
             * @brief Remove all the following objects of a client
             *
             * @param id the id of the client
             */
            void removeFollowingObjects(long id);
            /**
             * @brief Handle the command received by the client
             *
             * @param receivInfo the received command
             * @param connectedClient the connected client
             */
            void handleCommand(std::pair<RType::PacketType, std::vector<long>> receivInfo, std::shared_ptr<ClientServer> connectedClient);

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
            /**
             * @brief Run the CLI
             *
             */
            void runCli(void);
            /**
             * @brief a get line that has a timeout
             *
             * @return std::string the string getted in the getline
             * @return "" an empty string when it has timeout
             */
            std::string customGetLine(void);
            /**
             * @brief List all the players connected
             *
             */
            void listPlayers(void);
            /**
             * @brief change the difficulty of the game
             *
             * @param difficulty the command
             */
            void changeDifficulty(std::string difficulty);
            /**
             * @brief Kick a player
             *
             * @param player the player to kick
             */
            void kickPlayer(std::string player);
            /**
             * @brief Change the level of the game
             *
             * @param level the level to change to
             */
            void changeLevel(std::string level);
            /**
             * @brief Print the help of the CLI
             *
             */
            void printCliHelp(void);
            /**
             * @brief remove all the ennemies
             *
             */
            void removeAllEnnemies(void);

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
             * @brief The thread to run the cli
             *
             */
            std::thread _cliThread;
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

            /**
             * @brief The bool to represent if the game has started
             *
             */
            bool _gameHasStarted;
    };
}

/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** StartCommand
*/

#pragma once
#include "../ACommand.hh"

namespace RType {
    /**
     * @brief A class that represents a Start command. Inherits from ACommand abstract class (cf. ACommand)
     */
    class StartCommand : public ACommand {
        public:
            /**
             * @brief Construct a new StartCommand object
             *
             * @param data is a string argument that contains the data of the Command
             */
            StartCommand(std::string data);

            /**
             * @brief Execute the command
             *
             * @param socket the socket to send the response
             * @param client the client that sent the command
             */
            void execute(udp::socket &socket, std::shared_ptr<Client> client);
    };
}

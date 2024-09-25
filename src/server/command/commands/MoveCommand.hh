/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** MoveCommand
*/

#pragma once
#include "../ACommand.hh"

namespace RType {
    /**
     * @brief A class that represents a Move command. Inherits from ACommand abstract class (cf. ACommand)
     */
    class MoveCommand : public ACommand {
        public:
            /**
             * @brief Construct a new MoveCommand object
             *
             * @param data is a string argument that contains the data of the Command
             */
            MoveCommand(std::string data);

            /**
             * @brief Execute the command
             *
             * @param socket the socket to send the response
             * @param client the client that sent the command
             */
            void execute(udp::socket &socket, std::shared_ptr<Client> client);
    };
}

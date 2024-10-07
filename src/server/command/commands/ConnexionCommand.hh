/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** ConnexionCommand
*/

#pragma once
#include "../ACommand.hh"

namespace RType {
    /**
     * @brief A class that represents a Move command. Inherits from ACommand abstract class (cf. ACommand)
     */
    class ConnexionCommand : public ACommand {
        public:
            /**
             * @brief Construct a new ConnexionCommand object
             *
             * @param data is a string argument that contains the data of the Command
             */
            ConnexionCommand(const std::vector<long> &arguments);

            /**
             * @brief Execute the command
             *
             * @param socket the socket to send the response
             * @param client the client that sent the command
             */
            void execute(std::shared_ptr<ClientServer> client, FUNCTION_SEND sendToClient, FUNCTION_SEND sendToAll) override;
    };
}
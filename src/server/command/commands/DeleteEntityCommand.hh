/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** DeleteEntityCommand
*/

#pragma once
#include "../ACommand.hh"

namespace RType {
    /**
     * @brief A class that represents a DeleteEntity command. Inherits from ACommand abstract class (cf. ACommand)
     */
    class DeleteEntityCommand : public ACommand {
        public:
            /**
             * @brief Construct a new DeleteEntityCommand object
             *
             * @param data is a vector arguments that contains the data of the Command
             */
            DeleteEntityCommand(const std::vector<long> &arguments);

            /**
             * @brief Execute the command
             *
             * @param socket the socket to send the response
             * @param client the client that sent the command
             */
            void execute(std::shared_ptr<ClientServer> client, FUNCTION_SEND sendToClient, FUNCTION_SEND sendToAll, Coordinator &coord) override;
    };
}

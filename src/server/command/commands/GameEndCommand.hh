/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** GameEndCommand
*/

#pragma once
#include "../ACommand.hh"

namespace RType {
    /**
     * @brief A class that represents a GameEnd command. Inherits from ACommand abstract class (cf. ACommand)
     */
    class GameEndCommand : public ACommand {
        public:
            /**
             * @brief Construct a new GameEndCommand object
             *
             * @param data is a vector arguments that contains the data of the Command
             */
            GameEndCommand(const std::vector<long> &data);

            /**
             * @brief Execute the command
             *
             * @param socket the socket to send the response
             * @param client the client that sent the command
             */
            void execute(std::shared_ptr<ClientServer> client, FUNCTION_SEND sendToClient, FUNCTION_SEND sendToAll, Coordinator &coord) override;
    };
}

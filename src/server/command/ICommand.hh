/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** ICommand
*/

#pragma once

#include "../clientServer/ClientServer.hh"

namespace RType {
    /**
     * @brief An enum to differentiate the type of all the commands
     *
     */
    enum CommandType {
        MOVE,
        SHOOT,
        START,
        OTHER
    };

    /**
     * @brief An interface that represents a command
     *
     */
    class ICommand {
        public:
            /**
             * @brief Destroy the ICommand object
             *
             */
            virtual ~ICommand() = default;

            /**
             * @brief Get the Type member of the object
             *
             * @return CommandType the type of the Command (cf. CommandType)
             */
            virtual CommandType getType(void) const = 0;

            /**
             * @brief Get the Data member of the object
             *
             * @return std::string the data of the object
             */
            virtual std::string getData(void) const = 0;

            /**
             * @brief Execute the command
             *
             * @param socket the socket to send the response
             * @param client the client that sent the command
             */
            virtual void execute(udp::socket &socket, std::shared_ptr<ClientServer> client) = 0;
    };
}

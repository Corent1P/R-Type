/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** ICommand
*/

#pragma once

#include "../clientServer/ClientServer.hh"
#include "../../protocolHandler/Encoder.hh"

#define FUNCTION_SEND std::function<void(const std::basic_string<unsigned char>&)>

namespace RType {
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
             * @return PacketType the type of the Command (cf. PacketType)
             */
            virtual PacketType getType(void) const = 0;

            /**
             * @brief Get the Data member of the object
             *
             * @return std::string the data of the object
             */
            virtual std::vector<long> getData(void) const = 0;

            /**
             * @brief execute the command
             *
             * @param client the client that send the command
             * @param sendToClient the function that will send the message to the client
             * @param sendToAll the function that will send the message to all the connected client
             */
            virtual void execute(std::shared_ptr<ClientServer> client, FUNCTION_SEND sendToClient, FUNCTION_SEND sendToAll, Coordinator &coord) = 0;
    };
}

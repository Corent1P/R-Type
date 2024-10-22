/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** AckMissingCommand
*/

#pragma once
#include "../ACommand.hh"

namespace RType {
    /**
     * @brief A class that represents a ActionPlayer command. Inherits from ACommand abstract class (cf. ACommand)
     */
    class AckMissingCommand : public ACommand {
        public:
            /**
             * @brief Construct a new AckMissingCommand object
             *
             * @param data is a vector arguments that contains the data of the Command
             */
            AckMissingCommand(const COMMAND_ARGS &arguments);

            /**
             * @brief Execute the command
             *
             * @param socket the socket to send the response
             * @param client the client that sent the command
             */
            void execute(std::shared_ptr<ClientServer> client, FUNCTION_SEND sendToClient, FUNCTION_SEND sendToAll, Coordinator &coord) override;

        private:
            /**
             * @brief Get the lost packet with its id
             *
             * @param client the client that sent the command
             * @param packetId the id of the packet
             * @return U_STRING the lost packet
             */
            int getIndexLostPacketWithId(std::vector<U_STRING> &sentPackets, u_int8_t packetId);
            /**
             * @brief Check if a value is in a vector
             *
             * @param tab the vector to check
             * @param value the value to check
             * @return true if the value is in the vector, false otherwise
             */
            bool inVector(const std::vector<int32_t> &tab, u_int8_t value);
    };
}

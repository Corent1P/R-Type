/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** ActionPlayerCommand
*/

#pragma once
#include "../ACommand.hh"

namespace RType {
    /**
     * @brief A class that represents a ActionPlayer command. Inherits from ACommand abstract class (cf. ACommand)
     */
    class ActionPlayerCommand : public ACommand {
        public:
            /**
             * @brief Construct a new ActionPlayerCommand object
             *
             * @param data is a vector arguments that contains the data of the Command
             */
            ActionPlayerCommand(const std::vector<long> &arguments);

            /**
             * @brief Execute the command
             *
             * @param socket the socket to send the response
             * @param client the client that sent the command
             */
            void execute(std::shared_ptr<ClientServer> client, FUNCTION_SEND sendToClient, FUNCTION_SEND sendToAll, Coordinator &coord) override;
        private:
            /**
             * @brief Get the bullet position
             *
             * @param client the client that sent the command
             * @return sf::Vector2f the position of the bullet
             */
            sf::Vector2f getBulletPosition(std::shared_ptr<ClientServer> client);
            /**
             * @brief Get the bullet size
             *
             * @param entityType the type of the bullet
             * @return sf::Vector2f the size of the bullet
             */
            sf::Vector2f getBulletSize(WeaponType weaponType);
    };
}
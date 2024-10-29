/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** CommandFactory
*/

#pragma once

#include "../ICommand.hh"
#include "../commands/ConnexionCommand.hh"
#include "../commands/DisconnexionCommand.hh"
#include "../commands/NewEntityCommand.hh"
#include "../commands/DeleteEntityCommand.hh"
#include "../commands/MoveEntityCommand.hh"
#include "../commands/InfoLevelCommand.hh"
#include "../commands/InfoEntityCommand.hh"
#include "../commands/MovePlayerCommand.hh"
#include "../commands/ActionPlayerCommand.hh"
#include "../commands/GameStartCommand.hh"
#include "../commands/GameEndCommand.hh"
#include "../commands/AckMissingCommand.hh"
#include "../../Error.hh"

namespace RType {
    /**
     * @brief A class that creates commands object
     *
     */
    class CommandFactory {
        public:
            /**
             * @brief Construct a new CommandFactory object
             *
             */
            CommandFactory();

            /**
             * @brief Destroy the CommandFactory object
             *
             */
            ~CommandFactory() = default;


            /**
             * @brief Create a Command object
             *
             * @param command the command to create
             * @return std::shared_ptr<ICommand> the created command (cf. ICommand interface)
             */
            std::shared_ptr<ICommand> createCommand(const PACKET &command);

        private:
            /**
             * @brief A map that contains the constructors of all the commands and its associated PacketType
             *
             */
            std::map<PacketType, std::function<std::shared_ptr<ICommand>(std::vector<long>)>> _constructors;
    };
}

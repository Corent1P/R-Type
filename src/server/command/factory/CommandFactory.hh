/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** CommandFactory
*/

#pragma once

#include "../ICommand.hh"
#include "../commands/MoveCommand.hh"
#include "../commands/ShootCommand.hh"
#include "../commands/StartCommand.hh"
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
            std::shared_ptr<ICommand> createCommand(const std::string &command);

        private:
            /**
             * @brief A map that contains the constructors of all the commands and its associated CommandType
             *
             */
            std::map<CommandType, std::function<std::shared_ptr<ICommand>(std::string data)>> _constructors;

            /**
             * @brief Get the CommandType of a command
             *
             * @param command the command to get the CommandType
             * @return CommandType the CommandType of the command
             */
            CommandType getCommandType(const std::string &command);
            /**
             * @brief Get the data of a command
             *
             * @param command the command to get the data
             * @return std::string the data of the command
             */
            std::string getCommandData(const std::string &command);
    };
}

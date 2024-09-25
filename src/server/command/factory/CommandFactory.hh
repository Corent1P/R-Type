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
    class CommandFactory {
        public:
            CommandFactory();
            ~CommandFactory() = default;

            std::shared_ptr<ICommand> createCommand(const std::string &command);

        private:
            std::map<CommandType, std::function<std::shared_ptr<ICommand>(std::string data)>> _constructors;

            CommandType getCommandType(const std::string &command);
            std::string getCommandData(const std::string &command);
    };
}

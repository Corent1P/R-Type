/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** MoveCommand
*/

#pragma once
#include "../ACommand.hh"

namespace RType {
    class MoveCommand : public ACommand {
        public:
            MoveCommand(std::string data);

            void execute(std::shared_ptr<Client> client);
    };
}

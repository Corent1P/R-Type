/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** StartCommand
*/

#pragma once
#include "../ACommand.hh"

namespace RType {
    class StartCommand : public ACommand {
        public:
            StartCommand(std::string data);

            void execute(std::shared_ptr<Client> client);
    };
}

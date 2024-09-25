/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** ShootCommand
*/

#pragma once
#include "../ACommand.hh"

namespace RType {
    class ShootCommand : public ACommand {
        public:
            ShootCommand(std::string data);

            void execute(std::shared_ptr<Client> client);
    };
}

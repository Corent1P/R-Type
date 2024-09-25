/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** ICommand
*/

#pragma once

#include "../client/Client.hh"

namespace RType {
    enum CommandType {
        MOVE,
        SHOOT,
        START,
        OTHER
    };

    class ICommand {
        public:
            virtual ~ICommand() = default;

            virtual void execute(udp::socket &socket, std::shared_ptr<Client> client) = 0;
    };
}

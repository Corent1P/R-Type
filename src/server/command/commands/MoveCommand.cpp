/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** MoveCommand
*/

#include "MoveCommand.hh"

RType::MoveCommand::MoveCommand(std::string data):
    ACommand(data, MOVE)
{
    std::cout << "Move command created" << std::endl;
}

void RType::MoveCommand::execute(udp::socket &socket, std::shared_ptr<ClientServer> client)
{
    client->sendMessage(socket, "Move command\n");
    std::cout << "execution of move command" << std::endl;
}

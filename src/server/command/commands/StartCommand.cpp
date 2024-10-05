/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** StartCommand
*/

#include "StartCommand.hh"

RType::StartCommand::StartCommand(std::string data):
    ACommand(data, START)
{
    std::cout << "start command created" << std::endl;
}

void RType::StartCommand::execute(udp::socket &socket, std::shared_ptr<ClientServer> client)
{
    client->sendMessage(socket, "Start command\n");
    std::cout << "execution of start command" << std::endl;
}

/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** ShootCommand
*/

#include "ShootCommand.hh"

RType::ShootCommand::ShootCommand(std::string data):
    ACommand(data, SHOOT)
{
    std::cout << "shoot command created" << std::endl;
}

void RType::ShootCommand::execute(udp::socket &socket, std::shared_ptr<ClientServer> client)
{
    client->sendMessage(socket, "Shoot command");
    std::cout << "execution of shoot command" << std::endl;
}

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

void RType::ShootCommand::execute(std::shared_ptr<Client> client)
{
    std::cout << "execution of shoot command" << std::endl;
}

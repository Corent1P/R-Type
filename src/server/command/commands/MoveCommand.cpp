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

void RType::MoveCommand::execute(std::shared_ptr<Client> client)
{
    std::cout << "execution of move command" << std::endl;
}

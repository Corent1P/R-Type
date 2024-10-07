/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** ActionPlayerCommand
*/

#include "ActionPlayerCommand.hh"

RType::ActionPlayerCommand::ActionPlayerCommand(const std::vector<long> &data):
    ACommand(data, ACTION_PLAYER)
{
    std::cout << "Action command created" << std::endl;
}

void RType::ActionPlayerCommand::execute(std::shared_ptr<ClientServer> client, FUNCTION_SEND sendToClient, FUNCTION_SEND sendToAll)
{
    std::cout << "execution of action command" << std::endl;
}

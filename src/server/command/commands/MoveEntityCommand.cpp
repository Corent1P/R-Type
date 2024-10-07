/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** MoveEntityCommand
*/

#include "MoveEntityCommand.hh"

RType::MoveEntityCommand::MoveEntityCommand(const std::vector<long> &arguments):
    ACommand(arguments, MOVE_ENTITY)
{
    std::cout << "MoveEntityCommand command created" << std::endl;
}

void RType::MoveEntityCommand::execute(std::shared_ptr<Client> client, FUNCTION_SEND sendToClient, FUNCTION_SEND sendToAll)
{
    std::cout << "execution of move entity command" << std::endl;
}

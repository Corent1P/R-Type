/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** DeleteEntityCommand
*/

#include "DeleteEntityCommand.hh"

RType::DeleteEntityCommand::DeleteEntityCommand(const std::vector<long> &arguments):
    ACommand(arguments, DELETE_ENTITY)
{
    std::cout << "DeleteEntity command created" << std::endl;
}

void RType::DeleteEntityCommand::execute(std::shared_ptr<Client> client, FUNCTION_SEND sendToClient, FUNCTION_SEND sendToAll)
{
    std::cout << "execution of delete entity command" << std::endl;
}
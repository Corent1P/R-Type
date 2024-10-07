/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** NewEntityCommand
*/

#include "NewEntityCommand.hh"

RType::NewEntityCommand::NewEntityCommand(const std::vector<long> &arguments):
    ACommand(arguments, NEW_ENTITY)
{
    std::cout << "NewEntity command created" << std::endl;
}

void RType::NewEntityCommand::execute(std::shared_ptr<ClientServer> client, FUNCTION_SEND sendToClient, FUNCTION_SEND sendToAll)
{
    std::cout << "execution of new entity command" << std::endl;
}
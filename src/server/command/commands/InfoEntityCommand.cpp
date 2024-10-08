/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** InfoEntityCommand
*/

#include "InfoEntityCommand.hh"

RType::InfoEntityCommand::InfoEntityCommand(const std::vector<long> &arguments):
    ACommand(arguments, INFO_ENTITY)
{
    std::cout << "InfoEntity command created" << std::endl;
}

void RType::InfoEntityCommand::execute(std::shared_ptr<ClientServer> client, FUNCTION_SEND sendToClient, FUNCTION_SEND sendToAll, Coordinator &coord)
{
    std::cout << "execution of info entity command" << std::endl;
}

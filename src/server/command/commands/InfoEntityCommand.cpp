/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** InfoEntityCommand
*/

#include "InfoEntityCommand.hh"

RType::InfoEntityCommand::InfoEntityCommand(const COMMAND_ARGS &arguments):
    ACommand(arguments, INFO_ENTITY)
{
    std::cout << "InfoEntity command created" << std::endl;
}

void RType::InfoEntityCommand::execute(std::shared_ptr<ClientServer> client, FUNCTION_SEND sendToClient, FUNCTION_SEND sendToAll, Coordinator &coord)
{
    (void)client;
    (void)sendToClient;
    (void)sendToAll;
    (void)coord;
    std::cout << "execution of info entity command" << std::endl;
}

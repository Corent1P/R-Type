/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** InfoLevelCommand
*/

#include "InfoLevelCommand.hh"

RType::InfoLevelCommand::InfoLevelCommand(const std::vector<long> &arguments):
    ACommand(arguments, INFO_LEVEL)
{
    std::cout << "InfoLevel command created" << std::endl;
}

void RType::InfoLevelCommand::execute(std::shared_ptr<ClientServer> client, FUNCTION_SEND sendToClient, FUNCTION_SEND sendToAll, Coordinator &coord)
{
    (void)client;
    (void)sendToClient;
    (void)sendToAll;
    (void)coord;
    std::cout << "execution of info level command" << std::endl;
}

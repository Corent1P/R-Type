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
    (void)sendToAll;
    int level = 0; //? ask Corentin how to get the level

    sendToClient(Encoder::infoLevel(level));
}

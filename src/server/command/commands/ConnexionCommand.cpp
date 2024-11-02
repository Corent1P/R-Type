/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** ConnexionCommand
*/

#include "ConnexionCommand.hh"

RType::ConnexionCommand::ConnexionCommand(const std::vector<long> &arguments):
    ACommand(arguments, CONNEXION)
{
}

void RType::ConnexionCommand::execute(std::shared_ptr<ClientServer> client, FUNCTION_SEND sendToClient, FUNCTION_SEND sendToAll, Coordinator &coord)
{
    (void)client;
    (void)sendToClient;
    (void)sendToAll;
    (void)coord;
    // TODO: implement the command itself
}



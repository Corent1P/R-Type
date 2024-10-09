/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** ConnexionCommand
*/

#include "ConnexionCommand.hh"

RType::ConnexionCommand::ConnexionCommand(const COMMAND_ARGS &arguments):
    ACommand(arguments, CONNEXION)
{
    std::cout << "Connexion command created" << std::endl;
}

void RType::ConnexionCommand::execute(std::shared_ptr<ClientServer> client, FUNCTION_SEND sendToClient, FUNCTION_SEND sendToAll, Coordinator &coord)
{
    (void)client;
    (void)sendToClient;
    (void)sendToAll;
    (void)coord;
    std::cout << "execution of connexion command" << std::endl;
    // TODO: implement the command itself
}



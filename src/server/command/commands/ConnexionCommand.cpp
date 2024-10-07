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
    std::cout << "Connexion command created" << std::endl;
}

void RType::ConnexionCommand::execute(std::shared_ptr<ClientServer> client, FUNCTION_SEND sendToClient, FUNCTION_SEND sendToAll)
{
    std::cout << "execution of connexion command" << std::endl;
    // TODO: implement the command itself
}



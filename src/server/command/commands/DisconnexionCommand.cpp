/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** DisconnexionCommand
*/

#include "DisconnexionCommand.hh"

RType::DisconnexionCommand::DisconnexionCommand(const std::vector<long> &arguments):
    ACommand(arguments, DISCONNEXION)
{
    std::cout << "Disconnexion command created" << std::endl;
}

void RType::DisconnexionCommand::execute(std::shared_ptr<Client> client, FUNCTION_SEND sendToClient, FUNCTION_SEND sendToAll)
{
    std::cout << "execution of disconnexion command" << std::endl;
}

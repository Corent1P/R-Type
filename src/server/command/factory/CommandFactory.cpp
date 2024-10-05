/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** CommandFactory
*/

#include "CommandFactory.hh"

// TODO: check if the throw error is catch or not
RType::CommandFactory::CommandFactory()
{
    _constructors.insert({MOVE_PLAYER, [](const std::vector<long> &data){return std::shared_ptr<ICommand>(new MovePlayerCommand(data));}});
    // TODO implement the other commands
    // _constructors.insert({SHOOT, [](std::string data){return std::shared_ptr<ICommand>(new ShootCommand(data));}});
    // _constructors.insert({START, [](std::string data){return std::shared_ptr<ICommand>(new StartCommand(data));}});
}

std::shared_ptr<RType::ICommand> RType::CommandFactory::createCommand(const std::pair<RType::PacketType, std::vector<long>> &command)
{
    try {
        PacketType type = (PacketType)command.first;

        if (type == ERROR)
            throw Error("Unvalid Command sent from client");
        return _constructors[type](command.second);
    } catch(const Error &err) {
        std::cerr << "Error during command creation : " << err.what() << std::endl;
        return nullptr;
    }
}

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
    _constructors.insert({NEW_ENTITY, [](const std::vector<long> &data){return std::shared_ptr<ICommand>(new NewEntityCommand(data));}});
    _constructors.insert({DELETE_ENTITY, [](const std::vector<long> &data){return std::shared_ptr<ICommand>(new DeleteEntityCommand(data));}});
    _constructors.insert({MOVE_ENTITY, [](const std::vector<long> &data){return std::shared_ptr<ICommand>(new MoveEntityCommand(data));}});
    _constructors.insert({INFO_LEVEL, [](const std::vector<long> &data){return std::shared_ptr<ICommand>(new InfoLevelCommand(data));}});
    _constructors.insert({INFO_ENTITY, [](const std::vector<long> &data){return std::shared_ptr<ICommand>(new InfoEntityCommand(data));}});
    _constructors.insert({MOVE_PLAYER, [](const std::vector<long> &data){return std::shared_ptr<ICommand>(new MovePlayerCommand(data));}});
    _constructors.insert({ACTION_PLAYER, [](const std::vector<long> &data){return std::shared_ptr<ICommand>(new ActionPlayerCommand(data));}});
    _constructors.insert({GAME_START, [](const std::vector<long> &data){return std::shared_ptr<ICommand>(new GameStartCommand(data));}});
    _constructors.insert({GAME_END, [](const std::vector<long> &data){return std::shared_ptr<ICommand>(new GameEndCommand(data));}});
}

std::shared_ptr<RType::ICommand> RType::CommandFactory::createCommand(const std::pair<RType::PacketType, std::vector<long>> &command)
{
    try {
        PacketType type = (PacketType)command.first;

        if (type == ERROR || type == CONNEXION || type == DISCONNEXION)
            throw Error("Unvalid Command sent from client");
        return _constructors[type](command.second);
    } catch(const Error &err) {
        std::cerr << "Error during command creation : " << err.what() << std::endl;
        return nullptr;
    }
}

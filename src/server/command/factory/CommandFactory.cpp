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
    // TODO implement the commands
    _constructors.insert({CONNEXION, [](const COMMAND_ARGS &data){return std::shared_ptr<ICommand>(new ConnexionCommand(data));}});
    _constructors.insert({DISCONNEXION, [](const COMMAND_ARGS &data){return std::shared_ptr<ICommand>(new DisconnexionCommand(data));}});
    _constructors.insert({NEW_ENTITY, [](const COMMAND_ARGS &data){return std::shared_ptr<ICommand>(new NewEntityCommand(data));}});
    _constructors.insert({DELETE_ENTITY, [](const COMMAND_ARGS &data){return std::shared_ptr<ICommand>(new DeleteEntityCommand(data));}});
    _constructors.insert({MOVE_ENTITY, [](const COMMAND_ARGS &data){return std::shared_ptr<ICommand>(new MoveEntityCommand(data));}});
    _constructors.insert({INFO_LEVEL, [](const COMMAND_ARGS &data){return std::shared_ptr<ICommand>(new InfoLevelCommand(data));}});
    _constructors.insert({INFO_ENTITY, [](const COMMAND_ARGS &data){return std::shared_ptr<ICommand>(new InfoEntityCommand(data));}});
    _constructors.insert({MOVE_PLAYER, [](const COMMAND_ARGS &data){return std::shared_ptr<ICommand>(new MovePlayerCommand(data));}});
    _constructors.insert({ACTION_PLAYER, [](const COMMAND_ARGS &data){return std::shared_ptr<ICommand>(new ActionPlayerCommand(data));}});
    _constructors.insert({GAME_START, [](const COMMAND_ARGS &data){return std::shared_ptr<ICommand>(new GameStartCommand(data));}});
    _constructors.insert({GAME_END, [](const COMMAND_ARGS &data){return std::shared_ptr<ICommand>(new GameEndCommand(data));}});
}

std::shared_ptr<RType::ICommand> RType::CommandFactory::createCommand(const PACKET &command)
{
    try {
        PacketType type = (PacketType)command.first.first;

        if (type == ERROR)
            throw Error("Unvalid Command sent from client");
        return _constructors[type](command.second);
    } catch(const Error &err) {
        std::cerr << "Error during command creation : " << err.what() << std::endl;
        return nullptr;
    }
}

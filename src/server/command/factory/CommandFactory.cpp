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
    _constructors.insert({MOVE, [](std::string data){return std::shared_ptr<ICommand>(new MoveCommand(data));}});
    _constructors.insert({SHOOT, [](std::string data){return std::shared_ptr<ICommand>(new ShootCommand(data));}});
    _constructors.insert({START, [](std::string data){return std::shared_ptr<ICommand>(new StartCommand(data));}});
}

std::shared_ptr<RType::ICommand> RType::CommandFactory::createCommand(const std::string &command)
{
    try {
        CommandType commandType = getCommandType(command);
        std::string commandData = getCommandData(command);

        if (commandType == OTHER)
            throw Error("Unvalid Command sent from client");
        return _constructors[commandType](commandData);
    } catch(const Error &err) {
        std::cerr << "Error during command creation : " << err.what() << std::endl;
        return nullptr;
    }
}

RType::CommandType RType::CommandFactory::getCommandType(const std::string &command)
{
	std::string commandLabel = command.substr(0, command.find(' '));

    std::vector<std::string> commandLabels = {"Move", "Shoot", "Start"};
    for (int i = 0; i < commandLabels.size(); i++)
        if (commandLabels[i] == commandLabel)
            return (CommandType(i));
    return OTHER;
}

std::string RType::CommandFactory::getCommandData(const std::string &command)
{
    int positionBegin = command.find(' ');
    if (positionBegin == command.npos)
        throw Error("Invalid command, no data");
	return command.substr(positionBegin + 1);
}

/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** ACommand
*/

#include "ACommand.hh"

RType::ACommand::ACommand(const std::string &data, CommandType type):
    _data(data), _type(type)
{
}

std::string RType::ACommand::getData(void) const
{
	return _data;
}

RType::CommandType RType::ACommand::getType(void) const
{
	return _type;
}

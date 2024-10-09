/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** ACommand
*/

#include "ACommand.hh"

RType::ACommand::ACommand(const COMMAND_ARGS &data, PacketType type):
    _data(data), _type(type)
{
}

COMMAND_ARGS RType::ACommand::getData(void) const
{
	return _data;
}

RType::PacketType RType::ACommand::getType(void) const
{
	return _type;
}

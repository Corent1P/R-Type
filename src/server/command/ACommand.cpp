/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** ACommand
*/

#include "ACommand.hh"

RType::ACommand::ACommand(const std::vector<long> &data, PacketType type):
    _data(data), _type(type)
{
}

std::vector<long> RType::ACommand::getData(void) const
{
	return _data;
}

RType::PacketType RType::ACommand::getType(void) const
{
	return _type;
}

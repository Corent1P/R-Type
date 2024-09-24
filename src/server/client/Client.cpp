/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Client
*/

#include "Client.hh"

RType::Client::Client(boost::asio::ip::port_type portNumber, boost::asio::ip::address adress):
    _portNumber(portNumber), _address(adress), _isConnected(true)
{
    std::cout << "Client created with adress " << _address << ":" << _portNumber << std::endl;
}

void RType::Client::setIsConnected(bool isConnected)
{
	_isConnected = isConnected;
}

bool RType::Client::getIsConnected(void) const
{
	return _isConnected;
}

void RType::Client::setPortNumber(boost::asio::ip::port_type portNumber)
{
	_portNumber = portNumber;
}

boost::asio::ip::port_type RType::Client::getPortNumber(void) const
{
	return _portNumber;
}

void RType::Client::setAddress(boost::asio::ip::address address)
{
	_address = address;
}

boost::asio::ip::address RType::Client::getAddress(void) const
{
	return _address;
}

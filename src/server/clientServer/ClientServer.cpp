/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** ClientServer
*/

#include "ClientServer.hh"

RType::ClientServer::ClientServer(boost::asio::ip::udp::endpoint endpoint):
	_endpoint(endpoint), _portNumber(_endpoint.port()), _address(_endpoint.address()), _isConnected(true), _entity(nullptr)
{
}

void RType::ClientServer::setIsConnected(bool isConnected)
{
	_isConnected = isConnected;
}

bool RType::ClientServer::getIsConnected(void) const
{
	return _isConnected;
}

void RType::ClientServer::setPortNumber(std::size_t portNumber)
{
	_portNumber = portNumber;
}

std::size_t RType::ClientServer::getPortNumber(void) const
{
	return _portNumber;
}

void RType::ClientServer::setAddress(boost::asio::ip::address address)
{
	_address = address;
}

boost::asio::ip::address RType::ClientServer::getAddress(void) const
{
	return _address;
}

void RType::ClientServer::sendMessage(udp::socket &socket, const std::string &message)
{
	socket.async_send_to(boost::asio::buffer(message), _endpoint,
		[this, message](const boost::system::error_code &error, std::size_t bytes_transferred) {
            sendCallback(message, error, bytes_transferred);
        }
	);
}

void RType::ClientServer::sendMessage(udp::socket &socket, const std::basic_string<unsigned char> &message)
{
	socket.async_send_to(boost::asio::buffer(message), _endpoint,
		[this, message](const boost::system::error_code &error, std::size_t bytes_transferred) {
            sendCallback(message, error, bytes_transferred);
        }
	);
}

void RType::ClientServer::sendCallback(const std::string &, const boost::system::error_code &error, std::size_t bytesTransferred)
{
	(void)error;
	(void)bytesTransferred;
}

void RType::ClientServer::sendCallback(const std::basic_string<unsigned char> &, const boost::system::error_code &error, std::size_t bytesTransferred)
{
	(void)error;
	(void)bytesTransferred;
}

boost::asio::ip::udp::endpoint RType::ClientServer::getEndpoint(void) const
{
	return _endpoint;
}

bool RType::ClientServer::operator==(const RType::ClientServer &other) const
{
	return _entity->getId() == other.getEntity()->getId();
}

std::shared_ptr<RType::Entity> RType::ClientServer::getEntity(void) const
{
	return _entity;
}

void RType::ClientServer::setEntity(std::shared_ptr<RType::Entity> entity)
{
	_entity = entity;
}

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
	std::cout << "ClientServer created with adress " << _address << ":" << _portNumber << std::endl;
}

void RType::ClientServer::setIsConnected(bool isConnected)
{
	_isConnected = isConnected;
}

bool RType::ClientServer::getIsConnected(void) const
{
	return _isConnected;
}

void RType::ClientServer::setPortNumber(boost::asio::ip::port_type portNumber)
{
	_portNumber = portNumber;
}

boost::asio::ip::port_type RType::ClientServer::getPortNumber(void) const
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
	// if (!error) {
    //     std::cout << "Sent response to client, bytes transferred: " << bytesTransferred << std::endl;
    // } else {
    //     std::cout << "Error on send: " << error.message() << std::endl;
    // }
}

void RType::ClientServer::sendCallback(const std::basic_string<unsigned char> &, const boost::system::error_code &error, std::size_t bytesTransferred)
{
	(void)error;
	(void)bytesTransferred;
	// if (!error) {
    //     std::cout << "Sent response to client, bytes transferred: " << bytesTransferred << std::endl;
    // } else {
    //     std::cout << "Error on send: " << error.message() << std::endl;
    // }
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

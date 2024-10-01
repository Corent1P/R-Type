/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Client
*/

#include "Client.hh"

RType::Client::Client(boost::asio::ip::udp::endpoint endpoint, std::size_t id):
	_endpoint(endpoint), _portNumber(_endpoint.port()), _address(_endpoint.address()), _isConnected(true), _id(id), _position({10., 10.})
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

std::size_t RType::Client::getId(void) const
{
	return _id;
}

void RType::Client::sendMessage(udp::socket &socket, const std::string &message)
{
	socket.async_send_to(boost::asio::buffer(message), _endpoint,
		[this, message](const boost::system::error_code &error, std::size_t bytes_transferred) {
            sendCallback(message, error, bytes_transferred);
        }
	);
}

void RType::Client::sendMessage(udp::socket &socket, const std::basic_string<unsigned char> &message)
{
	socket.async_send_to(boost::asio::buffer(message), _endpoint,
		[this, message](const boost::system::error_code &error, std::size_t bytes_transferred) {
            sendCallback(message, error, bytes_transferred);
        }
	);
}

void RType::Client::sendCallback(const std::string &, const boost::system::error_code &error, std::size_t bytesTransferred)
{
	if (!error) {
        std::cout << "Sent response to client, bytes transferred: " << bytesTransferred << std::endl;
    } else {
        std::cout << "Error on send: " << error.message() << std::endl;
    }
}

void RType::Client::sendCallback(const std::basic_string<unsigned char> &, const boost::system::error_code &error, std::size_t bytesTransferred)
{
	if (!error) {
        std::cout << "Sent response to client, bytes transferred: " << bytesTransferred << std::endl;
    } else {
        std::cout << "Error on send: " << error.message() << std::endl;
    }
}

boost::asio::ip::udp::endpoint RType::Client::getEndpoint(void) const
{
	return _endpoint;
}

std::pair<double, double> RType::Client::getPosition(void) const
{
	return _position;
}

void RType::Client::setPosition(std::pair<double, double> position)
{
	_position = position;
}

void RType::Client::setPosition(double x, double y)
{
	_position.first = x;
	_position.second = y;
}

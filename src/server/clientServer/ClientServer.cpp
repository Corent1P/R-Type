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

void displayPackets(std::array<U_STRING, MAX_PACKETS> &packets)
{
	for (std::size_t i = 0; i < MAX_PACKETS; i++) {
		std::cout << "[" << i << " = ";
		if (packets[i].size() > 0)
			for (const auto &byte: packets[i])
				std::cout << (int)byte << " ";
		else
			std::cout << "empty";
		std::cout << "]" << std::endl;
	}
}

bool importantType(RType::PacketType type)
{
    return type == RType::CONNEXION ||
        type == RType::DISCONNEXION ||
        type == RType::ACK_MISSING || //not implemented yet
        type == RType::GAME_START ||
        type == RType::GAME_END ||
        type == RType::INFO_LEVEL ||
        type == RType::NEW_ENTITY ||
        type == RType::DELETE_ENTITY;
}

void RType::ClientServer::sendMessage(udp::socket &socket, const std::basic_string<unsigned char> &message)
{
    U_STRING messageNumbered = Encoder::addPacketNumber(message, _packetId);
    socket.async_send_to(boost::asio::buffer(messageNumbered), _endpoint,
        [this, messageNumbered](const boost::system::error_code &error, std::size_t bytes_transferred) {
            sendCallback(messageNumbered, error, bytes_transferred);
        }
	);
    PacketType type = Decoder::getType(messageNumbered);
    if (importantType(type))
        _packetsSent.push_back(messageNumbered);
    _packetId = (_packetId + 1) % MAX_PACKETS;
	// displayPackets(_packetsSent);
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

void RType::ClientServer::sendCallback(const U_STRING &, const boost::system::error_code &error, std::size_t bytesTransferred)
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

const std::vector<U_STRING> &RType::ClientServer::getPacketsSent(void) const
{
    return _packetsSent;
}

void RType::ClientServer::resetPacketsSent(void)
{
    _packetsSent.clear();
}
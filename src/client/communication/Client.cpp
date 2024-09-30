/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Client
*/

#include "Client.hh"

RType::Client::Client(boost::asio::io_context &ioContext, const std::string &host, const std::string &port):
    _ioContext(ioContext), _socket(ioContext, udp::endpoint(udp::v4(), 0))
{
    try {
        udp::resolver resolver(_ioContext);
		udp::resolver::query query(udp::v4(), host, port);
		udp::resolver::iterator iter = resolver.resolve(query);
		_endpoint = *iter;
    } catch(std::exception &err) {
        throw err;
    }
}

RType::Client::~Client()
{
    _socket.close();
}

void RType::Client::send(const std::string &message)
{
    _socket.send_to(boost::asio::buffer(message, message.size()), _endpoint);
}

std::string RType::Client::receive(void)
{
    std::array<char, 128> recvBuf;
    udp::endpoint senderEndpoint;
    size_t len = _socket.receive_from(boost::asio::buffer(recvBuf), senderEndpoint);
    return std::string(recvBuf.data(), len);
}

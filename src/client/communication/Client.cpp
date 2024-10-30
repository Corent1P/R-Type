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
    udp::resolver resolver(_ioContext);
    udp::resolver::query query(udp::v4(), host, port);
    boost::system::error_code ec;
    udp::resolver::results_type results = resolver.resolve(query, ec);
    if (ec || results.empty())
        throw ClientError("Unvalid connection");
    _endpoint = *results;
}

RType::Client::~Client()
{
    _socket.close();
}

void RType::Client::send(const std::basic_string<unsigned char> &message)
{
    boost::system::error_code ec;

    _socket.send_to(boost::asio::buffer(message, message.size()), _endpoint, 0, ec);
    if (ec)
        throw ClientError("Unable to send the message: " + ec.message());
}

std::basic_string<unsigned char> RType::Client::receive(void)
{
    std::array<unsigned char, 128> recvBuf; //* see if the size has to be changed
    udp::endpoint senderEndpoint;
    size_t len = _socket.receive_from(boost::asio::buffer(recvBuf), senderEndpoint);
    return std::basic_string<unsigned char>(recvBuf.data(), len);
}

void RType::Client::cancel(void)
{
    std::cout << "cancel Socket" << std::endl;
}

void RType::Client::logCommand(const PACKET &command)
{
    _packetsReceived.push_back(command.first.second);
}

void RType::Client::askForLostPackets(void)
{
    if (_packetsReceived.empty())
        return;
    std::cout << "packets received ===================================================" << std::endl;
    for (auto &packet: _packetsReceived)
        std::cout << packet << std::endl;
    std::cout << "packets received ===================================================" << std::endl;
    std::cout << "before sending" << std::endl;
    send(Encoder::ACKMissing(_packetsReceived));
    _packetsReceived.clear();
    std::cout << "packets cleared" << std::endl;
}

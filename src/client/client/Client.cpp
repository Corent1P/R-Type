#include "Client.hh"

RType::Client::Client(int port)
{
    try {
        udp::resolver resolver(_ioContext);
        udp::endpoint _receiverEndpoint = *resolver.resolve(udp::v4(), std::to_string(port), "daytime").begin();

        udp::socket socket(_ioContext);
        socket.open(udp::v4());
        socket.send_to(boost::asio::buffer(std::string("Hello from client")), _receiverEndpoint);

        std::string receiveBuffer;
        udp::endpoint senderEndpoint;
        size_t len = socket.receive_from(
            boost::asio::buffer(receiveBuffer), senderEndpoint);

        std::cout << receiveBuffer << std::endl;
    } catch(std::exception &err) {
        throw err;
    }
}

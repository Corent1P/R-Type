/*
** EPITECH PROJECT, 2024
** R-TYPE
** File description:
** R-TYPE server main
*/

#include <iostream>
#include <array>
#include "server/Server.hh"

void handleSignal(const boost::system::error_code &error, int signalNumber, boost::asio::io_context &ioContext)
{
    (void)signalNumber;
    if (!error)
        ioContext.stop();
}

int printHelp(int returnValue)
{
    std::cout << "USAGE: ./r-type_server <port>" << std::endl;
    std::cout << "\tport: the port where the server will listen for new connection." << std::endl;
    std::cout << "\t\tMust be a positive number." << std::endl;
    return returnValue;
}

int getPortArgument(int ac, char **av)
{
    if (ac != 2)
        return -1;
    int port = std::atoi(av[1]);
    if (!port)
        return -1;
    return port;
}

int main(int ac, char **av)
{
    if (ac == 2 && (std::string(av[1]) == "--help" || std::string(av[1]) == "-h"))
        return printHelp(0);
    try {
        int port = getPortArgument(ac, av);
        if (port == -1)
            return printHelp(84);
        boost::asio::io_context ioContext;
        RType::Server server(ioContext, port);
        boost::asio::signal_set signals(ioContext, SIGINT);

        signals.async_wait([&](const boost::system::error_code &error, int signalNumber) {
            handleSignal(error, signalNumber, ioContext);
        });
        ioContext.run();
        server.stop();
    } catch (const RType::EcsError &e) {
        std::cerr << "ECS Error: " << e.what() << std::endl;
        return 84;
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
}

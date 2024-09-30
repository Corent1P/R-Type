/*
** EPITECH PROJECT, 2024
** R-TYPE
** File description:
** R-TYPE client main
*/

#include <iostream>
#include <array>
#include "ClientError.hh"
#include "communication/Client.hh"

#include "Game.hh"

static int printHelp(int returnValue)
{
    std::cout << "USAGE: ./r-type_server <serverAdress> <serverPort>" << std::endl;
    std::cout << "\tserverAdress: the adress where the server is listening." << std::endl;
    std::cout << "\tserverPort: the port where the server is listening." << std::endl;
    std::cout << "\t\tMust be a positive number." << std::endl;
    return returnValue;
}

static bool errorHandling(int ac, char **av)
{
    if (ac != 3)
        return false;
    if (!atoi(av[2]))
        return false;
    return true;
}

int main(int ac, char **av)
{
    if (ac == 2 && (std::string(av[1]) == "--help" || std::string(av[1]) == "-h"))
        return printHelp(0);
    try {
        if (!errorHandling(ac, av))
            return printHelp(84);
        boost::asio::io_context ioContext;
        RType::Client client(ioContext, av[1], av[2]);
        RType::Game game;
        std::cout << game;
        game.gameLoop();
        // !to remove {
        client.send("Hello world");
        std::string msg = client.receive();
        std::cout << msg << std::endl;
        // !}
    }  catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    return 0;
}

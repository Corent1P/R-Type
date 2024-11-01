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

int main(int ac, char **av)
{
    std::string host = (ac >= 2 ? av[1] : "localhost");
    std::string port = (ac >= 3 ? av[2] : "4242");

    if (ac == 2 && (std::string(av[1]) == "--help" || std::string(av[1]) == "-h"))
        return printHelp(0);
    try {
        boost::asio::io_context ioContext;
        RType::Game game(ioContext, host, port);
        std::cout << game;
        game.gameLoop();
    } catch (const RType::EcsError &e) {
        std::cerr << "ECS Error: " << e.what() << std::endl;
        return 84;
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    } catch (...) {
        std::cerr << "Unknown error occurred." << std::endl;
        return 84;
    }
    return 0;
}

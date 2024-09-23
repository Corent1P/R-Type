/*
** EPITECH PROJECT, 2024
** R-TYPE
** File description:
** R-TYPE server main
*/

#include <iostream>
#include <array>
#include "server/Server.hh"

int main(void)
{
    try {
        boost::asio::io_context ioContext;
        RType::Server(ioContext, 4242);
        ioContext.run();
    } catch(std::exception &err) {
        std::cerr << "Error in server execution " << err.what() << std::endl;
    }
}

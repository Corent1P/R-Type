/*
** EPITECH PROJECT, 2024
** R-TYPE
** File description:
** R-TYPE client main
*/

#include <iostream>
#include <array>
#include "Error.hh"
#include "client/Client.hh"
#include <unistd.h> //! to remove

int main(int ac, char **av)
{
    (void)ac;
    (void)av;
    try {
        boost::asio::io_context ioContext;
        RType::Client client(ioContext, "localhost", "4242");
        //! to remove {
        client.send("Hello world");
        std::string msg = client.receive();
        std::cout << "Message from server " << msg << std::endl;
        sleep(5);
        client.send("Hello world 2");
        std::string msg2 = client.receive();
        std::cout << "Message from server " << msg2 << std::endl;
        //! }
    } catch(std::exception &err) {
        std::cerr << err.what() << std::endl;
        return 84;
    }
    return 0;
}

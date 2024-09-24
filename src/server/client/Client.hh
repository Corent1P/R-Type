/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Client
*/

#pragma once

#include "../includes.hh"

namespace RType {
    class Client {
        public:
            Client(boost::asio::ip::port_type portNumber, boost::asio::ip::address adress);
            ~Client() = default;

            void setIsConnected(bool isConnected);
            bool getIsConnected(void) const;

            void setPortNumber(boost::asio::ip::port_type portNumber);
            boost::asio::ip::port_type getPortNumber(void) const;

            void setAddress(boost::asio::ip::address address);
            boost::asio::ip::address getAddress(void) const;

        private:
            bool _isConnected;
            boost::asio::ip::port_type _portNumber;
            boost::asio::ip::address _address;
    };
}

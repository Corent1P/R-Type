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
            Client(boost::asio::ip::udp::endpoint endpoint);
            ~Client() = default;

            void setIsConnected(bool isConnected);
            bool getIsConnected(void) const;

            void setPortNumber(boost::asio::ip::port_type portNumber);
            boost::asio::ip::port_type getPortNumber(void) const;

            void setAddress(boost::asio::ip::address address);
            boost::asio::ip::address getAddress(void) const;

            boost::asio::ip::udp::endpoint getEndpoint(void) const;

            void sendMessage(udp::socket &socket, const std::string &message);

        private:
            udp::endpoint _endpoint;
            boost::asio::ip::port_type _portNumber;
            boost::asio::ip::address _address;
            bool _isConnected;

            void sendCallback(const std::string &message, const boost::system::error_code &error, std::size_t bytes_transferred);
    };
}

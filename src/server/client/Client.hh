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
            Client(boost::asio::ip::udp::endpoint endpoint, std::size_t id);
            ~Client() = default;

            void setIsConnected(bool isConnected);
            bool getIsConnected(void) const;

            void setPortNumber(boost::asio::ip::port_type portNumber);
            boost::asio::ip::port_type getPortNumber(void) const;

            void setAddress(boost::asio::ip::address address);
            boost::asio::ip::address getAddress(void) const;

            boost::asio::ip::udp::endpoint getEndpoint(void) const;
            std::size_t getId(void) const;

            void setPosition(std::pair<double, double> position);
            void setPosition(double x, double y);
            std::pair<double, double> getPosition(void) const;

            void sendMessage(udp::socket &socket, const std::string &message); //deprecated
            void sendMessage(udp::socket &socket, const std::basic_string<unsigned char> &message);

        private:
            udp::endpoint _endpoint;
            boost::asio::ip::port_type _portNumber;
            boost::asio::ip::address _address;
            bool _isConnected;
            std::size_t _id;
            std::pair<double, double> _position;

            void sendCallback(const std::string &message, const boost::system::error_code &error, std::size_t bytes_transferred); //deprecated
            void sendCallback(const std::basic_string<unsigned char> &message, const boost::system::error_code &error, std::size_t bytes_transferred);
    };
}

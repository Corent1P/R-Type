/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** ClientServer
*/

#pragma once

#include "../includes.hh"


namespace RType {
    class ClientServer {
        public:
            ClientServer(boost::asio::ip::udp::endpoint endpoint);
            ~ClientServer() = default;

            void setIsConnected(bool isConnected);
            bool getIsConnected(void) const;

            void setPortNumber(boost::asio::ip::port_type portNumber);
            boost::asio::ip::port_type getPortNumber(void) const;

            void setAddress(boost::asio::ip::address address);
            boost::asio::ip::address getAddress(void) const;

            boost::asio::ip::udp::endpoint getEndpoint(void) const;

            std::shared_ptr<RType::Entity> getEntity(void) const;
            void setEntity(std::shared_ptr<RType::Entity> entity);

            void sendMessage(udp::socket &socket, const std::string &message); //deprecated
            void sendMessage(udp::socket &socket, const std::basic_string<unsigned char> &message);

            bool operator==(const ClientServer &other) const;

        private:
            udp::endpoint _endpoint;
            boost::asio::ip::port_type _portNumber;
            boost::asio::ip::address _address;
            bool _isConnected;
            std::shared_ptr<RType::Entity> _entity;
            void sendCallback(const std::string &message, const boost::system::error_code &error, std::size_t bytes_transferred); //deprecated
            void sendCallback(const std::basic_string<unsigned char> &message, const boost::system::error_code &error, std::size_t bytes_transferred);
    };
}

/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** ClientServer
*/

#pragma once

#include "../includes.hh"


namespace RType {
    /**
     * @brief The ClientServer class representing a client
     *
     */
    class ClientServer {
        public:
            /**
             * @brief Construct a new ClientServer object
             *
             * @param endpoint the endpoint of the client
             */
            ClientServer(boost::asio::ip::udp::endpoint endpoint);
            /**
             * @brief Destroy the ClientServer object
             *
             */
            ~ClientServer() = default;

            /**
             * @brief Set the _isConnected attribute
             *
             * @param isConnected the value to set
             */
            void setIsConnected(bool isConnected);
            /**
             * @brief Get the _isConnected attribute
             *
             * @return bool the value of _isConnected
             */
            bool getIsConnected(void) const;

            /**
             * @brief Set the port number
             *
             * @param portNumber the port number to set
             */
            void setPortNumber(std::size_t portNumber);
            /**
             * @brief Get the port number
             *
             * @return std::size_t the port number
             */
            std::size_t getPortNumber(void) const;

            /**
             * @brief Set the address
             *
             * @param address the address to set
             */
            void setAddress(boost::asio::ip::address address);
            /**
             * @brief Get the address
             *
             * @return boost::asio::ip::address the address
             */
            boost::asio::ip::address getAddress(void) const;

            /**
             * @brief Get the endpoint
             *
             * @return boost::asio::ip::udp::endpoint the endpoint
             */
            boost::asio::ip::udp::endpoint getEndpoint(void) const;

            /**
             * @brief Get the entity
             *
             * @return std::shared_ptr<RType::Entity> the entity
             */
            std::shared_ptr<RType::Entity> getEntity(void) const;
            /**
             * @brief Set the entity
             *
             * @param entity the entity to set
             */
            void setEntity(std::shared_ptr<RType::Entity> entity);

            /**
             * @brief Send a message to the client
             *
             * @param socket the socket to send the message to
             * @param message the message to send
             * @deprecated use sendMessage(const std::basic_string<unsigned char> &message) instead
             */
            void sendMessage(udp::socket &socket, const std::string &message);
            /**
             * @brief Send a message to the client
             *
             * @param socket the socket to send the message to
             * @param message the message to send
             */
            void sendMessage(udp::socket &socket, const std::basic_string<unsigned char> &message);

            /**
             * @brief Overload of the == operator
             *
             * @param other the other ClientServer to compare
             * @return true if the two ClientServer are equal, false otherwise
             */
            bool operator==(const ClientServer &other) const;

            /**
             * @brief Get the packets sent
             *
             * @return the array of packets sent
             */
            const std::array<U_STRING, MAX_PACKETS> &getPacketsSent(void) const;

            /**
             * @brief Reset the packets sent array
             *
             */
            void resetPacketsSent(void);

        private:
            /**
             * @brief The endpoint of the client
             *
             */
            udp::endpoint _endpoint;
            /**
             * @brief The port number of the client
             *
             */
            std::size_t _portNumber;
            /**
             * @brief The address of the client
             *
             */
            boost::asio::ip::address _address;
            /**
             * @brief A bool to represent if the client is connected
             *
             */
            bool _isConnected;
            /**
             * @brief The player entity of the client
             *
             */
            std::shared_ptr<RType::Entity> _entity;
            /**
             * @brief the id of the last packet sent
             *
             */
            std::size_t _packetId = 0;
            /**
             * @brief the array to store the sent messages
             *
             */
            std::array<U_STRING, MAX_PACKETS> _packetsSent;

            /**
             * @brief the callback method after the sending of messages
             *
             * @param message string message
             * @param error the error code
             * @param bytes_transferred the number of bytes transferred
             * @deprecated use sendCallback(const std::basic_string<unsigned char> &message, const boost::system::error_code &error, std::size_t bytes_transferred) instead
             */
            void sendCallback(const std::string &message, const boost::system::error_code &error, std::size_t bytes_transferred);
            /**
             * @brief the callback method after the sending of messages
             *
             * @param message the basic string of unsigned char message
             * @param error the error code
             * @param bytes_transferred the number of bytes transferred
             */
            void sendCallback(const U_STRING &message, const boost::system::error_code &error, std::size_t bytes_transferred);
    };
}

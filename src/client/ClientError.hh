/*
** EPITECH PROJECT, 2024
** rType
** File description:
** Error
*/

#pragma once

#include <iostream>

namespace RType {
    /**
     * @brief ClientError class for handling client errors
     *
     */
    class ClientError: public std::exception {
        public:
            /**
             * @brief Construct a new ClientError object
             *
             * @param error (std::string) the error message
             */
            ClientError(std::string error);

            /**
             * @brief Contains the error message
             *
             * @return const char* the error message
             */
            const char *what() const noexcept override;

        private:
            /**
             * @brief the error message
             *
             */
            std::string _error;
    };
}

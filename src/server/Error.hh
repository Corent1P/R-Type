/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Error
*/

#pragma once

#include "includes.hh"

namespace RType {
    /**
     * @brief Error class, inherits from std::exception
     */
    class Error: public std::exception {
        public:
            /**
             * @brief Construct a new Error object
             *
             * @param error the error message
             */
            Error(std::string error);
            /**
             * @brief Returns the error message
             *
             * @return const char* the error message
             */
            const char *what() const noexcept override;

        private:
            /**
             * @brief The error message
             *
             */
            std::string _error;
    };
};

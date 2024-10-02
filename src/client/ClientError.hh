/*
** EPITECH PROJECT, 2024
** rType
** File description:
** Error
*/

#pragma once

#include <iostream>

namespace RType {
    class ClientError: public std::exception {
        public:
            ClientError(std::string error);
            const char *what() const noexcept override;

        private:
            std::string _error;
    };
}

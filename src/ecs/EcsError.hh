/*
** EPITECH PROJECT, 2024
** rType
** File description:
** EcsError
*/

#pragma once

#include <iostream>

namespace RType
{
    class EcsError: public std::exception {
        public:
            EcsError(std::string error);
            const char *what() const noexcept override;

        private:
            std::string _error;
    };
}
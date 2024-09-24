/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Error
*/

#pragma once

#include "includes.hh"

namespace RType {
    class Error: public std::exception {
        public:
            Error(std::string error);
            const char *what() const noexcept override;

        private:
            std::string _error;
    };
};

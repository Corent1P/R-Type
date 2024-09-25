/*
** EPITECH PROJECT, 2024
** rType
** File description:
** Error
*/

#include "Error.hh"

RType::Error::Error(std::string error):
    _error(error)
{
}

const char *RType::Error::what() const noexcept
{
    return _error.c_str();
}

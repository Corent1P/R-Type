/*
** EPITECH PROJECT, 2024
** rType
** File description:
** Error
*/

#include "ClientError.hh"

RType::ClientError::ClientError(std::string error):
    _error(error)
{
}

const char *RType::ClientError::what() const noexcept
{
    return _error.c_str();
}

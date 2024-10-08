/*
** EPITECH PROJECT, 2024
** rType
** File description:
** EcsError
*/

#include "EcsError.hh"

RType::EcsError::EcsError(std::string error):
    _error(error)
{
}

const char *RType::EcsError::what() const noexcept
{
    return _error.c_str();
}

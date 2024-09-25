/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** ACommand
*/

#pragma once

#include "ICommand.hh"

namespace RType {
    class ACommand : public ICommand {
        public:
            ACommand(const std::string &data, CommandType type);

            std::string getData(void) const;
            CommandType getType(void) const;

        protected:
            std::string _data;
            CommandType _type;
    };
}

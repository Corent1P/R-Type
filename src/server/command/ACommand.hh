/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** ACommand
*/

#pragma once

#include "ICommand.hh"

namespace RType {
    /**
     * @brief An abstract class that represents a command. Inherits from the ICommand interface
     *
     */
    class ACommand : public ICommand {
        public:
            /**
             * @brief Construct a new ACommand object
             *
             * @param data is a string argument that contains the data of the Command
             * @param type is the type of the Command (cf. CommandType)
             */
            ACommand(const std::string &data, CommandType type);

            /**
             * @brief Get the Data member of the object
             *
             * @return std::string the data of the object
             */
            std::string getData(void) const;

            /**
             * @brief Get the Type member of the object
             *
             * @return CommandType the type of the Command (cf. CommandType)
             */
            CommandType getType(void) const;

        protected:
            /**
             * @brief The data of the Command (ex.: "45" in the command "Move 45")
             *
             */
            std::string _data;
            /**
             * @brief The type of the Command (cf. CommandType)
             *
             */
            CommandType _type;
    };
}

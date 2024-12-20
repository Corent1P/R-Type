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
             * @param data is the vector that contains the data of the Command
             * @param type is the type of the Command (cf. PacketType)
             */
            ACommand(const std::vector<long> &data, PacketType type);

            /**
             * @brief Get the Data member of the object
             *
             * @return std::string the data of the object
             */
            std::vector<long> getData(void) const override;

            /**
             * @brief Get the Type member of the object
             *
             * @return PacketType the type of the Command (cf. PacketType)
             */
            PacketType getType(void) const override;

        protected:
            /**
             * @brief The data of the Command (ex.: "45" in the command "Move 45")
             *
             */
            std::vector<long> _data;
            /**
             * @brief The type of the Command (cf. PacketType)
             *
             */
            PacketType _type;
    };
}

/*
** EPITECH PROJECT, 2024
** R-type
** File description:
** Level component
*/

#pragma once

#include "../IComponent.hh"
namespace RType {

    /**
     * @brief Level component class
     */
    class LevelComponent: public RType::IComponent {
        public:
            /**
             * @brief Construct a new Level Component object
             *
             * @param level Initial level
             */
            LevelComponent(int level);

            /**
             * @brief Destroy the Level Component object
             */
            ~LevelComponent();

            /**
             * @brief Set the Level
             *
             * @param level New level
             */
            void setLevel(int level);

            /**
             * @brief Get the Level
             *
             * @return int Current level
             */
            int getLevel() const;

            /**
             * @brief Get the Output as a string
             *
             * @return std::string Output string
             */
            std::string getOutput() const;

        private:
            /**
             * @brief Current level
             */
            int _level;
    };
}

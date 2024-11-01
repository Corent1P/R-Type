/*
** EPITECH PROJECT, 2024
** R-type
** File description:
** Difficulty component
*/

#pragma once

#include "../IComponent.hh"

#define GET_DIFFICULTY getComponent<RType::DifficultyComponent>()

namespace RType {
    enum Difficulty {
        FABIEN,
        EASY,
        NORMAL,
        HARD,
        ALIEN
    };

    /**
     * @brief DifficultyComponent class for handling the difficulty of the game
     *
     */
    class DifficultyComponent: public RType::IComponent {
        public:

            /**
             * @brief Construct a new Difficulty Component object
             *
             * @param difficulty The difficulty to set
             */
            DifficultyComponent(Difficulty difficulty);

            /**
             * @brief Destroy the Difficulty Component object
             *
             */
            ~DifficultyComponent();

            /**
             * @brief Set the difficulty
             *
             * @param difficulty The difficulty to set
             */
            void setDifficulty(Difficulty difficulty);

            /**
             * @brief Get the difficulty
             *
             * @return Difficulty The difficulty
             */
            void setDifficulty(std::string difficulty);

            /**
             * @brief Get the difficulty
             *
             * @return Difficulty The difficulty
             */
            RType::Difficulty getDifficulty() const;

            /**
             * @brief Get the damage coefficient
             *
             * @return float The damage coefficient
             */
            float getDamageCoefficient() const;

            /**
             * @brief Get the output of the component
             *
             * @return std::string The output of the component
             */
            std::string getOutput() const;

        private:
            /**
             * @brief The difficulty
             *
             */
            Difficulty _difficulty;
    };
}

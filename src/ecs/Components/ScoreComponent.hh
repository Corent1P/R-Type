/*
** EPITECH PROJECT, 2024
** R-type
** File description:
** Score component
*/

#pragma once

#include "../IComponent.hh"
namespace RType {

    /**
     * @brief Score component class
     */
    class ScoreComponent: public RType::IComponent {
        public:
            /**
             * @brief Construct a new ScoreComponent object
             *
             * @param score Initial score
             */
            ScoreComponent(int score);

            /**
             * @brief Destroy the ScoreComponent object
             */
            ~ScoreComponent();

            /**
             * @brief Set the score
             *
             * @param score New score
             */
            void setScore(int score);

            /**
             * @brief Get the score
             *
             * @return int Current score
             */
            int getScore() const;

            /**
             * @brief Get the output as a string
             *
             * @return std::string Output string
             */
            std::string getOutput() const;
        private:
            /**
             * @brief Current score
             */
            int _score;
    };
}

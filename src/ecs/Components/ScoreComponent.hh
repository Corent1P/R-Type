/*
** EPITECH PROJECT, 2024
** R-type
** File description:
** Score component
*/

#pragma once

#include "../IComponent.hh"
namespace RType {

    class ScoreComponent: public RType::IComponent {
        public:
            ScoreComponent(int score);
            ~ScoreComponent();
            void setScore(int score);
            int getScore() const;
            std::string getOutput() const;
        private:
            int _score;
    };
}

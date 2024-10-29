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
    class DifficultyComponent: public RType::IComponent {
        public:
            DifficultyComponent(Difficulty difficulty);
            ~DifficultyComponent();
            void setDifficulty(Difficulty difficulty);
            void setDifficulty(std::string difficulty);
            RType::Difficulty getDifficulty() const;
            float getDamageCoefficient() const;
            std::string getOutput() const;
        private:
            Difficulty _difficulty;
    };
}

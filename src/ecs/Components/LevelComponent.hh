/*
** EPITECH PROJECT, 2024
** R-type
** File description:
** Level component
*/

#pragma once

#include "../IComponent.hh"
namespace RType {

    class LevelComponent: public RType::IComponent {
        public:
            LevelComponent(int level);
            ~LevelComponent();
            void setLevel(int level);
            int getLevel() const;
            std::string getOutput() const;
        private:
            int _level;
    };
}

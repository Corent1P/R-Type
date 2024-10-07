/*
** EPITECH PROJECT, 2024
** R-type
** File description:
** Level component
*/

#include "LevelComponent.hh"

RType::LevelComponent::LevelComponent(int level):
    _level(level)
{
}

RType::LevelComponent::~LevelComponent()
{
}

void RType::LevelComponent::setLevel(int level)
{
    _level = level;
}

int RType::LevelComponent::getLevel() const
{
    return (_level);
}

std::string RType::LevelComponent::getOutput() const
{
    std::string output("Level Component (level: " + std::to_string(_level)  + ")");
    return (output);
}

/*
** EPITECH PROJECT, 2024
** R-type
** File description:
** Score component
*/

#include "ScoreComponent.hh"

RType::ScoreComponent::ScoreComponent(int score):
    _score(score)
{
}

RType::ScoreComponent::~ScoreComponent()
{
}

void RType::ScoreComponent::setScore(int score)
{
    _score = score;
}

int RType::ScoreComponent::getScore() const
{
    return (_score);
}

std::string RType::ScoreComponent::getOutput() const
{
    std::string output("Score Component (score: " + std::to_string(_score)  + ")");
    return (output);
}

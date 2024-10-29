/*
** EPITECH PROJECT, 2024
** rType
** File description:
** DifficultyComponent
*/

#include "DifficultyComponent.hh"

RType::DifficultyComponent::DifficultyComponent(Difficulty difficulty):
	_difficulty(difficulty)
{
}

RType::DifficultyComponent::~DifficultyComponent()
{
}

void RType::DifficultyComponent::setDifficulty(Difficulty difficulty)
{
	_difficulty = difficulty;
}

void RType::DifficultyComponent::setDifficulty(std::string difficulty)
{
	if (difficulty == "fabien")
		_difficulty = FABIEN;
	if (difficulty == "easy")
		_difficulty = EASY;
	if (difficulty == "normal")
		_difficulty = NORMAL;
	if (difficulty == "hard")
		_difficulty = HARD;
	if (difficulty == "alien")
		_difficulty = ALIEN;
}

RType::Difficulty RType::DifficultyComponent::getDifficulty() const
{
	return _difficulty;
}

float RType::DifficultyComponent::getDamageCoefficient() const
{
    return static_cast<float>(_difficulty) * 0.5f;
}

std::string RType::DifficultyComponent::getOutput() const
{
    std::string output("Difficulty Component (difficulty: " + std::to_string(_difficulty) + ")");
    return (output);
}


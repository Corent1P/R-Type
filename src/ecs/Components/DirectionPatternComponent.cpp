/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Direction Pattern methods
*/

#include "DirectionPatternComponent.hh"

RType::DirectionPatternComponent::DirectionPatternComponent()
{
    _patternType = RType::NO_PATTERN;
    _pattern = sf::Vector2f(0, 0);
}

RType::DirectionPatternComponent::DirectionPatternComponent(RType::PatternType patternType)
{
    _patternType = patternType;
    _pattern = sf::Vector2f(0, 0);
}


RType::DirectionPatternComponent::~DirectionPatternComponent()
{
}


void RType::DirectionPatternComponent::setPatternType(RType::PatternType patternType)
{
    _patternType = patternType;
}

RType::PatternType RType::DirectionPatternComponent::getPatternType() const
{
    return(_patternType);
}

void RType::DirectionPatternComponent::setPattern(sf::Vector2f pattern)
{
    _pattern.x = pattern.x;
    _pattern.y = pattern.y;
}

sf::Vector2f RType::DirectionPatternComponent::getPattern() const
{
    return (_pattern);
}

std::string RType::DirectionPatternComponent::getOutput() const
{
    std::string pattern("");
    switch (_patternType)
        {
        default:
            pattern = "RIGHT(DEFAULT)";
            break;
        }
    std::string output("Entity Direction Component (entity direction: " + pattern + ")");
    return output;
}

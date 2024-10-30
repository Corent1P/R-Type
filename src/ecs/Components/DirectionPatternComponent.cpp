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

void RType::DirectionPatternComponent::setEntityToFollow(uint16_t entityToFollow) {
    _entityToFollow = entityToFollow;
}

uint16_t RType::DirectionPatternComponent::getEntityToFollow() const {
    return (_entityToFollow);
}

void RType::DirectionPatternComponent::setDirectionForZigZag(bool directionForZigZag) {
    _directionForZigZag = directionForZigZag;
}

bool RType::DirectionPatternComponent::getDirectionForZigZag() const {
    return (_directionForZigZag);
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

bool RType::DirectionPatternComponent::isPatternLeft(RType::PatternType patternType)
{
    if (patternType == RType::STRAIGHT_LEFT || patternType == RType::UP_N_DOWN_LEFT || patternType == RType::ZIGZAG_LEFT || patternType == RType::ZIGZAG_REVERSE_LEFT ||
        patternType == RType::SEMI_DIAGONAL_UP || patternType == RType::SEMI_DIAGONAL_DOWN || patternType == RType::DIAGONAL_UP ||
        patternType == RType::DIAGONAL_DOWN)
        return true;
    return false;
}

bool RType::DirectionPatternComponent::isPatternRight(RType::PatternType patternType)
{
    if (patternType == RType::STRAIGHT_RIGHT || patternType == RType::UP_N_DOWN_RIGHT)
        return true;
    return false;
}

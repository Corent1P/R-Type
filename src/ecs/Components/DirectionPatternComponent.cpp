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
        case STRAIGHT_UP:
            pattern = "STRAIGHT_UP";
            break;
        case STRAIGHT_DOWN:
            pattern = "STRAIGHT_DOWN";
            break;
        case STRAIGHT_LEFT:
            pattern = "STRAIGHT_LEFT";
            break;
        case STRAIGHT_RIGHT:
            pattern = "STRAIGHT_RIGHT";
            break;
        case UP_N_DOWN_LEFT:
            pattern = "UP_N_DOWN_LEFT";
            break;
        case UP_N_DOWN_RIGHT:
            pattern = "UP_N_DOWN_RIGHT";
            break;
        case LEFT_N_RIGHT:
            pattern = "LEFT_N_RIGHT";
            break;
        case UP_THEN_DOWN:
            pattern = "UP_THEN_DOWN";
            break;
        case FOLLOW_PLAYER:
            pattern = "FOLLOW_PLAYER";
            break;
        case REVERSE_UP_N_DOWN_RIGHT:
            pattern = "REVERSE_UP_N_DOWN_RIGHT";
            break;
        default:
            pattern = "No Pattern";
            break;
    }
    std::string output("Entity Direction Component (entity direction: " + pattern + ")");
    return output;
}

bool RType::DirectionPatternComponent::isPatternRight(PatternType pattern)
{
    return pattern == LEFT_N_RIGHT || pattern == STRAIGHT_RIGHT || pattern == UP_N_DOWN_RIGHT || pattern == REVERSE_UP_N_DOWN_RIGHT;
}

bool RType::DirectionPatternComponent::isPatternLeft(PatternType pattern)
{
    return (pattern == RType::STRAIGHT_LEFT || pattern == RType::UP_N_DOWN_LEFT || pattern == RType::ZIGZAG_LEFT || pattern == RType::ZIGZAG_REVERSE_LEFT ||
            pattern == RType::SEMI_DIAGONAL_UP || pattern == RType::SEMI_DIAGONAL_DOWN || pattern == RType::DIAGONAL_UP ||
            pattern == RType::DIAGONAL_DOWN);
}

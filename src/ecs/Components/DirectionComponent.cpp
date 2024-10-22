/*
** EPITECH PROJECT, 2024
** R-type
** File description:
** Direction Component methods
*/

#include "DirectionComponent.hh"

RType::DirectionComponent::DirectionComponent()
{
    _direction = RType::NOMOVE;

    _directions.push_back(0);
    _directions.push_back(0);
    _directions.push_back(0);
    _directions.push_back(0);
    _directions.push_back(0);
}

RType::DirectionComponent::DirectionComponent(Direction direction)
{
    _direction = direction;

    _directions.push_back(0);
    _directions.push_back(0);
    _directions.push_back(0);
    _directions.push_back(0);
    _directions.push_back(0);

}


RType::DirectionComponent::~DirectionComponent()
{
}

void RType::DirectionComponent::setDirection(Direction direction)
{
    _direction = direction;
}

RType::Direction RType::DirectionComponent::getDirection() const
{
    return (_direction);
}

void RType::DirectionComponent::setDirections(Direction direction, int newValue) {
    _directions.at(direction) = newValue;
}

int RType::DirectionComponent::getDirections(Direction direction) const
{
    return (_directions.at(direction));
}

std::string RType::DirectionComponent::getOutput() const
{
    std::string direction("");
    switch (_direction)
        {
        case UP:
            direction = "UP";
            break;
        case DOWN:
            direction = "DOWN";
            break;
        case LEFT:
            direction = "LEFT";
            break;
        case RIGHT:
            direction = "RIGHT";
            break;
        case NOMOVE:
            direction = "NOMOVE";
            break;
        default:
            direction = "RIGHT(DEFAULT)";
            break;
        }
    std::string output("Entity Direction Component (entity direction: " + direction + ")");
    return output;
}

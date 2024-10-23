/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Clock component methods
*/

#include "ClockComponent.hh"

RType::ClockComponent::ClockComponent()
{
    sf::Clock animation;
    sf::Clock shooting;
    sf::Clock chargedShot;
    sf::Clock logicClock;
    sf::Clock levelClock;
    sf::Clock shootingEffect;

    _clock.push_back(animation);
    _clock.push_back(shooting);
    _clock.push_back(chargedShot);
    _clock.push_back(logicClock);
    _clock.push_back(levelClock);
    _clock.push_back(shootingEffect);
}

sf::Clock  &RType::ClockComponent::getClock(ClockType type)
{
    return(_clock.at(type));
}

std::string RType::ClockComponent::getOutput() const
{
    std::string output("Clock Component");
    return (output);
}

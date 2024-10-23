/*
** EPITECH PROJECT, 2024
** R-type
** File description:
** PowerUp Component methods
*/

#include "PowerUpComponent.hh"

RType::PowerUpComponent::PowerUpComponent()
{
    _powerUpType = RType::NO_POWER_UP;

    _powerUps.push_back(true);
    _powerUps.push_back(false);
    _powerUps.push_back(false);

    _powerUpsIsActive.push_back(true);
    _powerUpsIsActive.push_back(false);
    _powerUpsIsActive.push_back(false);
}

RType::PowerUpComponent::PowerUpComponent(PowerUpType powerUpType)
{
    _powerUpType = powerUpType;
    _powerUps.push_back(true);
    _powerUps.push_back(false);
    _powerUps.push_back(false);

    _powerUpsIsActive.push_back(true);
    _powerUpsIsActive.push_back(false);
    _powerUpsIsActive.push_back(false);
}


RType::PowerUpComponent::~PowerUpComponent()
{
}

void RType::PowerUpComponent::setPowerUpType(PowerUpType powerUpType)
{
    _powerUpType = powerUpType;
}

RType::PowerUpType RType::PowerUpComponent::getPowerUpType() const
{
    return (_powerUpType);
}

void RType::PowerUpComponent::setPowerUps(PowerUpType powerUpType, bool newBool) {
    _powerUps.at(powerUpType) = newBool;
}

bool RType::PowerUpComponent::getPowerUps(PowerUpType powerUpType) const
{
    return (_powerUps.at(powerUpType));
}

void RType::PowerUpComponent::setPowerUpsIsActive(PowerUpType powerUpType, bool newBool) {
    _powerUpsIsActive.at(powerUpType) = newBool;
}

bool RType::PowerUpComponent::getPowerUpsIsActive(PowerUpType powerUpType) const
{
    return (_powerUpsIsActive.at(powerUpType));
}

std::string RType::PowerUpComponent::getOutput() const
{
    std::string powerUp("");
    switch (_powerUpType)
        {
        case NO_POWER_UP:
            powerUp = "NO POWER UP";
            break;
        case SHIELD:
            powerUp = "SHIELD";
            break;
        case FORCE_POD:
            powerUp = "FORCE POD";
            break;
        default:
            powerUp = "NO POWER UP";
            break;
        }
    std::string output("Entity PowerUP Component (entity Action " + powerUp + ")");
    return output;
}

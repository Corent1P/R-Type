/*
** EPITECH PROJECT, 2024
** rType
** File description:
** EntityTypeComponent
*/

#include "EntityTypeComponent.hh"

RType::EntityTypeComponent::EntityTypeComponent(EntityType entityType):
    _entityType(entityType)
{
}

RType::EntityTypeComponent::~EntityTypeComponent()
{
}

void RType::EntityTypeComponent::setEntityType(EntityType entityType)
{
	_entityType = entityType;
}

RType::EntityType RType::EntityTypeComponent::getEntityType() const
{
	return _entityType;
}

void RType::EntityTypeComponent::setWeaponType(WeaponType weaponType)
{
    _weaponType = weaponType;
}

RType::WeaponType RType::EntityTypeComponent::getWeaponType() const
{
    return(_weaponType);
}

void RType::EntityTypeComponent::setPowerUpType(PowerUpType powerUpType)
{
    _powerUpType = powerUpType;
}

RType::PowerUpType RType::EntityTypeComponent::getPowerUpType() const
{
    return(_powerUpType);
}

void RType::EntityTypeComponent::setEnemyType(EnemyType enemyType)
{
	_enemyType = enemyType;
}

RType::EnemyType RType::EntityTypeComponent::getEnemyType() const
{
	return _enemyType;
}

std::string RType::EntityTypeComponent::getOutput() const
{
    std::string entityType("");
    switch (_entityType)
        {
        case WINDOW:
            entityType = "window";
            break;
        case PLAYER:
            entityType = "player";
            break;
        case MOB:
            entityType = "mob";
            break;
        case BOSS:
            entityType = "boss";
            break;
        case BUTTON:
            entityType = "button";
            break;
        case LAYER:
            entityType = "layer";
            break;
        case WEAPON:
            entityType = "weapon";
            break;
        case POWER_UP:
            entityType = "power up";
            break;
        default:
            entityType = "unknown";
            break;
        }
    std::string output("Entity Type Component (entity type: " + entityType + ")");
    return (output);}

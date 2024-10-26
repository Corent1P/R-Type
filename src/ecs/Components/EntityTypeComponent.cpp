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
    _buttonType = INPUT_UNDEFINED;
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

void RType::EntityTypeComponent::setEnemyType(EnemyType enemyType)
{
	_enemyType = enemyType;
}

RType::EnemyType RType::EntityTypeComponent::getEnemyType() const
{
	return _enemyType;
}

void RType::EntityTypeComponent::setButtonType(MappingInput buttonType)
{
	_buttonType = buttonType;
}

RType::MappingInput RType::EntityTypeComponent::getButtonType() const
{
	return _buttonType;
}

bool RType::EntityTypeComponent::isMob(EntityType entityType)
{
    return entityType == E_SMALL_SPACESHIP || entityType == E_FLY || entityType == E_BABY_FLY || entityType == E_OCTOPUS || isBoss(entityType);
}

bool RType::EntityTypeComponent::isBoss(EntityType entityType)
{
    return entityType == E_BOSS;
}

bool RType::EntityTypeComponent::isEnnemyShoot(EntityType entityType)
{
    return entityType == E_ENNEMY_BULLET || entityType == E_STING;
}

bool RType::EntityTypeComponent::isItem(EntityType entityType)
{
    return entityType == E_ITEM_WEAPON || entityType == E_ITEM_HEAL || entityType == E_ITEM_SHIELD;
}

bool RType::EntityTypeComponent::isWeapon(EntityType entityType)
{
    return entityType == E_BULLET || entityType == E_BULLET_2 || entityType == E_BULLET_3 || entityType == E_BULLET_4;
}

bool RType::EntityTypeComponent::isPowerUp(EntityType entityType)
{
    return entityType == E_SHIELD;
}


std::string RType::EntityTypeComponent::getOutput() const
{
    std::string entityType("");
    switch (_entityType)
        {
        case E_WINDOW:
            entityType = "window";
            break;
        case E_PLAYER:
            entityType = "player";
            break;
        case E_SMALL_SPACESHIP:
            entityType = "mob small spaceship";
            break;
        case E_OCTOPUS:
            entityType = "mob octopus";
            break;
        case E_FLY:
            entityType = "mob fly";
            break;
        case E_BABY_FLY:
            entityType = "mob baby fly";
            break;
        case E_STING:
            entityType = "mob sting";
            break;
        case E_BOSS:
            entityType = "boss";
            break;
        case E_BUTTON:
            entityType = "button";
            break;
        case E_LAYER:
            entityType = "layer";
            break;
        case E_BULLET:
            entityType = "bullet";
            break;
        case E_ITEM_WEAPON:
            entityType = "item weapon";
            break;
        case E_ITEM_SHIELD:
            entityType = "item shield";
            break;
        case E_ITEM_HEAL:
            entityType = "item heal";
            break;
        case E_SHIELD:
            entityType = "item shield";
            break;
        default:
            entityType = "unknown";
            break;
        }
    std::string output("Entity Type Component (entity type: " + entityType + ")");
    return (output);
}

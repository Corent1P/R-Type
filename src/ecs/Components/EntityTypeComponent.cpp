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
        case E_MOB:
            entityType = "mob";
            break;
        case E_BOSS:
            entityType = "boss";
            break;
        case E_BUTTON:
            entityType = "button";
            break;
        default:
            entityType = "unknown";
            break;
        }
    std::string output("Entity Type Component (entity type: " + entityType + ")");
    return (output);}

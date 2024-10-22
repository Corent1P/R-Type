/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** handle draw system methods
*/

#include "HandleDrawTextSystem.hpp"

RType::HandleDrawTextSystem::HandleDrawTextSystem(std::function<std::shared_ptr<Entity>()> addEntity, std::function<void(std::shared_ptr<Entity>)> deleteEntity):
    ASystem(S_DRAWTEXT, addEntity, deleteEntity), _dotString("."), _dotCounter(0)
{
}

RType::HandleDrawTextSystem::~HandleDrawTextSystem()
{
}


void RType::HandleDrawTextSystem::effects(std::vector<std::shared_ptr<RType::Entity>> entities)
{
    for (const auto &w: entities) {
        if (GET_WINDOW_FOR_DRAW != nullptr) {
            for (const auto &entity: entities) {
                if (verifyRequiredComponent(entity) && *entity->GET_MENU == *w->GET_MENU) {
                    updateText(entity, w);
                    SET_TEXT_POSITION;
                    GET_WINDOW_FOR_DRAW->getWindow()->draw(*(entity->getComponent<RType::TextComponent>()->getText()));
                }
            }
            return;
        }
    }
}

bool RType::HandleDrawTextSystem::verifyRequiredComponent(std::shared_ptr<RType::Entity> entity)
{
    if (entity->getComponent<RType::PositionComponent>() == nullptr
    || entity->getComponent<RType::TextComponent>() == nullptr) {
        return false;
    }
    return (true);
}

void RType::HandleDrawTextSystem::updateText(std::shared_ptr<RType::Entity> button, std::shared_ptr<RType::Entity> window)
{
    if (button->getComponent<EntityTypeComponent>()->getButtonType() != INPUT_UNDEFINED) {
        auto keyCode = window->getComponent<RType::MappingInputComponent>()->getMappingInput(button->getComponent<EntityTypeComponent>()->getButtonType());
        auto textComponent = button->getComponent<TextComponent>();
        if (textComponent != nullptr) {
            std::string keyName = RType::MappingInputComponent::getKeyName(keyCode);
            if (window->getComponent<RType::MappingInputComponent>()->getInputToDefined() == button->getComponent<EntityTypeComponent>()->getButtonType())
                textComponent->setText(textComponent->getTextWithoutVariable() + getDotString());
            else
                textComponent->setText(textComponent->getTextWithoutVariable() + keyName);
        }
    }
}

const std::string& RType::HandleDrawTextSystem::getDotString(void)
{
    _dotCounter++;
    if (_dotCounter > 10) {
        _dotString += ".";
        if (_dotString.length() > 3) {
            _dotString = ".";
        }
        _dotCounter = 0;
    }
	return _dotString;
}

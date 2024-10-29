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
        if (GET_WINDOW_FOR_DRAW == nullptr)
            continue;
        for (const auto &entity: entities) {
            if (verifyRequiredComponent(entity) && *entity->GET_MENU == *w->GET_MENU) {
                updateText(entity, w);
                SET_TEXT_POSITION;
                if (GET_HOVER_C != nullptr && GET_HOVER_C->getHoverState()) {
                    drawHitBox(w, entity);
                }
                GET_WINDOW_FOR_DRAW->getWindow()->draw(*(entity->getComponent<RType::TextComponent>()->getText()));
            }
        }
        return;
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
    } else if (button->getComponent<EntityTypeComponent>() != nullptr && button->getComponent<EntityTypeComponent>()->getEntityType() == E_HEALTHTEXT) {
        auto textComponent = button->getComponent<TextComponent>();
        auto healthComponent = button->getComponent<HealthComponent>();
        if (textComponent && healthComponent && healthComponent->getIsDead() == false) {
            int healthPercentage = healthComponent->getMaxHealth() != 0 ? healthComponent->getHealth() * 100 / healthComponent->getMaxHealth() : 0;
            std::string healthStringPercentage = std::to_string(healthPercentage) + "%";
            textComponent->setText(textComponent->getTextWithoutVariable() + healthStringPercentage);
        } else
            textComponent->setText("You're in specator mode");
    } else if (button->getComponent<EntityTypeComponent>() != nullptr && button->getComponent<EntityTypeComponent>()->getEntityType() == E_SCORETEXT) {
        auto textScoreComponent = button->getComponent<TextComponent>();
        auto scoreComponent = button->getComponent<ScoreComponent>();
        if (textScoreComponent && scoreComponent) {
            textScoreComponent->setText(textScoreComponent->getTextWithoutVariable() + std::to_string(scoreComponent->getScore()));
        } else
            textScoreComponent->setText("You're in specator mode");
    }
}

void RType::HandleDrawTextSystem::drawHitBox(const std::shared_ptr<RType::Entity> &w, const std::shared_ptr<RType::Entity> &entity)
{
    if (entity->getComponent<EntityTypeComponent>()->getEntityType() != E_LAYER) {
        sf::FloatRect bounds = entity->getComponent<RType::TextComponent>()->getText()->getGlobalBounds();
        sf::RectangleShape rect(sf::Vector2f(bounds.width, bounds.height));
        rect.setPosition(entity->getComponent<RType::TextComponent>()->getText()->getPosition());
        rect.setOutlineColor(sf::Color::White);
        rect.setOutlineThickness(2);
        GET_WINDOW_FOR_DRAW->getWindow()->draw(rect);
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

/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** handle event system methods
*/

#include "HandleEventSystem.hpp"

RType::HandleEventSystem::HandleEventSystem(std::function<std::shared_ptr<Entity>()> addEntity, std::function<void(std::shared_ptr<Entity>)> deleteEntity, std::function<void(void)> disconnexion):
    ASystem(S_EVENT, addEntity, deleteEntity), _isShooting(false), _disconnexion(disconnexion)
{
}

RType::HandleEventSystem::~HandleEventSystem()
{
}

void RType::HandleEventSystem::effects(std::vector<std::shared_ptr<RType::Entity>> entities) {
    for (const auto &e: entities) {
        if (verifyRequiredComponent(e)) {
            auto inputs = e->getComponent<RType::MappingInputComponent>()->getMappingInputs();
            while (GET_WINDOW_POLL_EVENT->pollEvent(e->getComponent<RType::EventComponent>()->getEvent())) {
                if (e->getComponent<RType::EventComponent>()->getEvent().type == sf::Event::Closed) {
                    GET_WINDOW_POLL_EVENT->close();
                }
                modifyInput(entities, e);
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                    if (_disconnexion)
                        _disconnexion();
                    e->getComponent<RType::MenuComponent>()->setMenu(HOME);
                }
                for (const auto &entity: entities) {
                    handleInputPlayer(entity, e, inputs);
                    handleHoverOnButton(entity, e);
                    handleClickOnButton(entity, e);
                }
            }
        }
    }
}

void RType::HandleEventSystem::effect(std::shared_ptr<RType::Entity> entity)
{
    while (GET_WINDOW->pollEvent(entity->getComponent<RType::EventComponent>()->getEvent())) {
        if (entity->getComponent<RType::EventComponent>()->getEvent().type == sf::Event::Closed) {
            GET_WINDOW->close();
        }
    }
}

bool RType::HandleEventSystem::verifyRequiredComponent(std::shared_ptr<RType::Entity> entity)
{
    if (entity->getComponent<RType::SFWindowComponent>() == nullptr
    || entity->getComponent<RType::EventComponent>() == nullptr
    || entity->getComponent<RType::MappingInputComponent>() == nullptr
    || entity->getComponent<RType::MenuComponent>() == nullptr) {
        return false;
    }
    return (true);
}

void RType::HandleEventSystem::modifyInput(std::vector<std::shared_ptr<RType::Entity>> entities, std::shared_ptr<RType::Entity> window)
{
    if (window->getComponent<RType::MappingInputComponent>()->getInputToDefined() != INPUT_UNDEFINED
        && window->getComponent<RType::EventComponent>()->getEvent().type == sf::Event::KeyPressed) {
        auto keyCode = window->getComponent<RType::EventComponent>()->getEvent().key.code;

        for (const auto &button: entities) {
            if (button->getComponent<EntityTypeComponent>()
            && button->getComponent<EntityTypeComponent>()->getButtonType() == window->getComponent<RType::MappingInputComponent>()->getInputToDefined()) {

                auto textComponent = button->getComponent<TextComponent>();
                if (textComponent != nullptr) {
                    std::string keyName = RType::MappingInputComponent::getKeyName(keyCode);
                    textComponent->setText(textComponent->getTextWithoutVariable() + keyName);
                }
            }
        }
        window->getComponent<RType::MappingInputComponent>()->setMappingInput(keyCode);
    }
}

void RType::HandleEventSystem::handleInputPlayer(std::shared_ptr<RType::Entity> player, std::shared_ptr<RType::Entity> window, std::unordered_map<RType::MappingInput, sf::Keyboard::Key> inputs)
{
    if (player->getComponent<RType::EntityTypeComponent>() != nullptr
    && player->getComponent<RType::EntityTypeComponent>()->getEntityType() == E_PLAYER
    && player->getComponent<RType::DirectionComponent>() != nullptr
    && player->getComponent<RType::SpriteComponent>() != nullptr
    && player->getComponent<RType::ActionComponent>() != nullptr
    ) {
        if (sf::Keyboard::isKeyPressed(inputs.at(INPUT_LEFT)) && player->getComponent<RType::DirectionComponent>()->getDirections(LEFT) == 0) {
            player->getComponent<RType::DirectionComponent>()->setDirections(LEFT, 100);
        } else if (!sf::Keyboard::isKeyPressed(inputs.at(INPUT_LEFT)) && player->getComponent<RType::DirectionComponent>()->getDirections(LEFT) != 0) {
            player->getComponent<RType::DirectionComponent>()->setDirections(LEFT, 0);
        }
        if (sf::Keyboard::isKeyPressed(inputs.at(INPUT_RIGHT)) && player->getComponent<RType::DirectionComponent>()->getDirections(RIGHT) == 0) {
            player->getComponent<RType::DirectionComponent>()->setDirections(RIGHT, 100);
        } else if (!sf::Keyboard::isKeyPressed(inputs.at(INPUT_RIGHT)) && player->getComponent<RType::DirectionComponent>()->getDirections(RIGHT) != 0) {
            player->getComponent<RType::DirectionComponent>()->setDirections(RIGHT, 0);
        }
        if (sf::Keyboard::isKeyPressed(inputs.at(INPUT_UP)) && player->getComponent<RType::DirectionComponent>()->getDirections(UP) == 0) {
            player->getComponent<RType::DirectionComponent>()->setDirections(UP, 100);
        } else if (!sf::Keyboard::isKeyPressed(inputs.at(INPUT_UP)) && player->getComponent<RType::DirectionComponent>()->getDirections(UP) != 0) {
            player->getComponent<RType::DirectionComponent>()->setDirections(UP, 0);
        }
        if (sf::Keyboard::isKeyPressed(inputs.at(INPUT_DOWN)) && player->getComponent<RType::DirectionComponent>()->getDirections(DOWN) == 0) {
            player->getComponent<RType::DirectionComponent>()->setDirections(DOWN, 100);
        } else if (!sf::Keyboard::isKeyPressed(inputs.at(INPUT_DOWN)) && player->getComponent<RType::DirectionComponent>()->getDirections(DOWN) != 0) {
            player->getComponent<RType::DirectionComponent>()->setDirections(DOWN, 0);
        }
        if (sf::Keyboard::isKeyPressed(inputs.at(INPUT_SHOOT)) && !_isShooting) {
            player->getComponent<RType::ClockComponent>()->getClock(RType::CHARGED_SHOT_CLOCK).restart();
            _isShooting = true;
        } else if (sf::Keyboard::isKeyPressed(inputs.at(INPUT_SHOOT)) && _isShooting) {
            player->getComponent<RType::ClockComponent>()->setChargingTime(
                player->getComponent<RType::ClockComponent>()->getClock(RType::CHARGED_SHOT_CLOCK).getElapsedTime().asSeconds()
            );
            player->getComponent<RType::ActionComponent>()->setActions(RType::CHARGING_SHOT, true);
        } else if (!sf::Keyboard::isKeyPressed(inputs.at(INPUT_SHOOT)) && _isShooting) {
            player->getComponent<RType::ClockComponent>()->setChargedTime(player->getComponent<RType::ClockComponent>()->getChargingTime());
            _isShooting = false;
            player->getComponent<RType::ActionComponent>()->setActions(RType::SHOOTING, true);
        }
        if (sf::Joystick::isConnected(0))
        {
            float x = sf::Joystick::getAxisPosition(0, sf::Joystick::X);
            float y = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);
            if (window->getComponent<RType::EventComponent>()->getEvent().type == sf::Event::JoystickButtonPressed) {
                if (window->getComponent<RType::EventComponent>()->getEvent().joystickButton.button == 1) {
                    player->getComponent<RType::ActionComponent>()->setActions(RType::SHOOTING, true);
                }
            }
            if (y > 10.0) {
                player->getComponent<RType::DirectionComponent>()->setDirections(DOWN, y);
            } else {
                player->getComponent<RType::DirectionComponent>()->setDirections(DOWN, 0);
            }
            if (y < -10.0) {
                player->getComponent<RType::DirectionComponent>()->setDirections(UP, abs(y));
            } else {
                player->getComponent<RType::DirectionComponent>()->setDirections(UP, 0);
            }
            if (x < -10.0) {
                player->getComponent<RType::DirectionComponent>()->setDirections(LEFT, abs(x));
            } else {
                player->getComponent<RType::DirectionComponent>()->setDirections(LEFT, 0);
            }
            if (x > 10.0) {
                player->getComponent<RType::DirectionComponent>()->setDirections(RIGHT, x);
            } else {
                player->getComponent<RType::DirectionComponent>()->setDirections(RIGHT, 0);
            }

        }
    }
}

void RType::HandleEventSystem::handleHoverOnButton(std::shared_ptr<RType::Entity> button, std::shared_ptr<RType::Entity> window)
{
    if (!(button->getComponent<RType::HoverEffectComponent>() != nullptr
    && button->getComponent<RType::IntRectComponent>() != nullptr
    && button->getComponent<RType::PositionComponent>() != nullptr
    && button->getComponent<RType::MenuComponent>() != nullptr
    && *button->GET_MENU == *window->GET_MENU))
        return;
    if (!(window->getComponent<RType::EventComponent>()->getEvent().type == sf::Event::MouseMoved))
        return;

    sf::Event::MouseMoveEvent mouseEvent = window->GET_EVENT.mouseMove;

    int boxX = button->getComponent<RType::PositionComponent>()->getPositionX();
    int boxY = button->getComponent<RType::PositionComponent>()->getPositionY();
    int boxWidth = button->getComponent<RType::IntRectComponent>()->getIntRectWidth();
    int boxHeight = button->getComponent<RType::IntRectComponent>()->getIntRectHeight();

    int mouseX = mouseEvent.x;
    int mouseY = mouseEvent.y;

    auto coord = window->getComponent<RType::SFWindowComponent>()->getWindow()->mapPixelToCoords({mouseX, mouseY});
    sf::IntRect hitbox ({boxX, boxY}, {boxWidth, boxHeight});

    HOVER_ON_BUTTON(false);
    if (hitbox.contains(sf::Vector2i(coord)))
        HOVER_ON_BUTTON(true);
}

void RType::HandleEventSystem::handleClickOnButton(std::shared_ptr<RType::Entity> button, std::shared_ptr<RType::Entity> window)
{
    if (!(button->getComponent<RType::HoverEffectComponent>() != nullptr
    && button->getComponent<RType::IntRectComponent>() != nullptr
    && button->getComponent<RType::PositionComponent>() != nullptr
    && button->getComponent<RType::MenuComponent>() != nullptr
    && *button->GET_MENU == *window->GET_MENU))
        return;
    if (!(window->getComponent<RType::EventComponent>()->getEvent().type == sf::Event::MouseButtonPressed))
        return;
    sf::Event::MouseButtonEvent mouseEvent = window->getComponent<RType::EventComponent>()->getEvent().mouseButton;

    if (mouseEvent.button == sf::Mouse::Left) {
        int boxX = button->getComponent<RType::PositionComponent>()->getPositionX();
        int boxY = button->getComponent<RType::PositionComponent>()->getPositionY();
        int boxWidth = button->getComponent<RType::IntRectComponent>()->getIntRectWidth();
        int boxHeight = button->getComponent<RType::IntRectComponent>()->getIntRectHeight();

        int mouseX = mouseEvent.x;
        int mouseY = mouseEvent.y;

        auto coord = window->getComponent<RType::SFWindowComponent>()->getWindow()->mapPixelToCoords({mouseX, mouseY});
        sf::IntRect hitbox ({boxX, boxY}, {boxWidth, boxHeight});

        if (hitbox.contains(sf::Vector2i(coord)))
            CLICK_ON_BUTTON;
    }
}

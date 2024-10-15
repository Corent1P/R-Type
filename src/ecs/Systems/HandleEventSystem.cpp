/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** handle event system methods
*/

#include "HandleEventSystem.hpp"

RType::HandleEventSystem::HandleEventSystem(std::function<std::shared_ptr<Entity>()> addEntity, std::function<void(std::shared_ptr<Entity>)> deleteEntity):
    ASystem(S_EVENT, addEntity, deleteEntity), _isShooting(false)
{
}

RType::HandleEventSystem::~HandleEventSystem()
{
}

void RType::HandleEventSystem::effects(std::vector<std::shared_ptr<RType::Entity>> entities) {
    // bool canShoot = true;
    for (const auto &e: entities) {
        if (verifyRequiredComponent(e)) {
            while (GET_WINDOW_POLL_EVENT->pollEvent(e->getComponent<RType::EventComponent>()->getEvent())) {
                if (e->getComponent<RType::EventComponent>()->getEvent().type == sf::Event::Closed) {
                    GET_WINDOW_POLL_EVENT->close();
                }
                for (const auto &player: entities) {
                    if (player->getComponent<RType::EntityTypeComponent>() != nullptr
                    && player->getComponent<RType::EntityTypeComponent>()->getEntityType() == E_PLAYER
                    && player->getComponent<RType::DirectionComponent>() != nullptr
                    && player->getComponent<RType::SpriteComponent>() != nullptr
                    && player->getComponent<RType::ActionComponent>() != nullptr
                    && player->getComponent<RType::MappingInputComponent>() != nullptr
                    ) {
                        auto inputs = player->getComponent<RType::MappingInputComponent>()->getMappingInputs();
                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                            GET_WINDOW_POLL_EVENT->close();
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
                            _isShooting = true;
                            player->getComponent<RType::ActionComponent>()->setActions(RType::SHOOTING, true);
                        } else if (!sf::Keyboard::isKeyPressed(inputs.at(INPUT_SHOOT)) && _isShooting) {
                            _isShooting = false;
                        }

                        if (sf::Joystick::isConnected(0))
                        {
                           float x = sf::Joystick::getAxisPosition(0, sf::Joystick::X);
                           float y = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);
                           if (e->getComponent<RType::EventComponent>()->getEvent().type == sf::Event::JoystickButtonPressed) {
                                std::cout << "Bouton " << e->getComponent<RType::EventComponent>()->getEvent().joystickButton.button
                                        << " pressé sur la manette "
                                        << e->getComponent<RType::EventComponent>()->getEvent().joystickButton.joystickId << std::endl;
                                if (e->getComponent<RType::EventComponent>()->getEvent().joystickButton.button == 1) {
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
                    if (player->getComponent<RType::ClickEffectComponent>() != nullptr
                    && player->getComponent<RType::IntRectComponent>() != nullptr
                    && player->getComponent<RType::PositionComponent>() != nullptr) {
                        if (e->getComponent<RType::EventComponent>()->getEvent().type == sf::Event::MouseButtonPressed) {
                            sf::Event::MouseButtonEvent mouseEvent = e->getComponent<RType::EventComponent>()->getEvent().mouseButton;

                            if (mouseEvent.button == sf::Mouse::Left) {
                                int boxX = player->getComponent<RType::PositionComponent>()->getPositionX();
                                int boxY = player->getComponent<RType::PositionComponent>()->getPositionY();
                                int boxWidth = player->getComponent<RType::IntRectComponent>()->getIntRectWidth();
                                int boxHeight = player->getComponent<RType::IntRectComponent>()->getIntRectHeight();

                                int mouseX = mouseEvent.x;
                                int mouseY = mouseEvent.y;

                                if (mouseX >= boxX && mouseX <= (boxX + boxWidth) &&
                                    mouseY >= boxY && mouseY <= (boxY + boxHeight)) {
                                    CLICK_ON_BUTTON;
                                }
                            }
                        }
                        // player->getComponent<RType::TextComponent>()->ge

                    }
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
    ||entity->getComponent<RType::EventComponent>() == nullptr) {
        return false;
    }
    return (true);
}
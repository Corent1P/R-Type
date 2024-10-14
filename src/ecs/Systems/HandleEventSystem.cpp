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
                    ) {
                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                            GET_WINDOW_POLL_EVENT->close();
                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && player->getComponent<RType::DirectionComponent>()->getDirections(LEFT) == 0) {
                            player->getComponent<RType::DirectionComponent>()->setDirections(LEFT, 100);
                        } else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && player->getComponent<RType::DirectionComponent>()->getDirections(LEFT) != 0) {
                            player->getComponent<RType::DirectionComponent>()->setDirections(LEFT, 0);
                        }
                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && player->getComponent<RType::DirectionComponent>()->getDirections(RIGHT) == 0) {
                            player->getComponent<RType::DirectionComponent>()->setDirections(RIGHT, 100);
                        } else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && player->getComponent<RType::DirectionComponent>()->getDirections(RIGHT) != 0) {
                            player->getComponent<RType::DirectionComponent>()->setDirections(RIGHT, 0);
                        }
                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && player->getComponent<RType::DirectionComponent>()->getDirections(UP) == 0) {
                            player->getComponent<RType::DirectionComponent>()->setDirections(UP, 100);
                        } else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && player->getComponent<RType::DirectionComponent>()->getDirections(UP) != 0) {
                            player->getComponent<RType::DirectionComponent>()->setDirections(UP, 0);
                        }
                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && player->getComponent<RType::DirectionComponent>()->getDirections(DOWN) == 0) {
                            player->getComponent<RType::DirectionComponent>()->setDirections(DOWN, 100);
                        } else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && player->getComponent<RType::DirectionComponent>()->getDirections(DOWN) != 0) {
                            player->getComponent<RType::DirectionComponent>()->setDirections(DOWN, 0);
                        }
                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !_isShooting) {
                            _isShooting = true;
                            player->getComponent<RType::ActionComponent>()->setActions(RType::SHOOTING, true);
                        } else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && _isShooting) {
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
                        std::cout << "player -> " << player->getComponent<RType::DirectionComponent>()->getDirections(RIGHT)  << " " << player->getComponent<RType::DirectionComponent>()->getDirections(LEFT)  << " " << player->getComponent<RType::DirectionComponent>()->getDirections(DOWN)  << " " << player->getComponent<RType::DirectionComponent>()->getDirections(UP) << std::endl;
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
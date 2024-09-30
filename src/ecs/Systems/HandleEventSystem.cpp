/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** handle event system methods
*/

#include "HandleEventSystem.hpp"

RType::HandleEventSystem::HandleEventSystem():
    ASystem(EVENT)
{
}

RType::HandleEventSystem::~HandleEventSystem()
{
}
void RType::HandleEventSystem::effects(std::vector<std::shared_ptr<RType::Entity>> entities) {
    for (const auto &e: entities) {
        if (verifyRequiredComponent(e)) {
            while (GET_WINDOW_POLL_EVENT->pollEvent(e->getComponent<RType::EventComponent>()->getEvent())) {
                if (e->getComponent<RType::EventComponent>()->getEvent().type == sf::Event::Closed) {
                    GET_WINDOW_POLL_EVENT->close();
                }
                for (const auto &player: entities) {
                    if (player->getComponent<RType::EntityTypeComponent>() != nullptr 
                    && player->getComponent<RType::EntityTypeComponent>()->getEntityType() == PLAYER
                    && player->getComponent<RType::DirectionComponent>() != nullptr
                    && player->getComponent<RType::SpriteComponent>() != nullptr
                    ) {
                        if (sf::Event::KeyPressed) {
                            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                                player->getComponent<RType::DirectionComponent>()->setDirection(LEFT);
                                player->getComponent<RType::DirectionComponent>()->setDirections(LEFT, true);
                                std::cout << "moved left" << std::endl;
                            } else {
                                player->getComponent<RType::DirectionComponent>()->setDirections(LEFT, false);
                            }
                            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                                player->getComponent<RType::DirectionComponent>()->setDirection(RIGHT);
                                player->getComponent<RType::DirectionComponent>()->setDirections(RIGHT, true);
                                std::cout << "moved right" << std::endl;
                            } else {
                                player->getComponent<RType::DirectionComponent>()->setDirections(RIGHT, false);
                            }
                            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                                player->getComponent<RType::DirectionComponent>()->setDirection(UP);
                                player->getComponent<RType::DirectionComponent>()->setDirections(UP, true);
                                std::cout << "moved up" << std::endl;
                            } else {
                                player->getComponent<RType::DirectionComponent>()->setDirections(UP, false);
                            }
                            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                                player->getComponent<RType::DirectionComponent>()->setDirection(DOWN);
                                player->getComponent<RType::DirectionComponent>()->setDirections(DOWN, true);
                                std::cout << "moved down" << std::endl;
                            } else {
                                player->getComponent<RType::DirectionComponent>()->setDirections(DOWN, false);
                            }
                        } else {
                            player->getComponent<RType::DirectionComponent>()->setDirections(NOMOVE, true);
                            std::cout << "no move" << std::endl;
                        }

                        if (sf::Joystick::isConnected(0))
                        {
                           float x = sf::Joystick::getAxisPosition(0, sf::Joystick::X);
                           float y = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);
                           if (e->getComponent<RType::EventComponent>()->getEvent().type == sf::Event::JoystickButtonPressed) {
                                std::cout << "Bouton " << e->getComponent<RType::EventComponent>()->getEvent().joystickButton.button 
                                        << " pressé sur la manette " 
                                        << e->getComponent<RType::EventComponent>()->getEvent().joystickButton.joystickId << std::endl;
                            }
                           if (y > 10.0) {
                                player->getComponent<RType::DirectionComponent>()->setDirection(DOWN);
                                player->getComponent<RType::DirectionComponent>()->setDirections(DOWN, true);
                           } else {
                                player->getComponent<RType::DirectionComponent>()->setDirections(DOWN, false);
                           }
                           if (y < -10.0) {
                                player->getComponent<RType::DirectionComponent>()->setDirection(UP);
                                player->getComponent<RType::DirectionComponent>()->setDirections(UP, true);
                           } else {
                                player->getComponent<RType::DirectionComponent>()->setDirections(UP, false);
                           }
                           if (x < -10.0) {
                                player->getComponent<RType::DirectionComponent>()->setDirection(LEFT);
                                player->getComponent<RType::DirectionComponent>()->setDirections(LEFT, true);
                           } else {
                                player->getComponent<RType::DirectionComponent>()->setDirections(LEFT, false);
                           }
                           if (x > 10.0) {
                                player->getComponent<RType::DirectionComponent>()->setDirection(RIGHT);
                                player->getComponent<RType::DirectionComponent>()->setDirections(RIGHT, true);
                           } else {
                                player->getComponent<RType::DirectionComponent>()->setDirections(RIGHT, false);
                           }
                           
                        }
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
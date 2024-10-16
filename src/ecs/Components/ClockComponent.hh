/*
** EPITECH PROJECT, 2024
** R-type
** File description:
** Clock component
*/

#ifndef CLOCKCOMPONENT_HH_
#define CLOCKCOMPONENT_HH_

#include <SFML/Graphics.hpp>
#include "../IComponent.hh"

namespace RType {
    enum ClockType {
        ANIMATION_CLOCK,
        SHOOTING_CLOCK,
        CHARGED_SHOT_CLOCK,
        LOGIC_CLOCK,
        SPAWN_CLOCK,
        SHOOTING_EFFECT,
    };
    /**
     * @brief Component Clock
     *
     */
    class ClockComponent: public RType::IComponent {
        public:
            /**
             * @brief Construct a new Clock Component object
             *
             */
            ClockComponent();
            /**
             * @brief Destroy the Clock Component object
             *
             */
            ~ClockComponent() = default;
            /**
             * @brief Get the Clock object
             *
             * @param type
             * @return sf::Clock&
             */
            sf::Clock &getClock(ClockType type);
            /**
             * @brief Get the Output object
             *
             * @return std::string
             */
            std::string getOutput() const;
        private:
            std::vector<sf::Clock> _clock;
    };
}

#endif /* !CLOCKCOMPONENT_HH_ */

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

    class ClockComponent: public RType::IComponent {
        public:
            ClockComponent();
            ~ClockComponent() = default;
            sf::Clock &getClock(ClockType type);
            std::string getOutput() const;
        private:
            std::vector<sf::Clock> _clock;
    };
}

#endif /* !CLOCKCOMPONENT_HH_ */

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
        LEVEL_CLOCK,
        SHOOTING_EFFECT,
    };

    class ClockComponent: public RType::IComponent {
        public:
            ClockComponent();
            ~ClockComponent() = default;
            void setChargingTime(float time);
            float getChargingTime(void);
            void setChargedTime(float time);
            float getChargedTime(void);
            sf::Clock &getClock(ClockType type);
            std::string getOutput() const;
        private:
            std::vector<sf::Clock> _clock;
            float _chargingTime;
            float _chargedTime;
    };
}

#endif /* !CLOCKCOMPONENT_HH_ */

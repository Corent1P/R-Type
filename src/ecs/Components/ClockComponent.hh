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

    /**
     * @brief ClockComponent class for handling the clocks of the entity
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
             * @brief Set the charging time
             *
             * @param time The time to set
             */
            void setChargingTime(float time);

            /**
             * @brief Get the charging time
             *
             * @return float The charging time
             */
            float getChargingTime(void);

            /**
             * @brief Set the charged time
             *
             * @param time The time to set
             */
            void setChargedTime(float time);

            /**
             * @brief Get the charged time
             *
             * @return float The charged time
             */
            float getChargedTime(void);

            /**
             * @brief Get the clock
             *
             * @param type The type of the clock
             *
             * @return sf::Clock& The clock
             */
            sf::Clock &getClock(ClockType type);

            /**
             * @brief Get the output of the component
             *
             * @return std::string The output of the component
             */
            std::string getOutput() const;

        private:
            /**
             * @brief The vector of clocks of the entity
             *
             */
            std::vector<sf::Clock> _clock;

            /**
             * @brief The charging time
             *
             */
            float _chargingTime;

            /**
             * @brief The charged time
             *
             */
            float _chargedTime;
    };
}

#endif /* !CLOCKCOMPONENT_HH_ */

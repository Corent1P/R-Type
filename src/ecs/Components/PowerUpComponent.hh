/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** action component asign to a entity
*/

#ifndef POWERUPCOMPONENT_HPP_
#define POWERUPCOMPONENT_HPP_
#include "../IComponent.hh"

namespace RType {
    enum PowerUpType {
        NO_POWER_UP,
        SHIELD,
        FORCE_POD,
    };

    /**
     * @brief Power-up component class
     */
    class PowerUpComponent: public RType::IComponent {
        public:
            /**
             * @brief Construct a new PowerUpComponent object
             *
             * @param powerUp Initial power-up type
             */
            PowerUpComponent(PowerUpType powerUp);

            /**
             * @brief Default constructor
             */
            PowerUpComponent();

            /**
             * @brief Destroy the PowerUpComponent object
             */
            ~PowerUpComponent();

            /**
             * @brief Set the power-up type
             *
             * @param powerUpType New power-up type
             */
            void setPowerUpType(PowerUpType powerUpType);

            /**
             * @brief Get the power-up type
             *
             * @return PowerUpType Current power-up type
             */
            PowerUpType getPowerUpType() const;

            /**
             * @brief Set the power-up status
             *
             * @param powerUpType Power-up type
             * @param newBool New status
             */
            void setPowerUps(PowerUpType powerUpType, bool newBool);

            /**
             * @brief Get the power-up status
             *
             * @param powerUpType Power-up type
             * @return true If the power-up is active
             * @return false If the power-up is inactive
             */
            bool getPowerUps(PowerUpType powerUpType) const;

            /**
             * @brief Set the power-up active status
             *
             * @param powerUpType Power-up type
             * @param newBool New active status
             */
            void setPowerUpsIsActive(PowerUpType powerUpType, bool newBool);

            /**
             * @brief Get the power-up active status
             *
             * @param powerUpType Power-up type
             * @return true If the power-up is active
             * @return false If the power-up is inactive
             */
            bool getPowerUpsIsActive(PowerUpType powerUpType) const;

            /**
             * @brief Get the output as a string
             *
             * @return std::string Output string
             */
            std::string getOutput() const;
        private:
            /**
             * @brief Current power-up type
             */
            PowerUpType _powerUpType;

            /**
             * @brief Vector of power-up statuses
             */
            std::vector<bool> _powerUps;

            /**
             * @brief Vector of power-up active statuses
             */
            std::vector<bool> _powerUpsIsActive;
    };
}
#endif /* !POWERUPCOMPONENT_HPP_ */

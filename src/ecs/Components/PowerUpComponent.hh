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

    class PowerUpComponent: public RType::IComponent {
        public:
            PowerUpComponent(PowerUpType powerUp);
            PowerUpComponent();
            ~PowerUpComponent();
            void setPowerUpType(PowerUpType powerUpType);
            PowerUpType getPowerUpType() const;
            void setPowerUps(PowerUpType powerUpType, bool newBool);
            bool getPowerUps(PowerUpType powerUpType) const;
            void setPowerUpsIsActive(PowerUpType powerUpType, bool newBool);
            bool getPowerUpsIsActive(PowerUpType powerUpType) const;
            std::string getOutput() const;
        private:
            PowerUpType _powerUpType;
            std::vector<bool> _powerUps;
            std::vector<bool> _powerUpsIsActive;
    };
}
#endif /* !POWERUPCOMPONENT_HPP_ */

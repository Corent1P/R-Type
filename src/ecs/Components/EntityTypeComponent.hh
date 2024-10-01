/*
** EPITECH PROJECT, 2024
** R-type
** File description:
** Component related to the entity position
*/

#ifndef TYPECOMPONENT_HPP_
#define TYPECOMPONENT_HPP_
#include "../IComponent.hh"
namespace RType {
    enum EntityType {
        OTHER,
        WINDOW,
        PLAYER,
        MOB,
        BOSS,
        BUTTON,
        LAYER,
        WEAPON,
        POWER_UP,
    };

    enum WeaponType {
        LVL_1,
        LVL_2,
        LVL_3,
    };

    enum PowerUpType {
        NOPOWERUP,
        SHIELD,
    };

    class EntityTypeComponent: public RType::IComponent {
        public:
            EntityTypeComponent(EntityType entityType);
            ~EntityTypeComponent();
            void setEntityType(EntityType entityType);
            EntityType getEntityType() const;
            void setWeaponType(WeaponType weaponType);
            WeaponType getWeaponType() const;
            void setPowerUpType(PowerUpType powerUpType);
            PowerUpType getPowerUpType() const;
            std::string getOutput() const;
        private:
            EntityType _entityType;
            WeaponType _weaponType;
            PowerUpType _powerUpType;
    };
}
#endif /* !TYPECOMPONENT_HPP_ */

/*
** EPITECH PROJECT, 2024
** R-type
** File description:
** Component related to the entity position
*/

#ifndef TYPECOMPONENT_HPP_
#define TYPECOMPONENT_HPP_

#include "MappingInputComponent.hh"

namespace RType {
    enum EntityType {
        E_OTHER,
        E_WINDOW,
        E_PLAYER,
        E_ALLIES,
        E_SMALL_SPACESHIP,
        E_OCTOPUS,
        E_FLY,
        E_BOSS,
        E_BUTTON,
        E_LAYER,
        E_BULLET,
        E_POWER_UP,
        E_BULLET_EFFECT,
        E_HIT_EFFECT,
        E_EXPLOSION_EFFECT,
        E_TEXT,
    };

    enum WeaponType {
        LVL_1,
        LVL_2,
        LVL_3,
    };

    enum EnemyType {
        SMALL_SPACESHIP,
        OCTOPUS,
        FLY,
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
            void setEnemyType(EnemyType powerUpType);
            EnemyType getEnemyType() const;
            void setButtonType(MappingInput buttonType);
            MappingInput getButtonType() const;
            std::string getOutput() const;
            static bool isMob(EntityType);
        private:
            EntityType _entityType;
            WeaponType _weaponType;
            PowerUpType _powerUpType;
            EnemyType _enemyType;
            MappingInput _buttonType;
    };
}
#endif /* !TYPECOMPONENT_HPP_ */

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
        ALLIES,
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
            std::string getOutput() const;
        private:
            EntityType _entityType;
            WeaponType _weaponType;
            PowerUpType _powerUpType;
            EnemyType _enemyType;
    };
}
#endif /* !TYPECOMPONENT_HPP_ */

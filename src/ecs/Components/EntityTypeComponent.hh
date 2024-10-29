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
        E_ENNEMY_BULLET,
        E_HIT_EFFECT,
        E_BULLET_EFFECT,
        E_EXPLOSION_EFFECT,
        E_TEXT,
        E_ITEM_WEAPON,
        E_ITEM_SHIELD,
        E_ITEM_HEAL,
        E_SHIELD,
        E_BULLET_2,
        E_BULLET_3,
        E_BULLET_4,
        E_ITEM_FORCEPOD,
        E_FORCEPOD,
        E_FORCEPOD_BULLET,
        E_FORCEPOD_2,
        E_BULLET_LASER,
        E_BULLET_LASER_2,
        E_BULLET_LASER_3,
        E_BULLET_LASER_4,
    };

    enum WeaponType {
        LVL_1,
        LVL_2,
        LVL_3,
        LVL_4,
    };

    enum ForcePodType {
        F_NO_FORCEPOD,
        F_LVL_1,
        F_LVL_2,
    };

    enum EnemyType {
        SMALL_SPACESHIP,
        OCTOPUS,
        FLY,
    };

    class EntityTypeComponent: public RType::IComponent {
        public:
            EntityTypeComponent(EntityType entityType);
            ~EntityTypeComponent();
            void setEntityType(EntityType entityType);
            EntityType getEntityType() const;
            void setWeaponType(WeaponType weaponType);
            WeaponType getWeaponType() const;
            void setEnemyType(EnemyType powerUpType);
            EnemyType getEnemyType() const;
            void setForcePodType(ForcePodType forcePodType);
            ForcePodType getForcePodType() const;
            void setButtonType(MappingInput buttonType);
            MappingInput getButtonType() const;
            std::string getOutput() const;
            static bool isMob(EntityType);
            static bool isItem(EntityType);
            static bool isWeapon(EntityType);
            static bool isPowerUp(EntityType);
        private:
            EntityType _entityType;
            WeaponType _weaponType;
            EnemyType _enemyType;
            ForcePodType _forcePodType;
            MappingInput _buttonType;
    };
}
#endif /* !TYPECOMPONENT_HPP_ */

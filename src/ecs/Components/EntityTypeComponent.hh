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
        E_SPACE_SHIP_1,
        E_SPACE_SHIP_2,
        E_SPACE_SHIP_3,
        E_OCTOPUS,
        E_FLY,
        E_BABY_FLY,
        E_FLY_BOSS,
        E_SPACE_SHIP_BOSS,
        E_OCTOPUS_BOSS,
        E_BOMBER_BOSS,
        E_BABY_OCTOPUS,
        E_SPACE_SHIP_4,
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
        E_STING,
        E_SPACE_SHIP_BULLET,
        E_SPACE_SHIP_SEMI_DIAGONAL_UP,
        E_SPACE_SHIP_SEMI_DIAGONAL_DOWN,
        E_SPACE_SHIP_DIAGONAL_UP,
        E_SPACE_SHIP_DIAGONAL_DOWN,
        E_SOUNDS,
        E_STATIC_BOMB,
        E_ZIGZAG_BOMB,
        E_ZIGZAG_BOMB_REVERSE,
        E_HEALTHTEXT
    };

    enum WeaponType {
        LVL_1,
        LVL_2,
        LVL_3,
        LVL_4,
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
            void setButtonType(MappingInput buttonType);
            MappingInput getButtonType() const;
            std::string getOutput() const;
            static bool isMob(EntityType);
            static bool isBoss(EntityType);
            static bool isEnnemyShoot(EntityType);
            static bool isItem(EntityType);
            static bool isWeapon(EntityType);
            static bool isPowerUp(EntityType);
        private:
            EntityType _entityType;
            WeaponType _weaponType;
            EnemyType _enemyType;
            MappingInput _buttonType;
    };
}
#endif /* !TYPECOMPONENT_HPP_ */

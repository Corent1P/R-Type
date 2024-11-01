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
        E_ITEM_FORCEPOD,
        E_FORCEPOD,
        E_FORCEPOD_BULLET,
        E_FORCEPOD_2,
        E_BULLET_LASER,
        E_BULLET_LASER_2,
        E_BULLET_LASER_3,
        E_BULLET_LASER_4,
        E_FORCEPOD_3,
        E_CHARGING_EFFECT,
        E_FORCEPOD_BULLET_2,
        E_FORCEPOD_BULLET_3,
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
        E_HEALTHTEXT,
        E_SCORETEXT,
        E_HIT_EFFECT_2,
        E_HIT_EFFECT_3,
        E_HIT_EFFECT_4,
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
        F_LVL_3,
    };

    enum EnemyType {
        SMALL_SPACESHIP,
        OCTOPUS,
        FLY,
    };

    /**
     * @brief EntityTypeComponent class for handling the type of an entity
     *
     */
    class EntityTypeComponent: public RType::IComponent {
        public:
            /**
             * @brief Construct a new EntityTypeComponent object
             *
             * @param entityType The type of the entity
             */
            EntityTypeComponent(EntityType entityType);

            /**
             * @brief Destroy the EntityTypeComponent object
             *
             */
            ~EntityTypeComponent();

            /**
             * @brief Set the entity type
             *
             * @param entityType The type of the entity
             */
            void setEntityType(EntityType entityType);

            /**
             * @brief Get the entity type
             *
             * @return EntityType The type of the entity
             */
            EntityType getEntityType() const;

            /**
             * @brief Set the weapon type
             *
             * @param weaponType The type of the weapon
             */
            void setWeaponType(WeaponType weaponType);

            /**
             * @brief Get the weapon type
             *
             * @return WeaponType The type of the weapon
             */
            WeaponType getWeaponType() const;

            /**
             * @brief Set the enemy type
             *
             * @param powerUpType The type of the enemy
             */
            void setEnemyType(EnemyType powerUpType);

            /**
             * @brief Get the enemy type
             *
             * @return EnemyType The type of the enemy
             */
            EnemyType getEnemyType() const;

            /**
             * @brief Set the force pod type
             *
             * @param forcePodType The type of the force pod
             */
            void setForcePodType(ForcePodType forcePodType);

            /**
             * @brief Get the force pod type
             *
             * @return ForcePodType The type of the force pod
             */
            ForcePodType getForcePodType() const;

            /**
             * @brief Set the button type
             *
             * @param buttonType The type of the button
             */
            void setButtonType(MappingInput buttonType);

            /**
             * @brief Get the button type
             *
             * @return MappingInput The type of the button
             */
            MappingInput getButtonType() const;

            /**
             * @brief Get the output of the component
             *
             * @return std::string The output of the component
             */
            std::string getOutput() const;

            /**
             * @brief Check if the entity is a mob
             *
             * @param entityType The type of the entity
             *
             * @return true If the entity is a mob
             * @return false Otherwise
             */
            static bool isMob(EntityType);

            /**
             * @brief Check if the entity is a boss
             *
             * @param entityType The type of the entity
             *
             * @return true If the entity is a boss
             * @return false Otherwise
             */
            static bool isBoss(EntityType);

            /**
             * @brief Check if the entity is a ennemy shoot
             *
             * @param entityType The type of the entity
             *
             * @return true If the entity is a ennemy shoot
             * @return false Otherwise
             */
            static bool isEnnemyShoot(EntityType);

            /**
             * @brief Check if the entity is a item
             *
             * @param entityType The type of the entity
             *
             * @return true If the entity is a item
             * @return false Otherwise
             */
            static bool isItem(EntityType);

            /**
             * @brief Check if the entity is a weapon
             *
             * @param entityType The type of the entity
             *
             * @return true If the entity is a weapon
             * @return false Otherwise
             */
            static bool isWeapon(EntityType);

            /**
             * @brief Check if the entity is a power up
             *
             * @param entityType The type of the entity
             *
             * @return true If the entity is a power up
             * @return false Otherwise
             */
            static bool isPowerUp(EntityType);
        private:

            /**
             * @brief The type of the entity
             *
             */
            EntityType _entityType;

            /**
             * @brief The type of the weapon
             *
             */
            WeaponType _weaponType;

            /**
             * @brief The type of the enemy
             *
             */
            EnemyType _enemyType;

            /**
             * @brief The type of the force pod
             *
             */
            ForcePodType _forcePodType;

            /**
             * @brief The type of the button
             *
             */
            MappingInput _buttonType;
    };
}
#endif /* !TYPECOMPONENT_HPP_ */

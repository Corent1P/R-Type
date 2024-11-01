/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** system about all components drawing
*/

#ifndef HANDLEDRAWSYSTEM_HPP_
#define HANDLEDRAWSYSTEM_HPP_
#include "../ASystem.hh"
#include "../Components/SFWindowComponent.hh"
#include "../Components/SpriteComponent.hh"
#include "../Components/PositionComponent.hh"
#include "../Components/EntityTypeComponent.hh"
#include "../Components/LevelComponent.hh"
#include "../Components/MenuComponent.hh"

#define GET_WINDOW_FOR_DRAW w->getComponent<RType::SFWindowComponent>()

namespace RType {
    /**
     * @brief a system handling Sprite Drawing.
     *
     */
    class HandleDrawSystem: public ASystem {
        public:
            /**
             * @brief Construct a new Handle Draw System object.
             *
             * @param addEntity method used to add a new Entity to the coordinator.
             * @param deleteEntity method used to delete a Entity from the coordinator.
             */
            HandleDrawSystem(std::function<std::shared_ptr<Entity>()> addEntity, std::function<void(std::shared_ptr<Entity>)> deleteEntity);
            /**
             * @brief Destroy the Handle Draw System object.
             *
             */
            ~HandleDrawSystem();
            /**
             * @brief method looping on each entities in order to check if they have the mendatory Component in order to process the system effect.
             *        Also used to process a system effect if two distincts entites are involved in the procces.
             *
             * @param entities a vector that contains each entity stored in the coordinator.
             */
            void effects(std::vector<std::shared_ptr<RType::Entity>> entities);
            /**
             * @brief a method to verify if a entity has the right components to process the system effect.
             *
             * @param entity the entity to check
             * @return true
             * @return false
             */
            bool verifyRequiredComponent(std::shared_ptr<RType::Entity> entity);
            /**
             * @brief a method to verify if a entity has the right components to process the system effect.
             *
             * @param entity the entity to check
             * @param window the window entity
             * @return true
             * @return false
             */
            bool verifyRequiredComponent(std::shared_ptr<RType::Entity> entity, std::shared_ptr<RType::Entity> window);
        protected:
        private:
            /**
             * @brief a vector of all entities.
             *
             */
            std::vector<std::shared_ptr<RType::Entity>> _entities;
            /**
             * @brief a method drawing each entities having a sprite Hitbox.
             *
             * @param w a entity of entityType WINDOW entity.
             * @param entity a target entity.
             */
            void drawHitBox(const std::shared_ptr<RType::Entity> &w, const std::shared_ptr<RType::Entity> &entity);
    };
}

#endif /* !HANDLEDRAWSYSTEM_HPP_ */

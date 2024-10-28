/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** system about all components drawing
*/

#ifndef HANDLEDRAWTEXTSYSTEM_HPP_
#define HANDLEDRAWTEXTSYSTEM_HPP_
#include "../ASystem.hh"
#include "../Components/SFWindowComponent.hh"
#include "../Components/TextComponent.hh"
#include "../Components/PositionComponent.hh"
#include "../Components/EntityTypeComponent.hh"
#include "../Components/LevelComponent.hh"
#include "../Components/MenuComponent.hh"

#define GET_WINDOW_FOR_DRAW w->getComponent<RType::SFWindowComponent>()
#define SET_TEXT_POSITION entity->getComponent<RType::TextComponent>()->getText()->setPosition(entity->getComponent<PositionComponent>()->getPositions())

namespace RType {
    /**
     * @brief a system handling Text Drawing.
     *
     */
    class HandleDrawTextSystem: public ASystem {
        public:
            /**
             * @brief Construct a new Handle Draw Text System object.
             *
             * @param addEntity method used to add a new Entity to the coordinator.
             * @param deleteEntity method used to delete a Entity from the coordinator.
             */
            HandleDrawTextSystem(std::function<std::shared_ptr<Entity>()> addEntity, std::function<void(std::shared_ptr<Entity>)> deleteEntity);
            /**
             * @brief Destroy the Handle Draw Text System object.
             *
             */
            ~HandleDrawTextSystem();
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
             * @param entity
             * @return true
             * @return false
             */
            bool verifyRequiredComponent(std::shared_ptr<RType::Entity> entity);
            /**
             * @brief update the text in case of mapping input
             *
             * @param button
             * @param window
             */
            void updateText(std::shared_ptr<RType::Entity> button, std::shared_ptr<RType::Entity> window);
        protected:
        private:
            const std::string& getDotString(void);
            void drawHitBox(const std::shared_ptr<RType::Entity> &w, const std::shared_ptr<RType::Entity> &entity);
            std::vector<std::shared_ptr<RType::Entity>> _entities;
            std::string _dotString;
            std::size_t _dotCounter;
    };
}

#endif /* !HANDLEDRAWTEXTSYSTEM_HPP_ */

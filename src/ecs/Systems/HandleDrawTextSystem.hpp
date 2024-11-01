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
#include "../Components/HealthComponent.hh"
#include "../Components/ScoreComponent.hh"
#include "../Components/HoverEffectComponent.hh"
#include "../Components/IntRectComponent.hh"
#include "../Components/MusicComponent.hh"
#include "../Components/SoundQueueComponent.hh"
#include "../Components/AutoUpdateTextComponent.hh"
#include "../Components/SoundVolumeComponent.hh"

#define GET_WINDOW_FOR_DRAW w->getComponent<RType::SFWindowComponent>()
#define SET_TEXT_POSITION entity->getComponent<RType::TextComponent>()->getText()->setPosition(entity->getComponent<PositionComponent>()->getPositions())
#define GET_HOVER_C entity->getComponent<RType::HoverEffectComponent>()
#define GET_AUTO_UPDATE_TEXT_C text->getComponent<RType::AutoUpdateTextComponent>()

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
            /**
             * @brief a method drawing each entities having a sprite Hitbox.
             *
             * @param w a entity of entityType WINDOW entity.
             * @param entity a target entity.
             */
            static void drawHitBox(const std::shared_ptr<RType::Entity> &w, const std::shared_ptr<RType::Entity> &entity);
        protected:
        private:
            /**
             * @brief a method auto updating the text
             *
             * @param w a entity of entityType WINDOW entity.
             * @param text a target entity of entityType text.
             */
            void autoUpdateText(const std::shared_ptr<RType::Entity> &w, const std::shared_ptr<RType::Entity> &text);
            const std::string& getDotString(void);
            /**
             * @brief a vector of all entities.
             *
             */
            std::vector<std::shared_ptr<RType::Entity>> _entities;
            std::string _dotString;
            std::size_t _dotCounter;
    };
}

#endif /* !HANDLEDRAWTEXTSYSTEM_HPP_ */

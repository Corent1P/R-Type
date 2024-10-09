/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** system about all components drawing
*/

#ifndef HANDLEDRAWSYSTEM_HPP_
#define HANDLEDRAWSYSTEM_HPP_
#include "../ASystem.hh"
#include ".././Components/SFWindowComponent.hh"
#include ".././Components/SpriteComponent.hh"
#include ".././Components/PositionComponent.hh"
#include ".././Components/EntityTypeComponent.hh"
#include ".././Components/LevelComponent.hh"

#define GET_WINDOW_FOR_DRAW w->getComponent<RType::SFWindowComponent>()
namespace RType {
    class HandleDrawSystem: public ASystem {
        public:
            HandleDrawSystem(std::function<std::shared_ptr<Entity>()> addEntity, std::function<void(std::shared_ptr<Entity>)> deleteEntity);
            ~HandleDrawSystem();
            void effects(std::vector<std::shared_ptr<RType::Entity>> entities);
            bool verifyRequiredComponent(std::shared_ptr<RType::Entity> entity);
        protected:
        private:
            std::vector<std::shared_ptr<RType::Entity>> _entities;

            void drawHitBox(const std::shared_ptr<RType::Entity> &w, const std::shared_ptr<RType::Entity> &entity);
    };
}

#endif /* !HANDLEDRAWSYSTEM_HPP_ */

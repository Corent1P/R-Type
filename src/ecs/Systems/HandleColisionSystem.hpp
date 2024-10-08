/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** system used to handle entity colision
*/

#ifndef HANDLECOLISIONSYTEM_HPP_
#define HANDLECOLISIONSYTEM_HPP_
#include "../ASystem.hh"
#include ".././Components/SFWindowComponent.hh"
#include ".././Components/EventComponent.hh"
#include ".././Components/DirectionComponent.hh"
#include ".././Components/EntityTypeComponent.hh"
#include ".././Components/SpriteComponent.hh"
#include ".././Components/ActionComponent.hh"
#include ".././Components/PositionComponent.hh"
#include ".././Components/DirectionPatternComponent.hh"
#include ".././Components/TextureComponent.hh"
#include ".././Components/ClockComponent.hh"
#include ".././Components/VelocityComponent.hh"
#include ".././Components/IntRectComponent.hh"

namespace RType {

    class HandleColisionSystem: public  RType::ASystem {
        public:
            HandleColisionSystem(std::function<std::shared_ptr<Entity>()> addEntity, std::function<void(std::shared_ptr<Entity>)> deleteEntity);
            ~HandleColisionSystem();
            void effects(std::vector<std::shared_ptr<RType::Entity>> entities);
            void effect(std::shared_ptr<RType::Entity> entity);
            bool verifyRequiredComponent(std::shared_ptr<RType::Entity> entity);
        protected:
        private:
    };
}
#endif /* !HANDLECOLISIONSYTEM_HPP_ */

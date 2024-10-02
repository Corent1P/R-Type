/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** system used to handle entity shoot
*/

#ifndef HANDLESHOOTSYTEM_HPP_
#define HANDLESHOOTSYTEM_HPP_
#include "../ASystem.hh"
#include ".././Components/SFWindowComponent.hh"
#include ".././Components/EventComponent.hh"
#include ".././Components/DirectionComponent.hh"
#include ".././Components/EntityTypeComponent.hh"
#include ".././Components/SpriteComponent.hh"
#include ".././Components/ActionComponent.hh"
#include ".././Components/PositionComponent.hh"

namespace RType {

    class HandleShootSystem: public  RType::ASystem {
        public:
            HandleShootSystem(std::function<void(std::shared_ptr<Entity>)> addEntity, std::function<void(std::shared_ptr<Entity>)> deleteEntity);
            ~HandleShootSystem();
            void effects(std::vector<std::shared_ptr<RType::Entity>> entities);
            void effect(std::shared_ptr<RType::Entity> entity);
            bool verifyRequiredComponent(std::shared_ptr<RType::Entity> entity);
        protected:
        private:
    };
}
#endif /* !HANDLESHOOTSYTEM_HPP_ */

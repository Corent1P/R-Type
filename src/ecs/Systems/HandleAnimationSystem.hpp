/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** System handling any entity based on their type
*/

#ifndef HANDLEANIMATIONSYSTEM_HPP_
#define HANDLEANIMATIONSYSTEM_HPP_
#include "../ASystem.hh"
#include ".././Components/SFWindowComponent.hh"
#include ".././Components/SpriteComponent.hh"
#include ".././Components/PositionComponent.hh"
#include ".././Components/ClockComponent.hh"
#include ".././Components/EntityTypeComponent.hh"

namespace RType {
    class HandleAnimationSystem: public ASystem {
        public:
            HandleAnimationSystem(std::function<std::shared_ptr<Entity>()> addEntity, std::function<void(std::shared_ptr<Entity>)> deleteEntity);
            ~HandleAnimationSystem();
            void effect(std::shared_ptr<RType::Entity> entity);
            bool verifyRequiredComponent(std::shared_ptr<RType::Entity> entity);
        protected:
        private:
            std::vector<std::shared_ptr<RType::Entity>> _entities;
    };
}

#endif /* !HANDLEANIMATIONSYSTEM_HPP_ */

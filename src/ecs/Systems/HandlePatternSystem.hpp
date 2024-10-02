/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** System handling direction pattern for any entity
*/

#ifndef HANDLEPATTERNSYSTEM_HPP_
#define HANDLEPATTERNSYSTEM_HPP_
#include "../ASystem.hh"
#include ".././Components/SFWindowComponent.hh"
#include ".././Components/SpriteComponent.hh"
#include ".././Components/PositionComponent.hh"
#include ".././Components/ClockComponent.hh"
#include ".././Components/EntityTypeComponent.hh"
#include ".././Components/DirectionPatternComponent.hh"

namespace RType {
    class HandlePatternSystem: public ASystem {
        public:
            HandlePatternSystem(std::function<void(std::shared_ptr<Entity>)> addEntity, std::function<void(std::shared_ptr<Entity>)> deleteEntity);
            ~HandlePatternSystem();
            void effect(std::shared_ptr<RType::Entity> entity);
            bool verifyRequiredComponent(std::shared_ptr<RType::Entity> entity);
        protected:
        private:
            std::vector<std::shared_ptr<RType::Entity>> _entities;
    };
}

#endif /* !HANDLEPATTERNSYSTEM_HPP_ */

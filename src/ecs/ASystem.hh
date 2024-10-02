/*
** EPITECH PROJECT, 2024
** R-type
** File description:
** Interface for systems
*/

#ifndef ASYSTEM_HPP_
#define ASYSTEM_HPP_

#include "ISystem.hh"
#include "math.h"
#include <functional>

namespace RType {
    class ASystem: public ISystem {
        public:
            ASystem(SystemType type = BASIC, std::function<void(std::shared_ptr<Entity>)> addEntity = nullptr, std::function<void(std::shared_ptr<Entity>)> deleteEntity = nullptr);
            ~ASystem() = default;
            void effects(std::vector<std::shared_ptr<RType::Entity>> entities);
            void effect(std::shared_ptr<RType::Entity> entity);

            bool verifyRequiredComponent(std::shared_ptr<RType::Entity> entity);
            SystemType getType() const;
        protected:
            SystemType _type;
            std::function<void(std::shared_ptr<Entity>)> _addEntity;
            std::function<void(std::shared_ptr<Entity>)> _deleteEntity;
    };
}
#endif /* !ASYSTEM_HPP_ */

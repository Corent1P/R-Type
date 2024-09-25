/*
** EPITECH PROJECT, 2024
** R-type
** File description:
** Interface for systems
*/

#ifndef ASYSTEM_HPP_
#define ASYSTEM_HPP_

#include "ISystem.hh"
namespace RType {
    class ASystem: public ISystem {
        public:
            ASystem(SystemType type = BASIC);
            ~ASystem() = default;
            void effects(std::vector<std::shared_ptr<RType::Entity>> entities);
            void effect(std::shared_ptr<RType::Entity> entity);

            bool verifyRequiredComponent(std::shared_ptr<RType::Entity> entity);
            SystemType getType() const;
        protected:
            SystemType _type;
    };
}
#endif /* !ASYSTEM_HPP_ */

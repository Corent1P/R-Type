/*
** EPITECH PROJECT, 2024
** R-type
** File description:
** Interface for systems
*/

#ifndef ASYSTEM_HPP_
#define ASYSTEM_HPP_

#include "ISystem.hpp"
namespace RType {
    class ASystem: public ISystem {
        public:
            ASystem();
            ~ASystem() = default;
            void effect();
            bool verifyRequiredComponent();
            SystemType getType() const;
        protected:
            SystemType _type;
    };
}
#endif /* !ASYSTEM_HPP_ */

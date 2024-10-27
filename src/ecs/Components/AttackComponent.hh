/*
** EPITECH PROJECT, 2024
** R-type
** File description:
** Attack component
*/

#ifndef ATTACKCOMPONENT_HPP_
#define ATTACKCOMPONENT_HPP_

#include "../IComponent.hh"
#include <functional>
#include "../Entity.hpp"
#include "./AttackPatterns/AttackPatterns.hh"

#define ATTACK_PATTERNS std::function<void(std::shared_ptr<RType::Entity>, std::function<std::shared_ptr<Entity>()>, std::function<void(const std::basic_string<unsigned char> &message)>)>

namespace RType {
    enum Pattern {
            SPAWN_BABY_FLY,
            SPAWN_STING,
            SPACE_SHIP_SHOOT,
            WAVE_SHOOT,
            SPAWN_BABY_OCTOPUS,
            SPAWN_KAMIKAZE_OCTOPUS
    };

    class AttackComponent: public RType::IComponent {
        public:
            AttackComponent();
            ~AttackComponent() = default;
            void pushBackAttacksPatterns(Pattern pattern);
            void pushBackAttacksPatterns(std::string pattern);
            void executeCurrentAttackPattern(std::shared_ptr<RType::Entity> boss, std::function<std::shared_ptr<Entity>()> addEntity, std::function<void(const std::basic_string<unsigned char> &message)> sendMessageToAllClient);
            void nextAttackPattern(void);
            std::size_t getNumberOfPattern(void) const;
            std::size_t getCurrentPatternIndex(void) const;
            std::string getOutput() const;
        private:
            std::size_t _currentPatternIndex;
            std::vector<ATTACK_PATTERNS> _patterns;
    };
}

#endif /* !ATTACKCOMPONENT_HPP_ */

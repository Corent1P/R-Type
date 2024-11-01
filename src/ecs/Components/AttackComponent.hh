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
            SPAWN_KAMIKAZE_OCTOPUS,
            SPAWN_WALL_STATIC_BOMB,
            SPAWN_WALL_ZIGZAG_BOMB
    };
    /**
     * @brief AttackComponent class for handling the attack patterns of the bosses
     *
     */
    class AttackComponent: public RType::IComponent {
        public:
            /**
             * @brief Construct a new Attack Component object
             *
             */
            AttackComponent();

            /**
             * @brief Destroy the Attack Component object
             *
             */
            ~AttackComponent() = default;

            /**
             * @brief Push a new attack pattern
             *
             * @param pattern The pattern to push
             */
            void pushBackAttacksPatterns(Pattern pattern);

            /**
             * @brief Push a new attack pattern
             *
             * @param pattern The pattern to push
             */
            void pushBackAttacksPatterns(std::string pattern);

            /**
             * @brief Execute the current attack pattern
             *
             * @param boss The boss entity
             * @param addEntity The function to add an entity
             * @param sendMessageToAllClient The function to send a message to all clients
             */
            void executeCurrentAttackPattern(std::shared_ptr<RType::Entity> boss, std::function<std::shared_ptr<Entity>()> addEntity, std::function<void(const std::basic_string<unsigned char> &message)> sendMessageToAllClient);

            /**
             * @brief Get the next attack pattern
             *
             */
            void nextAttackPattern(void);

            /**
             * @brief Get the number of pattern
             *
             * @return std::size_t The number of pattern
             */
            std::size_t getNumberOfPattern(void) const;

            /**
             * @brief Get the current pattern index
             *
             * @return std::size_t The current pattern index
             */
            std::size_t getCurrentPatternIndex(void) const;

            /**
             * @brief Get the output of the component
             *
             * @return std::string The output of the component
             */
            std::string getOutput() const;

        private:
            /**
             * @brief The current pattern index
             *
             */
            std::size_t _currentPatternIndex;

            /**
             * @brief The vector of attack patterns
             *
             */
            std::vector<ATTACK_PATTERNS> _patterns;
    };
}

#endif /* !ATTACKCOMPONENT_HPP_ */

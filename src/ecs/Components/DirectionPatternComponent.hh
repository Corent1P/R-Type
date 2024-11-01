/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** direction component assign to a entity movement
*/

#ifndef DIRECTIONPATTERNCOMPONENT_HPP_
#define DIRECTIONPATTERNCOMPONENT_HPP_
#include "../IComponent.hh"
#include <SFML/Graphics.hpp>

namespace RType {
    enum PatternType {
        NO_PATTERN,
        STRAIGHT_UP,
        STRAIGHT_DOWN,
        STRAIGHT_LEFT,
        STRAIGHT_RIGHT,
        UP_N_DOWN_LEFT,
        UP_N_DOWN_RIGHT,
        LEFT_N_RIGHT,
        UP_THEN_DOWN,
        FOLLOW_PLAYER,
        ZIGZAG_LEFT,
        SEMI_DIAGONAL_UP,
        SEMI_DIAGONAL_DOWN,
        DIAGONAL_UP,
        DIAGONAL_DOWN,
        ZIGZAG_REVERSE_LEFT,
        REVERSE_UP_N_DOWN_RIGHT
    };
    /**
     * @brief DirectionPatternComponent class for handling the direction pattern of an entity
     *
     */
    class DirectionPatternComponent: public RType::IComponent {
        public:
            /**
             * @brief Construct a new DirectionPatternComponent object
             *
             */
            DirectionPatternComponent();

            /**
             * @brief Construct a new DirectionPatternComponent object
             *
             * @param patternType The pattern to set
             */
            DirectionPatternComponent(PatternType patternType);

            /**
             * @brief Destroy the DirectionPatternComponent object
             *
             */
            ~DirectionPatternComponent();

            /**
             * @brief Set the pattern type
             *
             * @param patternType The pattern to set
             */
            void setPatternType(PatternType patternType);

            /**
             * @brief Get the pattern type
             *
             * @return PatternType The pattern
             */
            PatternType getPatternType() const;

            /**
             * @brief Set the pattern
             *
             * @param pattern The pattern to set
             */
            void setPattern(sf::Vector2f pattern);

            /**
             * @brief Get the pattern
             *
             * @return sf::Vector2f The pattern
             */
            sf::Vector2f getPattern() const;

            /**
             * @brief Set the entity to follow
             *
             * @param entityToFollow The entity to follow
             */
            void setEntityToFollow(uint16_t entityToFollow);

            /**
             * @brief Get the entity to follow
             *
             * @return uint16_t The entity to follow
             */
            uint16_t getEntityToFollow() const;

            /**
             * @brief Set the direction for zigzag
             *
             * @param directionForZigZag The direction for zigzag
             */
            void setDirectionForZigZag(bool directionForZigZag);

            /**
             * @brief Get the direction for zigzag
             *
             * @return bool The direction for zigzag
             */
            bool getDirectionForZigZag() const;

            /**
             * @brief Get the Output object
             *
             * @return std::string
             */
            std::string getOutput() const;

            /**
             * @brief Check if the pattern is right
             *
             * @param pattern The pattern to check
             *
             * @return true If the pattern is right
             * @return false Otherwise
             */
            static bool isPatternRight(PatternType pattern);

            /**
             * @brief Check if the pattern is left
             *
             * @param pattern The pattern to check
             *
             * @return true If the pattern is left
             * @return false Otherwise
             */
            static bool isPatternLeft(PatternType pattern);

        private:
            /**
             * @brief The pattern type
             *
             */
            PatternType _patternType;

            /**
             * @brief The pattern
             *
             */
            sf::Vector2f _pattern;

            /**
             * @brief The entity to follow
             *
             */
            uint16_t _entityToFollow = 0;

            /**
             * @brief The direction for zigzag
             *
             */
            bool _directionForZigZag = false;
    };
}
#endif /* !DIRECTIONPATTERNCOMPONENT_HPP_ */

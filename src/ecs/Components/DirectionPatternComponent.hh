/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** direction component asign to a entity movement 
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
    };

    class DirectionPatternComponent: public RType::IComponent {
        public:
            DirectionPatternComponent();
            DirectionPatternComponent(PatternType patternType);
            ~DirectionPatternComponent();
            void setPatternType(PatternType patternType);
            PatternType getPatternType() const;
            void setPattern(sf::Vector2f pattern);
            sf::Vector2f getPattern() const;
            std::string getOutput() const;
        private:
            PatternType _patternType;
            sf::Vector2f _pattern;
    };
}
#endif /* !DIRECTIONPATTERNCOMPONENT_HPP_ */

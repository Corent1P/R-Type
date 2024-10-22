/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** input component asign to a entity movement
*/

#ifndef MAPPININPUTCOMPONENT_HPP_
#define MAPPININPUTCOMPONENT_HPP_
#include "../IComponent.hh"
#include <SFML/Graphics.hpp>
namespace RType {
    enum MappingInput {
        INPUT_UNDEFINED = -1,
        INPUT_UP,
        INPUT_DOWN,
        INPUT_LEFT,
        INPUT_RIGHT,
        INPUT_SHOOT
    };

    class MappingInputComponent: public RType::IComponent {
        public:
            MappingInputComponent();
            ~MappingInputComponent() = default;
            void setMappingInput(sf::Keyboard::Key newKey);
            sf::Keyboard::Key getMappingInput(MappingInput key) const;
            const std::unordered_map<RType::MappingInput, sf::Keyboard::Key>& getMappingInputs() const;
            void setInputToDefined(MappingInput key);
            const RType::MappingInput& getInputToDefined(void);
            void initInput(void);
            void clearInput(sf::Keyboard::Key key);
            static std::string getKeyName(sf::Keyboard::Key key);
            std::string getOutput() const;
        private:
            std::unordered_map<MappingInput, sf::Keyboard::Key> _inputs;
            MappingInput _inputToDefined;
    };
}
#endif /* !MAPPININPUTCOMPONENT_HPP_ */

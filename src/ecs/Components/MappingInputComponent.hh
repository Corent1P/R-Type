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
    /**
     * @brief Enum for different mapping inputs
     */
    enum MappingInput {
        INPUT_UNDEFINED = -1,
        INPUT_UP,
        INPUT_DOWN,
        INPUT_LEFT,
        INPUT_RIGHT,
        INPUT_SHOOT
    };

    /**
     * @brief Mapping input component class
     */
    class MappingInputComponent: public RType::IComponent {
        public:
            /**
             * @brief Construct a new Mapping Input Component object
             */
            MappingInputComponent();

            /**
             * @brief Set the Mapping Input
             *
             * @param newKey New key to map
             */
            void setMappingInput(sf::Keyboard::Key newKey);

            /**
             * @brief Get the Mapping Input
             *
             * @param key Mapping input key
             * @return sf::Keyboard::Key Mapped key
             */
            sf::Keyboard::Key getMappingInput(MappingInput key) const;

            /**
             * @brief Get all Mapping Inputs
             *
             * @return const std::unordered_map<RType::MappingInput, sf::Keyboard::Key>& Reference to the mapping inputs
             */
            const std::unordered_map<RType::MappingInput, sf::Keyboard::Key>& getMappingInputs() const;

            /**
             * @brief Set the Input to Defined
             *
             * @param key Mapping input key
             */
            void setInputToDefined(MappingInput key);

            /**
             * @brief Get the Input to Defined
             *
             * @return const RType::MappingInput& Reference to the input to defined
             */
            const RType::MappingInput& getInputToDefined(void);

            /**
             * @brief Initialize the input
             */
            void initInput(void);

            /**
             * @brief Clear the input
             *
             * @param key Key to clear
             */
            void clearInput(sf::Keyboard::Key key);

            /**
             * @brief Get the Key Name
             *
             * @param key Key to get the name of
             * @return std::string Key name
             */
            static std::string getKeyName(sf::Keyboard::Key key);

            /**
             * @brief Get the Output as a string
             *
             * @return std::string Output string
             */
            std::string getOutput() const;

        private:
            /**
             * @brief Mapping inputs
             */
            std::unordered_map<MappingInput, sf::Keyboard::Key> _inputs;

            /**
             * @brief Input to be defined
             */
            MappingInput _inputToDefined;
    };
}
#endif /* !MAPPININPUTCOMPONENT_HPP_ */

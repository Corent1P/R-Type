/*
** EPITECH PROJECT, 2024
** R-type
** File description:
** SFML window component
*/

#ifndef SFWINDOWCOMPONENT_HH_
#define SFWINDOWCOMPONENT_HH_
#include <SFML/Graphics.hpp>
#include "../Include.hh"
#include "../IComponent.hh"

namespace RType {

    /**
     * @brief SFML window component class
     */
    class SFWindowComponent: public RType::IComponent {
        public:
            /**
             * @brief Construct a new SFWindowComponent object
             *
             * @param screenWidth Width of the screen
             * @param screenHeight Height of the screen
             */
            SFWindowComponent(int screenWidth, int screenHeight);

            /**
             * @brief Destroy the SFWindowComponent object
             */
            ~SFWindowComponent();

            /**
             * @brief Get the window object
             *
             * @return std::shared_ptr<sf::RenderWindow> Shared pointer to the window
             */
            std::shared_ptr<sf::RenderWindow> getWindow() const;

            /**
             * @brief Get the output as a string
             *
             * @return std::string Output string
             */
            std::string getOutput() const;

            /**
             * @brief Check if the window is open
             *
             * @return true If the window is open
             * @return false If the window is closed
             */
            bool getIsOpen();
        protected:
        private:
            /**
             * @brief Shared pointer to the SFML window
             */
            std::shared_ptr<sf::RenderWindow> _window;
    };
}

#endif /* !SFWINDOWCOMPONENT_HH_ */

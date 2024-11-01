/*
** EPITECH PROJECT, 2024
** R-type
** File description:
** Menu component
*/

#pragma once

#include "../IComponent.hh"

#define GET_MENU getComponent<RType::MenuComponent>()

namespace RType {
    /**
     * @brief Enum for different menu states
     */
    enum Menu {
        EVERYWHERE,
        HOME,
        OPTIONS,
        MAPPING_INPUT,
        LOADING,
        GAME,
        DEAD,
        WIN
    };

    /**
     * @brief Menu component class
     */
    class MenuComponent: public RType::IComponent {
        public:
            /**
             * @brief Construct a new Menu Component object
             *
             * @param menu Initial menu state
             */
            MenuComponent(Menu menu);

            /**
             * @brief Destroy the Menu Component object
             */
            ~MenuComponent();

            /**
             * @brief Set the Menu state
             *
             * @param menu New menu state
             */
            void setMenu(Menu menu);

            /**
             * @brief Get the Menu state
             *
             * @return RType::Menu Current menu state
             */
            RType::Menu getMenu() const;

            /**
             * @brief Get the Output as a string
             *
             * @return std::string Output string
             */
            std::string getOutput() const;

            /**
             * @brief Compare with another MenuComponent
             *
             * @param other Another MenuComponent
             * @return true If both components are equal
             * @return false Otherwise
             */
            bool operator==(const MenuComponent &other) const;

        private:
            /**
             * @brief Current menu state
             */
            Menu _menu;
    };
}

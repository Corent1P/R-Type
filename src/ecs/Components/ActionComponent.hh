/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** action component asign to a entity
*/

#ifndef ACTIONCOMPONENT_HPP_
#define ACTIONCOMPONENT_HPP_
#include "../IComponent.hh"

namespace RType {
    enum Action {
        NOTHING,
        SHOOTING,
        CHARGING_SHOT,
    };

    /**
     * @brief ActionComponent class for handling the actions of an entity
     *
     */
    class ActionComponent: public RType::IComponent {
        public:
            /**
             * @brief Construct a new ActionComponent object
             *
             */
            ActionComponent();

            /**
             * @brief Destroy the ActionComponent object
             *
             */
            ~ActionComponent();

            /**
             * @brief Set the actions of the entity
             *
             * @param direction The action to set
             * @param newBool The new value of the action
             */
            void setActions(Action direction, bool newBool);

            /**
             * @brief Get the actions of the entity
             *
             * @param direction The action to get
             *
             * @return bool The value of the action
             */
            bool getActions(Action direction) const;

            /**
             * @brief Get the output of the component
             *
             * @return std::string The output of the component
             */
            std::string getOutput() const;

        private:
            /**
             * @brief The vector of actions of the entity
             *
             */
            std::vector<bool> _actions;
    };
}
#endif /* !ACTIONCOMPONENT_HPP_ */

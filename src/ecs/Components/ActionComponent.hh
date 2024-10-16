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
    };
    /**
     * @brief Component Player action
     *
     */
    class ActionComponent: public RType::IComponent {
        public:
            /**
             * @brief Construct a new Action Component object
             *
             * @param Action
             *
             */
            ActionComponent(Action Action);
            /**
             * @brief Construct a new Action Component object
             *
             */
            ActionComponent();
            /**
             * @brief Destroy the Action Component object
             *
             */
            ~ActionComponent();
            /**
             * @brief Set the Action object
             *
             * @param entityType
             *
             */
            void setAction(Action entityType);
            /**
             * @brief Get the Action object
             *
             * @return Action
             */
            Action getAction() const;
            /**
             * @brief Set the Actions object
             *
             * @param direction
             * @param newBool
             */
            void setActions(Action action, bool newBool);
            /**
             * @brief Get the Actions object
             *
             * @param action
             * @return true
             * @return false
             */
            bool getActions(Action action) const;
            /**
             * @brief Get the Output object
             *
             * @return std::string
             */
            std::string getOutput() const;
        private:
            Action _action;
            std::vector<bool> _actions;
    };
}
#endif /* !ACTIONCOMPONENT_HPP_ */

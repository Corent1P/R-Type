/*
** EPITECH PROJECT, 2024
** R-type
** File description:
** handling event system
*/

#ifndef HANDLEEVENTSYTEM_HPP_
#define HANDLEEVENTSYTEM_HPP_
#include "ISystem.hh"

class HandleEventSytem {
    public:
        HandleEventSytem();
        ~HandleEventSytem();
        void effect(std::shared_ptr<Entity> entities);
        bool verifyRequiredComponent(Entity entity);
        SystemType getType() const;
    protected:
    private:
};

#endif /* !HANDLEEVENTSYTEM_HPP_ */

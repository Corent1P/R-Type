/*
** EPITECH PROJECT, 2024
** R-type
** File description:
** Interface for systems
*/

#ifndef ISYSTEM_HPP_
#define ISYSTEM_HPP_

class ISystem {
    public:
        virtual ~ISystem() = 0;
        virtual void effect() = 0;
        virtual bool verifyRequierdComponent() = 0;
};

#endif /* !ISYSTEM_HPP_ */

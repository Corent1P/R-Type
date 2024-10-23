/*
** EPITECH PROJECT, 2024
** rType
** File description:
** ISystem
*/

#include "ISystem.hh"

std::ostream &operator<<(std::ostream &s, const RType::ISystem &system)
{
    s << "System: ";

    switch (system.getType()) {
        case RType::S_BASIC:
            s << "Basic system";
            break;
        case RType::S_EVENT:
            s << "Event system";
            break;
        case RType::S_CLEAR:
            s << "Clear system";
            break;
        case RType::S_DRAW:
            s << "Draw system";
            break;
        case RType::S_DRAWTEXT:
            s << "Draw Text system";
            break;
        case RType::S_DISPLAY:
            s << "Display system";
            break;
        case RType::S_MOVE:
            s << "Movement system";
            break;
        case RType::S_ANIMATION:
            s << "Animation system";
            break;
        case RType::S_PATTERN:
            s << "Pattern system";
            break;
        case RType::S_SHOOT:
            s << "Shoot system";
            break;
        case RType::S_COLISION:
            s << "Collision system";
            break;
        default:
            s << "Unknown system";
            break;
    }
    return s;
}

/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** includes
*/

#pragma once

#include <array>
#include <ctime>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <boost/asio.hpp>
#include <map>


#include "../ecs/Coordinator.hh"
#include "../ecs/Components/PositionComponent.hh"
#include "../ecs/Components/HealthComponent.hh"
#include "../ecs/Components/EntityTypeComponent.hh"
#include "../ecs/Components/EventComponent.hh"
#include "../ecs//Components/DirectionComponent.hh"
#include "../ecs//Components/ClockComponent.hh"
#include "../ecs//Components/DifficultyComponent.hh"
#include "../ecs/Systems/HandleEventSystem.hpp"
#include "../ecs/Systems/HandleMoveSystem.hpp"
#include "../ecs/Systems/HandleEntitySpawnSystem.hh"

using boost::asio::ip::udp;

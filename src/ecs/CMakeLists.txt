set(SRC_CLIENT
    ./Coordinator.cpp
    ./Entity.cpp
    ./ISystem.cpp
    ./ASystem.cpp
    ./Error.cpp
    ../client/Game.cpp
)

set(SRC_COMPONENTS
    ./Components/PositionComponent.cpp
    ./Components/HealthComponent.cpp
    ./Components/EntityTypeComponent.cpp
    ./Components/SFWindowComponent.cpp
    ./Components/EventComponent.cpp
    ./Components/TextureComponent.cpp
    ./Components/SpriteComponent.cpp
    ./Components/DirectionComponent.cpp
    ./Components/ClockComponent.cpp
    ./Components/ActionComponent.cpp
    ./Components/DirectionPatternComponent.cpp
    ./Components/VelocityComponent.cpp
    ./Components/LevelComponent.cpp
)

set(SRC_SYSTEMS
    ./Systems/HandleEventSystem.cpp
    ./Systems/HandleDrawSystem.cpp
    ./Systems/HandleMoveSystem.cpp
    ./Systems/HandleAnimationSystem.cpp
    ./Systems/HandlePatternSystem.cpp
    ./Systems/HandleShootSystem.cpp
)

add_library(ecs ${SRC_CLIENT} ${SRC_COMPONENTS} ${SRC_SYSTEMS})

target_compile_options(ecs PRIVATE
    -fPIC
    -Wall
    -Wextra
    -Werror
    -g
)

find_package(SFML COMPONENTS system window graphics network audio REQUIRED)
target_link_libraries(ecs sfml-system sfml-window sfml-graphics sfml-network sfml-audio)
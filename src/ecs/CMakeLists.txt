set(SRC_ECS
    ./Coordinator.cpp
    ./Entity.cpp
    ./ISystem.cpp
    ./ASystem.cpp
    ./EcsError.cpp
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
    ./Components/ScaleComponent.cpp
    ./Components/IntRectComponent.cpp
)

set(SRC_SYSTEMS
    ./Systems/HandleEventSystem.cpp
    ./Systems/HandleDrawSystem.cpp
    ./Systems/HandleMoveSystem.cpp
    ./Systems/HandleMoveSpriteSystem.cpp
    ./Systems/HandleAnimationSystem.cpp
    ./Systems/HandlePatternSystem.cpp
    ./Systems/HandleShootSystem.cpp
    ./Systems/HandleColisionSystem.cpp
    ./Systems/HandleEntitySpawnSystem.cpp
)

set(SRC_CLIENTS # To Remove
    ../client/communication/Client.cpp
    ../client/ClientError.cpp

)

add_library(ecs ${SRC_ECS} ${SRC_COMPONENTS} ${SRC_SYSTEMS} ${SRC_CLIENTS} )

if (NOT WIN32)
    target_compile_options(ecs PRIVATE
        -fPIC
        -g
    )
endif()

find_package(SFML 2.6.1 COMPONENTS system window graphics network audio REQUIRED)
target_link_libraries(ecs PUBLIC sfml::sfml)
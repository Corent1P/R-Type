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
    ./Components/MappingInputComponent.cpp
    ./Components/TextComponent.cpp
    ./Components/ClickEffectComponent.cpp
    ./Components/MenuComponent.cpp
    ./Components/ShootIntervalComponent.cpp
    ./Components/DamageComponent.cpp
    ./Components/PowerUpComponent.cpp
    ./Components/ParseLevelInfoComponent.cpp
    ./Components/AttackComponent.cpp
    ./Components/AttackPatterns/AttackPatterns.cpp
    ./Components/SoundComponent.cpp
    ./Components/MusicComponent.cpp
    ./Components/SoundBufferComponent.cpp
    ./Components/SoundQueueComponent.cpp
    ./Components/DifficultyComponent.cpp
    ./Components/ScoreComponent.cpp
    ./Components/HoverEffectComponent.cpp
    ./Components/AutoUpdateTextComponent.cpp
    ./Components/SoundVolumeComponent.cpp
)

set(SRC_SYSTEMS
    ./Systems/HandleEventSystem.cpp
    ./Systems/HandleClearSystem.cpp
    ./Systems/HandleDrawSystem.cpp
    ./Systems/HandleDrawTextSystem.cpp
    ./Systems/HandleSoundSystem.cpp
    ./Systems/HandleMusicSystem.cpp
    ./Systems/HandleDisplaySystem.cpp
    ./Systems/HandleMoveSystem.cpp
    ./Systems/HandleMoveSpriteSystem.cpp
    ./Systems/HandleAnimationSystem.cpp
    ./Systems/HandlePatternSystem.cpp
    ./Systems/HandleShootSystem.cpp
    ./Systems/HandleCollisionSystem.cpp
    ./Systems/HandleEntitySpawnSystem.cpp
    ./Systems/HandleBossAttackSystem.cpp

)
# set(SFML_DIR "../../vcpkg_installed/x64-windows/share/sfml")
add_library(ecs ${SRC_ECS} ${SRC_COMPONENTS} ${SRC_SYSTEMS} )

if (NOT WIN32)
    target_compile_options(ecs PRIVATE
        -fPIC
    )
endif()

find_package(Boost REQUIRED)
find_package(Lua REQUIRED)
find_package(SFML COMPONENTS system window graphics network audio REQUIRED)

target_include_directories(ecs PRIVATE ${LUA_INCLUDE_DIR})

target_link_libraries(ecs PRIVATE
    ${LUA_LIBRARIES}
    JsonCpp::JsonCpp
    Boost::boost
    sfml-system
    sfml-window
    sfml-graphics
    sfml-network
    sfml-audio
)

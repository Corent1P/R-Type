set(SRC_CLIENT
    ./main.cpp
    ./Game.cpp
    ./communication/Client.cpp
    ./ClientError.cpp
)

add_executable(r-type_client ${SRC_CLIENT})

file(COPY ${CMAKE_SOURCE_DIR}/ressources DESTINATION .)

if (NOT WIN32)
    target_compile_options(r-type_client PRIVATE
        -fPIC
        -g
    )
endif()

target_link_libraries(r-type_client PRIVATE
    ecs
    protocolHandler
    JsonCpp::JsonCpp
    Boost::boost
    sfml-system
    sfml-window
    sfml-graphics
)

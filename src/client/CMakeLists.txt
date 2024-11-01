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
    )
endif()

if (APPLE)
    find_library(COREAUDIO_LIBRARY CoreAudio)
    find_library(AUDIOUNIT_LIBRARY AudioUnit)
    find_library(AUDIO_TOOLBOX_LIBRARY AudioToolbox)

    target_link_libraries(r-type_client PRIVATE
        ${COREAUDIO_LIBRARY}
        ${AUDIOUNIT_LIBRARY}
        ${AUDIO_TOOLBOX_LIBRARY}
        ecs
        protocolHandler
        JsonCpp::JsonCpp
        Boost::boost
        sfml-system
        sfml-window
        sfml-graphics
        sfml-audio
    )
else()
    target_link_libraries(r-type_client PRIVATE
        ecs
        protocolHandler
        JsonCpp::JsonCpp
        Boost::boost
        sfml-system
        sfml-window
        sfml-graphics
        sfml-audio
    )
endif()
cmake_minimum_required(VERSION 3.25)
project(Gra_balony)

set(CMAKE_CXX_STANDARD 20)

# Use pkg-config to find SFML
include(FindPkgConfig)
pkg_check_modules(SFML REQUIRED sfml-all)

add_executable(${PROJECT_NAME} main.cpp
        ball.cpp
        ball.h
        EventHandler.h
        Globals.h

)

# Link against SFML libraries
target_link_libraries(${PROJECT_NAME}
        ${SFML_LIBRARIES}
)

# Include SFML headers
target_include_directories(${PROJECT_NAME} PRIVATE ${SFML_INCLUDE_DIRS})

# Add SFML compile flags
target_compile_options(${PROJECT_NAME} PRIVATE ${SFML_CFLAGS_OTHER})
cmake_minimum_required(VERSION 3.28)
project(rocket_ascent_simulator)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(SOURCES
        src/main.cpp
        src/environment/environment.cpp
        src//helper/data_handling.cpp
        src/integrator/integrator.cpp
        src/io/basic_ui.cpp
        src/rocket/motor.cpp
        src/rocket/rocket.cpp
)

# 2. Pass the list to your executable
add_executable(RAS ${SOURCES})

# 3. Anchor the include path so #include "dynamics/Rocket.hpp" works
target_include_directories(RAS PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
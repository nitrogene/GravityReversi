cmake_minimum_required(VERSION 3.16)

project(GravityReversi VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

# Include directories
include_directories(src/core src/gui src/agents src/controller)

# Source groups for IDE organization
file(GLOB_RECURSE CORE_SOURCES src/core/*.cpp src/core/*.h)
file(GLOB_RECURSE GUI_SOURCES src/gui/*.cpp src/gui/*.h)
file(GLOB_RECURSE AGENT_SOURCES src/agents/*.cpp src/agents/*.h)
file(GLOB_RECURSE CONTROLLER_SOURCES src/controller/*.cpp src/controller/*.h)

set(SOURCES
    src/main.cpp
    ${CORE_SOURCES}
    ${GUI_SOURCES}
    ${AGENT_SOURCES}
    ${CONTROLLER_SOURCES}
)

add_executable(GravityReversi ${SOURCES})

target_link_libraries(GravityReversi PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets)

# Installation rules (optional for now)
install(TARGETS GravityReversi
    BUNDLE DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

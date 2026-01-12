cmake_minimum_required(VERSION 3.16)

project(GravityReversi VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Hint for Qt6 if not in PATH
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "C:/Qt/6.10.1/mingw_64")

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets Test)

# Include directories
include_directories(src/core src/gui src/agents src/controller)

# Set output directory to bin/ in the source tree
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

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
add_executable(TestBitBoard tests/test_bitboard.cpp src/core/BitBoard.cpp src/core/BitBoard.h)
add_executable(TestRandomAgent tests/test_randomagent.cpp src/agents/RandomAgent.cpp src/core/BitBoard.cpp)
add_executable(TestGreedyAgent tests/test_greedyagent.cpp src/agents/GreedyAgent.cpp src/core/BitBoard.cpp)
add_executable(TestMinimaxAgent tests/test_minimaxagent.cpp src/agents/MinimaxAgent.cpp src/core/BitBoard.cpp)
add_executable(TestRules tests/test_rules.cpp src/core/BitBoard.cpp src/core/BitBoard.h)

target_link_libraries(GravityReversi PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets)
target_link_libraries(TestBitBoard PRIVATE Qt6::Core Qt6::Test)
target_link_libraries(TestRandomAgent PRIVATE Qt6::Core Qt6::Test)
target_link_libraries(TestGreedyAgent PRIVATE Qt6::Core Qt6::Test)
target_link_libraries(TestMinimaxAgent PRIVATE Qt6::Core Qt6::Test)
target_link_libraries(TestRules PRIVATE Qt6::Core Qt6::Test)

# Automatic deployment of Qt dependencies on Windows
if(WIN32)
    find_program(WINDEPLOYQT_EXECUTABLE windeployqt HINTS "C:/Qt/6.10.1/mingw_64/bin")
    if(WINDEPLOYQT_EXECUTABLE)
        add_custom_command(TARGET GravityReversi POST_BUILD
            COMMAND ${WINDEPLOYQT_EXECUTABLE} --no-compiler-runtime --verbose 0 $<TARGET_FILE:GravityReversi>
            COMMENT "Running windeployqt..."
        )
    endif()
endif()

# Installation rules (optional for now)
install(TARGETS GravityReversi
    BUNDLE DESTINATION .
    RUNTIME DESTINATION bin
)

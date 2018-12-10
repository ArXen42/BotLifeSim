cmake_minimum_required(VERSION 3.12)
project(BotLifeSim)

set(CMAKE_CXX_STANDARD 17)

## If you want to link SFML statically
#set(SFML_STATIC_LIBRARIES TRUE)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

add_executable(BotLifeSim main.cpp Model/World.cpp Model/World.hpp Model/Bot.cpp Model/Bot.hpp View/WorldImageVisualizerBase.cpp View/WorldImageVisualizerBase.hpp View/DefaultWorldImageVisualizer.cpp View/DefaultWorldImageVisualizer.hpp Model/CellInfo.hpp Model/CellInfo.cpp Model/BotCommand.hpp Model/Types.hpp Model/CellPosition.cpp Model/CellPosition.hpp)
target_link_libraries(BotLifeSim sfml-graphics sfml-audio)

# Integration with PVS-Studio
include("PVS-Studio.cmake")
pvs_studio_add_target(
        TARGET BotLifeSim.Analyze ALL
        OUTPUT FORMAT errorfile
        PREPROCESSOR clang
        ANALYZE BotLifeSim)
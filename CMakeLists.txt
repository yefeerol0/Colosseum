cmake_minimum_required(VERSION 3.20)

project(Colosseum VERSION 1.0 LANGUAGES CXX)

# C++ STANDARD
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# SOURCE FILES
set(COLOSSEUM_SOURCES
    ${PROJECT_SOURCE_DIR}/ColosseumGame/src/CombatActions.cpp
    ${PROJECT_SOURCE_DIR}/ColosseumGame/src/CombatManager.cpp
    ${PROJECT_SOURCE_DIR}/ColosseumGame/src/ConsoleInterface.cpp
    ${PROJECT_SOURCE_DIR}/ColosseumGame/src/EnemyBehavior.cpp
    ${PROJECT_SOURCE_DIR}/ColosseumGame/src/GameManager.cpp
    ${PROJECT_SOURCE_DIR}/ColosseumGame/src/Gladiator.cpp
    ${PROJECT_SOURCE_DIR}/ColosseumGame/src/GladiatorDataLoader.cpp
    ${PROJECT_SOURCE_DIR}/ColosseumGame/src/main.cpp
    ${PROJECT_SOURCE_DIR}/ColosseumGame/src/PlayerController.cpp
    ${PROJECT_SOURCE_DIR}/ColosseumGame/src/RandomGenerator.cpp
    ${PROJECT_SOURCE_DIR}/ColosseumGame/src/UpgradeSystem.cpp
)

add_executable(Colosseum ${COLOSSEUM_SOURCES})

# HEADER DIRECTORIES
target_include_directories(Colosseum PRIVATE
    ${PROJECT_SOURCE_DIR}/ColosseumGame/includes
    ${PROJECT_SOURCE_DIR}/ColosseumGame/libs
)

add_custom_command(TARGET Colosseum POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${PROJECT_SOURCE_DIR}/ColosseumGame/data/Enemies.json"
            "$<TARGET_FILE_DIR:Colosseum>"
)
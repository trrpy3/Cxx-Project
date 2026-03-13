cmake_minimum_required(VERSION 3.14)
project(GameTests)
set(CMAKE_CXX_STANDARD 17)
if(MSVC)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
endif()
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
cmake_policy(SET CMP0135 NEW)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
FetchContent_MakeAvailable(googletest)

if(MSVC)
    # Для каждого таргета Google Test устанавливаем флаги
    set_target_properties(gtest PROPERTIES
        COMPILE_FLAGS "/MTd"
        INTERFACE_COMPILE_FLAGS "/MTd"
    )
    set_target_properties(gtest_main PROPERTIES
        COMPILE_FLAGS "/MTd"
        INTERFACE_COMPILE_FLAGS "/MTd"
    )
    set_target_properties(gmock PROPERTIES
        COMPILE_FLAGS "/MTd"
        INTERFACE_COMPILE_FLAGS "/MTd"
    )
    set_target_properties(gmock_main PROPERTIES
        COMPILE_FLAGS "/MTd"
        INTERFACE_COMPILE_FLAGS "/MTd"
    )
endif()

set(PROJECT_ROOT "${CMAKE_SOURCE_DIR}/..")
message(STATUS "Project root: ${PROJECT_ROOT}")

include_directories(
    ${PROJECT_ROOT}/src
    ${PROJECT_ROOT}/src/entities
    ${PROJECT_ROOT}/src/core
    ${PROJECT_ROOT}/src/items
    ${PROJECT_ROOT}/src/items/armor
    ${PROJECT_ROOT}/src/items/weapon
    ${PROJECT_ROOT}/src/items/consumables
)

set(GAME_SOURCES
    ${CMAKE_SOURCE_DIR}/../src/entities/entity.cpp
    ${CMAKE_SOURCE_DIR}/../src/entities/player.cpp
    ${CMAKE_SOURCE_DIR}/../src/entities/enemy.cpp
    ${CMAKE_SOURCE_DIR}/../src/entities/npc.cpp
    ${CMAKE_SOURCE_DIR}/../src/core/battle.cpp
    ${CMAKE_SOURCE_DIR}/../src/core/location.cpp
    ${CMAKE_SOURCE_DIR}/../src/core/forest.cpp
    ${CMAKE_SOURCE_DIR}/../src/core/swamp.cpp
    ${CMAKE_SOURCE_DIR}/../src/core/mountain.cpp
    ${CMAKE_SOURCE_DIR}/../src/core/town.cpp
    ${CMAKE_SOURCE_DIR}/../src/items/armor/armor.cpp
    ${CMAKE_SOURCE_DIR}/../src/items/weapon/weapon.cpp
    ${CMAKE_SOURCE_DIR}/../src/items/consumables/healthpotion.cpp
    ${CMAKE_SOURCE_DIR}/../src/items/consumables/stuff.cpp
    ${CMAKE_SOURCE_DIR}/../src/items/consumables/effect.cpp
    ${CMAKE_SOURCE_DIR}/../src/core/input.cpp
    ${CMAKE_SOURCE_DIR}/../src/core/save_load.cpp
    ${CMAKE_SOURCE_DIR}/../src/core/enums.h
)

add_library(game_lib STATIC ${GAME_SOURCES})

if(MSVC)
    set_target_properties(game_lib PROPERTIES
        COMPILE_FLAGS "/MTd"
    )
endif()

add_executable(game_tests
    test_main.cpp
    test_entity.cpp
    test_player.cpp
    test_combat.cpp
    test_inventory.cpp
    test_items.cpp
    test_locations.cpp
)

if(MSVC)
    set_target_properties(game_tests PROPERTIES
        COMPILE_FLAGS "/MTd"
    )
endif()

target_link_libraries(game_tests
    game_lib
    GTest::gtest
    GTest::gtest_main
    GTest::gmock
    GTest::gmock_main
)

include(GoogleTest)
gtest_discover_tests(game_tests)
cmake_minimum_required(VERSION 3.20)
set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")
project(UndertaleLikeGame)


set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
        ${CMAKE_SOURCE_DIR}/src/items/weapon/weapon.cpp
        ${CMAKE_SOURCE_DIR}/src/items/armor/armor.cpp
        ${CMAKE_SOURCE_DIR}/src/items/consumables/stuff.cpp
        ${CMAKE_SOURCE_DIR}/src/items/consumables/healthpotion.cpp
        ${CMAKE_SOURCE_DIR}/src/items/consumables/effect.cpp 
        ${CMAKE_SOURCE_DIR}/src/entities/entity.cpp
        ${CMAKE_SOURCE_DIR}/src/entities/player.cpp
        ${CMAKE_SOURCE_DIR}/src/entities/npc.cpp
        ${CMAKE_SOURCE_DIR}/src/entities/enemy.cpp
        ${CMAKE_SOURCE_DIR}/src/core/location.cpp
        ${CMAKE_SOURCE_DIR}/src/core/world.cpp
        ${CMAKE_SOURCE_DIR}/src/core/town.cpp
        ${CMAKE_SOURCE_DIR}/src/core/forest.cpp
        ${CMAKE_SOURCE_DIR}/src/core/swamp.cpp
        ${CMAKE_SOURCE_DIR}/src/core/mountain.cpp
        ${CMAKE_SOURCE_DIR}/src/core/cave.cpp
        ${CMAKE_SOURCE_DIR}/src/core/shop.cpp
        ${CMAKE_SOURCE_DIR}/src/core/battle.cpp
        ${CMAKE_SOURCE_DIR}/src/core/input.cpp
        ${CMAKE_SOURCE_DIR}/src/core/save_load.cpp
)

set(HEADERS
        ${CMAKE_SOURCE_DIR}/src/core/enums.h
        ${CMAKE_SOURCE_DIR}/src/items/consumables/effect.h
        ${CMAKE_SOURCE_DIR}/src/core/save_load.h
        ${CMAKE_SOURCE_DIR}/src/items/consumables/stuff.h
        ${CMAKE_SOURCE_DIR}/src/items/consumables/healthpotion.h
        ${CMAKE_SOURCE_DIR}/src/items/weapon/weapon.h
        ${CMAKE_SOURCE_DIR}/src/items/armor/armor.h
        ${CMAKE_SOURCE_DIR}/src/entities/entity.h
        ${CMAKE_SOURCE_DIR}/src/entities/player.h
        ${CMAKE_SOURCE_DIR}/src/entities/enemy.h
        ${CMAKE_SOURCE_DIR}/src/entities/npc.h
        ${CMAKE_SOURCE_DIR}/src/core/location.h
        ${CMAKE_SOURCE_DIR}/src/core/world.h
        ${CMAKE_SOURCE_DIR}/src/core/town.h
        ${CMAKE_SOURCE_DIR}/src/core/forest.h
        ${CMAKE_SOURCE_DIR}/src/core/swamp.h
        ${CMAKE_SOURCE_DIR}/src/core/mountain.h
        ${CMAKE_SOURCE_DIR}/src/core/cave.h
        ${CMAKE_SOURCE_DIR}/src/core/shop.h
        ${CMAKE_SOURCE_DIR}/src/core/battle.h
        ${CMAKE_SOURCE_DIR}/src/core/input.h
        ${CMAKE_SOURCE_DIR}/src/core/exceptions.h
        ${CMAKE_SOURCE_DIR}/src/core/user_interface.h
)

add_library(game_lib ${SOURCES} ${HEADERS})
target_include_directories(game_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(game ${CMAKE_SOURCE_DIR}/src/main.cpp)
target_link_libraries(game game_lib)
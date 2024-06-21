cmake_minimum_required(VERSION 3.5.0)
project(gamelib VERSION 2.0.0)

set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(lib/raylib)

add_library(gamelib source/objects/debugconsole.cpp source/objects/console.cpp source/objects/commandproc.cpp source/physics/collider.cpp source/core/tilemap.cpp source/graphics/dynamicmesh.cpp source/graphics/transitions/squaretransition.cpp source/graphics/transitions/iristransition.cpp source/graphics/textureatlas.cpp source/graphics/animatedsprite.cpp source/core/object.cpp source/core/position.cpp source/graphics/renderqueue.cpp source/graphics/renderqueuesortedz.cpp source/graphics/transitions/fadetransition.cpp source/graphics/renderqueuesorted2d.cpp source/graphics/texturecache.cpp source/graphics/sprite.cpp source/core/programstack.cpp source/core/program.cpp source/core/behaviour.cpp source/behaviours/playermovement.cpp source/core/input.cpp source/behaviours/movement.cpp source/utils.cpp)

add_executable(testapp source/demos/test.cpp)

add_executable(datapack source/tools/datapack.cpp)

add_executable(tilemapedit source/tools/tilemapedit.cpp)

add_executable(village source/games/village/village.cpp)

add_executable(arpg source/games/arpg/arpg.cpp)

find_library(MATH_LIBRARY m)
if(MATH_LIBRARY)
    target_link_libraries(gamelib ${MATH_LIBRARY})
endif()

target_link_libraries(gamelib raylib)
target_link_libraries(testapp gamelib)
target_link_libraries(datapack gamelib)
target_link_libraries(tilemapedit gamelib)
target_link_libraries(village gamelib)
target_link_libraries(arpg gamelib)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/external/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/external/include/hlslpp)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/data)


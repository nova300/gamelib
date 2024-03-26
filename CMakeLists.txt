cmake_minimum_required(VERSION 3.5.0)
project(gamelib VERSION 2.0.0)

set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(lib/raylib)

add_library(gamelib source/core/object.cpp source/core/position.cpp source/graphics/renderqueue.cpp source/graphics/texturecache.cpp source/graphics/sprite.cpp source/core/programstack.cpp source/core/program.cpp source/core/objectstore.cpp source/core/behaviour.cpp source/behaviours/playermovement.cpp source/graphics/lights.cpp)

add_executable(testapp source/games/test.cpp)

find_library(MATH_LIBRARY m)
if(MATH_LIBRARY)
    target_link_libraries(application ${MATH_LIBRARY})
endif()

target_link_libraries(gamelib raylib)
target_link_libraries(testapp gamelib)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/external/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/external/include/hlslpp)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/data)


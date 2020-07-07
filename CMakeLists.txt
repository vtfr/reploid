cmake_minimum_required(VERSION 3.10)
project(megaman VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# LodePNG
add_library(lodepng
    vendor/lodepng/lodepng.cpp
    vendor/lodepng/lodepng.h)

include_directories(src/**)
add_executable(megaman src/main.cc)
target_sources(megaman
    PRIVATE 
        ${CMAKE_CURRENT_LIST_DIR}/src/graphics/image.cc
        ${CMAKE_CURRENT_LIST_DIR}/src/graphics/loader.cc
        ${CMAKE_CURRENT_LIST_DIR}/src/routing/map.cc
        ${CMAKE_CURRENT_LIST_DIR}/src/routing/a_star_router.cc
        ${CMAKE_CURRENT_LIST_DIR}/src/math/distance.cc
)
target_link_libraries(megaman lodepng)
target_include_directories(megaman PUBLIC vendor)
target_include_directories(megaman PUBLIC src)


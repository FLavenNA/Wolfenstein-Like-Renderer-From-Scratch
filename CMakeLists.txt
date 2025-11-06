cmake_minimum_required(VERSION 3.16)
project(Wolfenstein-Like-Renderer)

# Set the C standard
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_definitions(DEBUG)
endif()

include_directories(include)

add_subdirectory(libs/SDL EXCLUDE_FROM_ALL)
add_subdirectory(libs/SDL_ttf EXCLUDE_FROM_ALL)

# Collect all .c files in src/
file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS 
    "${CMAKE_SOURCE_DIR}/src/*.c"
    "${CMAKE_SOURCE_DIR}/src/core/*.c"
    "${CMAKE_SOURCE_DIR}/src/render/*.c"
    "${CMAKE_SOURCE_DIR}/src/utils/*.c")

add_executable(Wolfenstein-Like-Renderer ${SRC_FILES})

target_include_directories(Wolfenstein-Like-Renderer PRIVATE
                         ${CMAKE_SOURCE_DIR}/include
                         ${CMAKE_SOURCE_DIR}/include/core
                         ${CMAKE_SOURCE_DIR}/include/render
                         ${CMAKE_SOURCE_DIR}/include/utils)

target_link_libraries(Wolfenstein-Like-Renderer 
    PRIVATE
    SDL3::SDL3
    SDL3_ttf::SDL3_ttf)

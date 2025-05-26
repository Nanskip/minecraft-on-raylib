cmake_minimum_required(VERSION 3.11)
project(Minecraft VERSION 1.0.0 LANGUAGES C)

# Set C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Set Raylib paths
set(RAYLIB_PATH "${CMAKE_SOURCE_DIR}/raylib-5.5_win64_mingw-w64")
set(RAYLIB_INCLUDE_PATH "${RAYLIB_PATH}/include")
set(RAYLIB_LIB_PATH "${RAYLIB_PATH}/lib")

# Add include directories (Raylib + Perlin)
include_directories(
    ${RAYLIB_INCLUDE_PATH}
    ${CMAKE_SOURCE_DIR}/libraries
)

# Add executable with both main and perlin source files
add_executable(${PROJECT_NAME}
    src/main.c
    libraries/perlin.c
)

# Link Raylib and required Windows libraries
target_link_libraries(${PROJECT_NAME} PRIVATE 
    ${RAYLIB_LIB_PATH}/libraylib.a
    winmm
)

# Copy resources to build directory
file(COPY ${CMAKE_SOURCE_DIR}/resources DESTINATION ${CMAKE_BINARY_DIR})

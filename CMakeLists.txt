cmake_minimum_required(VERSION 2.8.7)
project(blackjack C)

# Force C99 mode for all targets
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# If your old CMake doesn’t fully respect the above, force flags manually too:
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")
set(CMAKE_C_STANDARD 99)
add_definitions(-D_POSIX_C_SOURCE=199309L)
add_definitions(-D_XOPEN_SOURCE=700)

include_directories(
    include
    lib
    dependencies
    dependencies/hwlib_stub
)

file(GLOB SRC_FILES
     src/*.c
     src/*/*.c
)

file(GLOB DEP_FILES
     dependencies/*.c
)

add_executable(blackjack
    ${SRC_FILES}
    ${DEP_FILES}
)

target_link_libraries(blackjack rt)



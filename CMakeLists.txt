cmake_minimum_required(VERSION 3.12)
project(minesweeper)

# Add your source files
set(SOURCES
    src/main.cpp
)

# Create the executable
add_executable(minesweeper ${SOURCES})
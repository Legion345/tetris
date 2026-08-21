cmake_minimum_required(VERSION 3.5.2)
project(Tetris LANGUAGES C)

set(CURSES_NEED_NCURSES TRUE)
find_package(Curses REQUIRED)

add_executable(tetris src/main.c src/tetris.c src/util.c)
target_include_directories(tetris PRIVATE ${CURSES_INCLUDE_DIRS})
target_link_libraries(tetris PRIVATE ${CURSES_LIBRARIES})

message(STATUS "Tetris the Game")

cmake_minimum_required(VERSION 3.23)

project(MiniGemPuzzle)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

file(GLOB_RECURSE SRC_FILES *.cpp *.h)

add_executable(MiniGemPuzzle WIN32 ${SRC_FILES})

#Зависимости
find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIR})
target_link_libraries(MiniGemPuzzle ${SDL2_LIBRARY})
target_link_libraries(MiniGemPuzzle ${SDL2MAIN_LIBRARY})

#Перенос ассетов

add_custom_command(TARGET MiniGemPuzzle PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E remove_directory 
                       $<TARGET_FILE_DIR:MiniGemPuzzle>/Levels)

add_custom_command(TARGET MiniGemPuzzle PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/assets/Levels $<TARGET_FILE_DIR:MiniGemPuzzle>/Levels)
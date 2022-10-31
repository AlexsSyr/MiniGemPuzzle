cmake_minimum_required(VERSION 3.23)

project(MiniGemPuzzle)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

file(GLOB_RECURSE SRC_FILES *.cpp *.h)

add_executable(MiniGemPuzzle WIN32 ${SRC_FILES})

#Зависимости
#SDL2
find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIR})
target_link_libraries(MiniGemPuzzle ${SDL2_LIBRARY})
target_link_libraries(MiniGemPuzzle ${SDL2MAIN_LIBRARY})

#FreeImage
set(FREE_IMAGE_DIR UNDEFINED CACHE PATH "Path to FreeImage dir.")
include_directories(${FREE_IMAGE_DIR})


 target_link_libraries(MiniGemPuzzle ${FREE_IMAGE_DIR}/FreeImage.lib)


#Перенос ассетов
#Уровни
add_custom_command(TARGET MiniGemPuzzle PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E remove_directory 
                       $<TARGET_FILE_DIR:MiniGemPuzzle>/Levels)

add_custom_command(TARGET MiniGemPuzzle PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/assets/Levels $<TARGET_FILE_DIR:MiniGemPuzzle>/Levels)

#Текстуры
add_custom_command(TARGET MiniGemPuzzle PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E remove_directory 
                       $<TARGET_FILE_DIR:MiniGemPuzzle>/Images)

add_custom_command(TARGET MiniGemPuzzle PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/assets/Images $<TARGET_FILE_DIR:MiniGemPuzzle>/Images)


add_custom_command(TARGET MiniGemPuzzle PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy
                       ${FREE_IMAGE_DIR}/FreeImage.dll $<TARGET_FILE_DIR:MiniGemPuzzle>)

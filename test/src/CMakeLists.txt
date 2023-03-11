cmake_minimum_required(VERSION 3.0)
set(CMAKE_CXX_STANDARD 20)
project(test_project)

add_subdirectory("${PROJECT_SOURCE_DIR}/../.." "${CMAKE_CURRENT_BINARY_DIR}/audio")
add_executable(${PROJECT_NAME} "test.cpp")
target_link_libraries(${PROJECT_NAME} audio)

####Copy resources folder to target solution directory.
add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/../res $<TARGET_FILE_DIR:${PROJECT_NAME}>/res)
if(WIN32)
    add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/../res $<TARGET_FILE_DIR:${PROJECT_NAME}>/../res)
endif(WIN32)
#####
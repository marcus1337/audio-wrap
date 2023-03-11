cmake_minimum_required(VERSION 3.10)
project(audio_wrap)
set(CMAKE_CXX_STANDARD 20)

add_library(${PROJECT_NAME} STATIC 
"src/null.cpp"
)

target_include_directories(${PROJECT_NAME}
  PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> 
)

target_link_libraries(${PROJECT_NAME})


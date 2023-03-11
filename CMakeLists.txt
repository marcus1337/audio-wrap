cmake_minimum_required(VERSION 3.10)
project(audio)
set(CMAKE_CXX_STANDARD 20)

set(loud_dir "audio/soloud")

file(GLOB soloud_SRC
     "${loud_dir}/*.h"
     "${loud_dir}/*.cpp"
	 "${loud_dir}/audiosource/speech/*.h"
     "${loud_dir}/audiosource/speech/*.cpp"
	 "${loud_dir}/audiosource/wav/*.h"
     "${loud_dir}/audiosource/wav/*.cpp"
	 "${loud_dir}/audiosource/wav/*.c"
	 "${loud_dir}/filter/*.h"
     "${loud_dir}/filter/*.cpp"
)

add_library(${PROJECT_NAME} STATIC 
"audio/Audio.h" "audio/Audio.cpp" ${soloud_SRC} "audio/SoloudAudio.h" "audio/SoloudAudio.cpp"
)

target_include_directories(${PROJECT_NAME}
  PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> 
)

target_link_libraries(${PROJECT_NAME})


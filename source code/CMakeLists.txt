cmake_minimum_required(VERSION 3.24)
project(ji)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXE_LINKER_FLAGS "-static")
add_executable(ji main.cpp)
#链接`__imp_PlaySoundA'
target_link_libraries(ji winmm.lib)


add_executable(main main.cpp)
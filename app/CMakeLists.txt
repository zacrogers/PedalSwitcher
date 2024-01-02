cmake_minimum_required(VERSION 3.20.0)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
find_package(etl REQUIRED)
FILE(GLOB app_sources src/*.cpp)
# target_compile_options(app PRIVATE -DLUA_32BITS -DLUA_C89_NUMBERS)
target_sources(app PRIVATE ${app_sources})
project(pedal_switcher)

target_link_libraries(app PRIVATE etl::etl)
target_sources(app PRIVATE src/main.cpp)
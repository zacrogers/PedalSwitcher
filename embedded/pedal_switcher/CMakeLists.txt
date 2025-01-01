cmake_minimum_required(VERSION 3.20.0)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
find_package(etl REQUIRED)
FILE(GLOB app_sources src/*.cpp)
# target_compile_options(app PRIVATE -DLUA_32BITS -DLUA_C89_NUMBERS)
target_sources(app PRIVATE ${app_sources})
target_sources(app PRIVATE src/subsystems/display.cpp)
target_sources(app PRIVATE src/subsystems/graphics.cpp)
target_sources(app PRIVATE src/states/page/main_menu.cpp)
project(gb_emu)


if(CONFIG_VROOM_ENABLE_GAMES)
    target_sources(app PRIVATE src/states/game/pong.cpp)
    # target_sources(app PRIVATE src/states/game/snake.cpp)
    # target_sources(app PRIVATE src/states/game/sudoku.cpp)
endif()


if(CONFIG_USE_PHYSICAL_CONTROLS)
    target_sources(app PRIVATE src/subsystems/controls.cpp)
elseif(CONFIG_USE_BT_CONTROLLER)
endif()


# if(CONFIG_VROOM_ENABLE_UTILITIES)
#     if(CONFIG_VROOM_ENABLE_WIFI)
#         target_sources(app PRIVATE src/connectivity/wifi.cpp)
#         target_sources(app PRIVATE src/states/page/wifi_page.cpp)
#     endif()

#     if(CONFIG_VROOM_ENABLE_BT)
#         target_sources(app PRIVATE src/connectivity/bt.cpp)
#     endif()

#     # if(CONFIG_BATTMAN_SEND_BATT_SIGNAL)
#     #     target_sources(app PRIVATE src/subsystems/battman.cpp)
#     # endif()
# endif()

zephyr_include_directories(../deps/modules/etl)

# if(CONFIG_LUA)
#     zephyr_include_directories(../modules/lua)
# endif()


target_link_libraries(app PRIVATE etl::etl)
target_sources(app PRIVATE src/main.cpp)

# if(CONFIG_VROOM_ENABLE_GB_EMULATOR)
#     include_directories(
#         ../emu_core/inc
#         ../emu_core/src
#     )
#     target_sources(app PRIVATE
#         ../emu_core/src/cpu.cpp
#         ../emu_core/src/registers.cpp
#         ../emu_core/src/process.cpp
#         ../emu_core/src/instructions.cpp
#         ../emu_core/src/cart.cpp
#     )
# endif()



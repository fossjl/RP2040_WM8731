add_library(RP2040_WM8731 INTERFACE)
target_sources(RP2040_WM8731 INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/src/wm8731.c
)
target_include_directories(RP2040_WM8731 INTERFACE
    src
    include
)
target_link_libraries(RP2040_WM8731 INTERFACE
    pico_stdlib 
    hardware_i2c
    pico_audio_i2s
)
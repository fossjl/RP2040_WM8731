add_library(RP2040_WM8731 INTERFACE)
target_sources(RP2040_WM8731 INTERFACE
${CMAKE_CURRENT_LIST_DIR}/src/wm8731.c
${CMAKE_CURRENT_LIST_DIR}/src/data/LineInConfig.c
${CMAKE_CURRENT_LIST_DIR}/src/data/HeadphoneOutConfig.c
${CMAKE_CURRENT_LIST_DIR}/src/data/AnalogPathControl.c
${CMAKE_CURRENT_LIST_DIR}/src/data/DigitalAudioInterfaceFormat.c
${CMAKE_CURRENT_LIST_DIR}/src/data/DigitalPathControl.c
${CMAKE_CURRENT_LIST_DIR}/src/data/HeadphoneOutConfig.c
${CMAKE_CURRENT_LIST_DIR}/src/data/LineInConfig.c
${CMAKE_CURRENT_LIST_DIR}/src/data/PowerDownControl.c
${CMAKE_CURRENT_LIST_DIR}/src/data/SamplingControl.c
)
target_include_directories(RP2040_WM8731 INTERFACE
    src
    src/data
    include
)
target_link_libraries(RP2040_WM8731 INTERFACE
    pico_stdlib 
    hardware_i2c
    pico_audio_i2s
)
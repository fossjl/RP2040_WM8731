add_library(RP2040_WM8731 INTERFACE)
target_sources(RP2040_WM8731 INTERFACE
${CMAKE_CURRENT_LIST_DIR}/src/wm8731.c
${CMAKE_CURRENT_LIST_DIR}/src/api/LineInConfig.c
${CMAKE_CURRENT_LIST_DIR}/src/api/HeadphoneOutConfig.c
${CMAKE_CURRENT_LIST_DIR}/src/api/AnalogPathControl.c
${CMAKE_CURRENT_LIST_DIR}/src/api/DigitalAudioInterfaceFormat.c
${CMAKE_CURRENT_LIST_DIR}/src/api/DigitalPathControl.c
${CMAKE_CURRENT_LIST_DIR}/src/api/HeadphoneOutConfig.c
${CMAKE_CURRENT_LIST_DIR}/src/api/LineInConfig.c
${CMAKE_CURRENT_LIST_DIR}/src/api/PowerDownControl.c
${CMAKE_CURRENT_LIST_DIR}/src/api/SamplingControl.c
)
target_include_directories(RP2040_WM8731 INTERFACE
    src
    src/api
    include
)
target_link_libraries(RP2040_WM8731 INTERFACE
    pico_stdlib 
    hardware_i2c
)
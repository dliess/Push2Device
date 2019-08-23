cmake_minimum_required(VERSION 2.8.12)

set (CMAKE_CXX_STANDARD 17)

add_subdirectory(Topology)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_LIST_DIR}")
find_package(libusb-1.0 REQUIRED)

add_library(Push2Device STATIC
    "Push2Device.cpp"
    "Push2DisplayRenderer.cpp"
    "Push2UsbDisplay.cpp"
    "Push2LedColorMap.cpp"
    "Push2Midi1InputCallback.cpp"
)

target_include_directories(Push2Device PUBLIC ${CMAKE_CURRENT_LIST_DIR})

target_link_libraries(Push2Device PUBLIC
    Push2DeviceTopology
    usbMidiPortHandling
    midi
    FpBase
    FpGfx
    FpDisplay
    LIBUSB1::LIBUSB1
)
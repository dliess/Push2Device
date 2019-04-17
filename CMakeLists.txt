cmake_minimum_required(VERSION 2.8.12)

set (CMAKE_CXX_STANDARD 11)

set(TOPOLOGY_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(TOPOLOGY_GENERATED_HEADER "${TOPOLOGY_DIR}/Push2Topology.h")
set(TOPOLOGY_SOURCE_JSON "${TOPOLOGY_DIR}/Push2Topology.json")

#message( "TOPOLOGY_CODE_GEN_TOOL: "${TOPOLOGY_CODE_GEN_TOOL} )

add_custom_command(
    OUTPUT ${TOPOLOGY_GENERATED_HEADER}
    COMMAND python ${TOPOLOGY_CODE_GEN_TOOL} ${TOPOLOGY_SOURCE_JSON}
    WORKING_DIRECTORY ${TOPOLOGY_DIR}
    COMMENT "Generating Widget-Topology header"
    DEPENDS ${TOPOLOGY_SOURCE_JSON})

add_custom_target(generateTopologyHeader DEPENDS "${TOPOLOGY_GENERATED_HEADER}" "${TOPOLOGY_CODE_GEN_TOOL}")


set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_LIST_DIR}")
find_package(libusb-1.0 REQUIRED)

add_library(Push2Device STATIC
    "Push2Device.cpp"
    "Push2DeviceCompl.cpp"
    "Push2DisplayRenderer.cpp"
    "Push2UsbDisplay.cpp"
    "Push2LedColorMap.cpp"
    "Push2Midi1InputCallback.cpp"
)
#add_dependencies(Push2Device generateTopologyHeader)

target_include_directories(Push2Device PUBLIC ${CMAKE_CURRENT_LIST_DIR})

target_link_libraries(Push2Device PUBLIC
    usbMidiPortHandling
    midi
    FpBase
    FpGfx
    FpDisplay
    LIBUSB1::LIBUSB1
)
cmake_minimum_required(VERSION 2.8.12)

project(Push2Device)

set (CMAKE_CXX_STANDARD 17)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include(cmake/CPM.cmake)

CPMFindPackage(
  NAME Midi
  GITHUB_REPOSITORY dliess/Midi
  GIT_TAG 284372a58ad8b7823100ff493cb4feba16e695d5
)

CPMFindPackage(
  NAME FrontPanelIO
  GITHUB_REPOSITORY dliess/FrontPanelIO
  GIT_TAG 6eb64575d8f3798c5f28d47d8708baa8893584b7
)

CPMAddPackage(
  NAME timemeasure
  GITHUB_REPOSITORY dliess/TimeMeasure
  GIT_TAG develop
)

add_subdirectory(Topology)
add_subdirectory(Test EXCLUDE_FROM_ALL)

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

target_link_libraries(Push2Device
  PUBLIC Push2DeviceTopology
  PUBLIC usbMidiPortHandling
  PUBLIC midi
  PUBLIC FpBase
  PUBLIC FpGfx
  PUBLIC FpDisplay
  PUBLIC LIBUSB1::LIBUSB1
  PRIVATE TimeMeasure
)

option(__WITH_QT_ADAPTER__ "add qt adapter" ON)
if(${__WITH_QT_ADAPTER__})
  add_subdirectory(Qt)
endif()
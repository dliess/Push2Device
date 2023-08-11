cmake_minimum_required(VERSION 3.11)

project(Push2Device
        VERSION 0.0.1
        LANGUAGES CXX)

set (CMAKE_CXX_STANDARD 17)

include(GNUInstallDirs)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include(cmake/CPM.cmake)

option (USE_MPARK_VARIANT "use mpark variant" ON)

CPMFindPackage(
  NAME midi
  GITHUB_REPOSITORY dliess/Midi
  GIT_TAG master
  OPTIONS
    "USE_MPARK_VARIANT ${USE_MPARK_VARIANT}"
)
if(midi_ADDED)
  add_library(MIDI::midi ALIAS midi)
  add_library(MIDI::usbmidi ALIAS usbmidi)
  add_library(MIDI::usbMidiPortHandling ALIAS usbMidiPortHandling)
endif()

CPMFindPackage(
  NAME FrontPanelIO
  GITHUB_REPOSITORY dliess/FrontPanelIO
  GIT_TAG master
)
if(FrontPanelIO_ADDED)
  add_library(FrontPanelIO::FpBase ALIAS FpBase)
  add_library(FrontPanelIO::FpGfx ALIAS FpGfx)
  add_library(FrontPanelIO::FpDisplay ALIAS FpDisplay)
endif()

#CPMAddPackage(
#  NAME TimeMeasure
#  GITHUB_REPOSITORY dliess/TimeMeasure
#  GIT_TAG develop
#)
#if(TimeMeasure_ADDED)
#  add_library(TimeMeasure::TimeMeasure ALIAS TimeMeasure)
#endif()

add_subdirectory(Topology)
add_subdirectory(Test EXCLUDE_FROM_ALL)

find_package(libusb-1.0 REQUIRED)

set(TARGET_NAME ${PROJECT_NAME})

set(SOURCES
  "Push2Device.cpp"
  "Push2DisplayRenderer.cpp"
  "Push2UsbDisplay.cpp"
  "Push2LedColorMap.cpp"
  "Push2Midi1InputCallback.cpp"
)

set(PUBLIC_HEADERS
  "Interface/Push2Device.h"
  "Interface/Push2LedColorMap.h"
)

set(HEADERS
  ${PUBLIC_HEADERS}
  "Push2DisplayRenderer.h"
  "Push2Midi1InputCallback.h"
  "Push2UsbDisplay.h"
)

add_library(${TARGET_NAME} STATIC ${SOURCES} ${HEADERS})

target_include_directories(${TARGET_NAME} 
  PRIVATE "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
  PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Interface>"
  PUBLIC "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}>"
)

target_link_libraries(${TARGET_NAME}
  PUBLIC Push2DeviceTopology
  PRIVATE MIDI::usbmidi
  PRIVATE MIDI::usbMidiPortHandling
  PUBLIC MIDI::midi
  PUBLIC FrontPanelIO::FpBase
  PUBLIC FrontPanelIO::FpGfx
  PUBLIC FrontPanelIO::FpDisplay
  PRIVATE LIBUSB1::LIBUSB1
  #PRIVATE TimeMeasure::TimeMeasure
)

set(FIND_QT_DEPENDENCIES "")
option(__WITH_QT_ADAPTER__ "add qt adapter" ON)
if(${__WITH_QT_ADAPTER__})
  add_subdirectory(Qt)
  set(FIND_QT_DEPENDENCIES "find_dependency(Qt5 5.11.3 COMPONENTS Core REQUIRED)")
endif()


set_target_properties(${TARGET_NAME} PROPERTIES
    PUBLIC_HEADER "${PUBLIC_HEADERS}"
)

install(TARGETS ${TARGET_NAME}  EXPORT ${PROJECT_NAME}-targets
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}
)

install(EXPORT ${PROJECT_NAME}-targets
  NAMESPACE  ${PROJECT_NAME}::
  DESTINATION  "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}"
)

configure_file(cmake/${PROJECT_NAME}Config.cmake.in cmake/${PROJECT_NAME}Config.cmake @ONLY)

include(CMakePackageConfigHelpers)
write_basic_package_version_file("${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config-version.cmake" COMPATIBILITY SameMajorVersion)
install(FILES 
           "${CMAKE_CURRENT_BINARY_DIR}/cmake/${PROJECT_NAME}Config.cmake"
           "${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config-version.cmake" 
        DESTINATION 
           "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}")
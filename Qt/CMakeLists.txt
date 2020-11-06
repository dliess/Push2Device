set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 5.14.2 COMPONENTS Core Gui REQUIRED)

set(SOURCES
    "Push2DeviceOverlay.cpp"
    "Push2DeviceQtAdapter.cpp"
)

set(HEADERS
    "Push2DeviceOverlay.h"
    "Push2DeviceQtAdapter.h"
)

add_library(Push2DeviceQt STATIC ${SOURCES} ${HEADERS})

target_include_directories(Push2DeviceQt PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(Push2DeviceQt
  PUBLIC Qt5::Core
  PUBLIC Qt5::Gui
  PUBLIC Push2Device
)

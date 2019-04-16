find_path(LIBUSB_1_INCLUDE_DIR
  NAMES
    libusb.h
  PATHS
    /usr/include
    /usr/local/include
  PATH_SUFFIXES
    libusb-1.0
)

find_library(LIBUSB_1_LIBRARY
NAMES
  usb-1.0 usb
PATHS
  /usr/lib
  /usr/local/lib
)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(libusb-1.0 DEFAULT_MSG LIBUSB_1_LIBRARY LIBUSB_1_INCLUDE_DIR)
mark_as_advanced(LIBUSB_1_INCLUDE_DIR LIBUSB_1_LIBRARY)
if(LIBUSB_1_LIBRARY)
  message(STATUS "#### ${LIBUSB_1_LIBRARY}")
  add_library(LIBUSB1::LIBUSB1 UNKNOWN IMPORTED)
  set_target_properties(LIBUSB1::LIBUSB1 PROPERTIES
    IMPORTED_LOCATION "${LIBUSB_1_LIBRARY}"
    INTERFACE_INCLUDE_DIRECTORIES "${LIBUSB_1_INCLUDE_DIR}")
endif()
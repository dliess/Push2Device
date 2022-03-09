add_executable(Push2DeviceTest
    "main.cpp"
)

target_link_libraries(Push2DeviceTest
  PRIVATE Push2Device
  PRIVATE MIDI::usbMidiPortHandling
)
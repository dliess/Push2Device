cmake_minimum_required(VERSION 2.8.12)

add_executable(Push2DeviceTest
    "main.cpp"
)

target_link_libraries(Push2DeviceTest
  Push2Device
)
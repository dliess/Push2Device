#!/bin/bash 

source /opt/sdk/nomidi/1.0.0.0/environment-setup-cortexa53-poky-linux
cmake -DCMAKE_TOOLCHAIN_FILE=/opt/sdk/nomidi/1.0.0.0/sysroots/x86_64-pokysdk-linux/usr/share/cmake/OEToolchainConfig.cmake \
      -DCPM_LOCAL_PACKAGES_ONLY=ON \
      -D__WITH_QT_ADAPTER__=ON \
      ..
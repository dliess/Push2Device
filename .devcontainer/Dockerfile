FROM debian:bullseye

# Users and passwords
ARG BUILD_USER=build-user
ARG UID=1000
ARG GID=1000
ARG BUILD_USER_PWD=pwd

RUN rm -rf /var/lib/apt/lists/*

# Generate and set locale
RUN apt-get update \
    && DEBIAN_FRONTEND=noninteractive apt-get install -y locales \
    && sed -i -e 's/# en_US.UTF-8 UTF-8/en_US.UTF-8 UTF-8/' /etc/locale.gen \
    && dpkg-reconfigure --frontend=noninteractive locales

RUN locale-gen --purge en_US.UTF-8
RUN update-locale LC_ALL=en_US.UTF-8 LANG=en_US.UTF-8
ENV LC_ALL en_US.UTF-8
ENV LANG en_US.UTF-8
ENV LANGUAGE en_US.UTF-8

# Package installs
RUN apt-get update && apt-get install -y \
	sudo \
        cmake \
        clang-format \
        ninja-build \
        g++ \
        gdb \
        git \
        libasound2-dev \
        libgtest-dev \
        libusb-1.0-0-dev \
        python \
        && rm -rf /var/lib/apt/lists/*

# install Qt build dependencies
RUN apt-get update && apt-get install -y \
        qtbase5-dev \
        qtdeclarative5-dev \
        && rm -rf /var/lib/apt/lists/*

# some utilities for runtime
RUN apt-get update && apt-get install -y \
        vim \
        libzmq3-dev \
        feedgnuplot \
        netcat \
        zsh \
        curl \
        && rm -rf /var/lib/apt/lists/*

#RUN sh -c "$(curl -fsSL https://raw.github.com/ohmyzsh/ohmyzsh/master/tools/install.sh)"

# Create group and user
RUN groupadd --gid=$GID $BUILD_USER
RUN useradd --create-home --shell /bin/bash $BUILD_USER --uid=$UID -g $BUILD_USER
RUN echo "$BUILD_USER:$BUILD_USER_PWD" | chpasswd
RUN usermod -aG sudo $BUILD_USER

USER $BUILD_USER
WORKDIR /home/$BUILD_USER





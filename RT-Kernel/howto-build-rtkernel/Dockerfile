#docker build -t ubuntu/builder:latest .
#docker run -it -v <host path>:<container path> --name rt-builder ubuntu/builder:latest
FROM ubuntu:latest

MAINTAINER WonJong Shin "shinonejong@gmail.com"

RUN sed -i.bak "s,http://archive.ubuntu.com/ubuntu,http://de.archive.ubuntu.com/ubuntu,g;" /etc/apt/sources.list
# RUN sed -i.bak "s,http://archive.ubuntu.com/ubuntu,http://de.archive.ubuntu.com/ubuntu,g; s,http://archive.canonical.com/ubuntu,http://de.archive.canonical.com/ubuntu,g" /etc/apt/sources.list

RUN apt-get -qq update && apt-get -qqy upgrade && \
    apt-get install -y sudo bc kmod bison flex wget vim git && \
    apt-get install -y libncurses-dev libelf-dev libssl-dev lib32z1 lib32stdc++6 build-essential && \
    rm -rf /var/lib/apt/lists/*

# Change the password of user 'builder' by replace with 'builder:{NEWPASSWORD}'
RUN useradd --home-dir /home/builder --create-home --shell /bin/bash -G sudo builder && \
    echo 'builder:builder' | chpasswd
USER builder
WORKDIR /home/builder

ENV HOME /home/builder

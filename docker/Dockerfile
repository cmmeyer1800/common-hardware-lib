FROM ubuntu:latest

RUN apt-get update
RUN apt-get install -y \
    git help2man perl python3 make \
    g++ \
    libfl2 \
    libfl-dev \
    zlib1g zlib1g-dev \
    ccache \
    mold \
    libgoogle-perftools-dev \
    perl-doc \
    git autoconf flex bison \
    gtkwave \
    ssh

RUN apt-get install -y verilator

WORKDIR /root

RUN systemctl ssh start

RUN systemctl ssh enable

CMD ["/bin/bash"]
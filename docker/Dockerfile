FROM ubuntu:latest

RUN apt-get update
RUN apt-get install -y git
RUN apt-get install -y help2man 
RUN apt-get install -y perl
RUN apt-get install -y python3
RUN apt-get install -y make
RUN apt-get install -y g++
RUN apt-get install -y libfl2
RUN apt-get install -y libfl-dev
RUN apt-get install -y zlib1g zlib1g-dev
RUN apt-get install -y ccache
RUN apt-get install -y mold
RUN apt-get install -y libgoogle-perftools-dev
RUN apt-get install -y perl-doc
RUN apt-get install -y git autoconf flex bison
# RUN apt-get install -y gtkwave
RUN apt-get install -y verilator

WORKDIR /root

CMD ["/bin/bash"]
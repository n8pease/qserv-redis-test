FROM ubuntu:latest

RUN apt update

RUN apt-get install -y build-essential

RUN apt-get install -y cmake

RUN apt-get install -y gdb

COPY src/boost_1_69_0.tar.bz2 /usr/local/

WORKDIR /usr/local

RUN tar --bzip2 -xf /usr/local/boost_1_69_0.tar.bz2

RUN rm /usr/local/boost_1_69_0.tar.bz2

WORKDIR /usr/local/boost_1_69_0

RUN ./bootstrap.sh --with-libraries=test

RUN ./b2

WORKDIR /

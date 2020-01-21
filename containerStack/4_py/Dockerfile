FROM gsidx:1.0

COPY src/pybind11 /code/pybind11

RUN apt-get install -y python3-dev

RUN apt-get install -y python3-pip

RUN /usr/bin/python3.6 -m pip install pytest

RUN mkdir /code/pybind11/build

WORKDIR /code/pybind11/build

RUN cmake ..

RUN make check -j 4

WORKDIR /code/pybind11

RUN pip3 install .

COPY src/gsidxWrapper.cc /code/app

WORKDIR /code/app

RUN c++ -O3 -Wall -shared -std=c++11 \
    -fPIC `python3 -m pybind11 --includes` \
    -I/usr/local/boost_1_69_0 gsidxWrapper.cc \
    -o gsidxWrapper`python3-config --extension-suffix`


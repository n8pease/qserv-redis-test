FROM ubuntuwithboost:1.0

COPY src/hiredis /code/hiredis
RUN make install -C /code/hiredis

RUN mkdir /code/compile

COPY src/redis-plus-plus /code/redis-plus-plus
WORKDIR /code/redis-plus-plus
RUN mkdir compile
WORKDIR /code/redis-plus-plus/compile
RUN cmake -DCMAKE_BUILD_TYPE=Release ..
RUN make
RUN make install
RUN ldconfig

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

WORKDIR /

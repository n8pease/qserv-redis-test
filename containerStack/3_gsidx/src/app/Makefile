all : gsidxWrapper testGlobalSpatialIndex

gsidxWrapper : GsidxContext.o GlobalSpatialIndex.o
	c++ -O0 -Wall -shared -std=c++11 \
    -fPIC `python3 -m pybind11 --includes` \
    -I/usr/local/boost_1_69_0 gsidxWrapper.cc \
	ChunkData.o GsidxContext.o GlobalSpatialIndex.o \
    -o gsidx`python3-config --extension-suffix` \
	-L/usr/local/boost_1_69_0/stage/lib \
	-L/usr/local/lib \
	-lhiredis -lredis++ -pthread -lboost_unit_test_framework -lboost_system

testGlobalSpatialIndex : testGlobalSpatialIndex.o GlobalSpatialIndex.o GsidxContext.o
	g++ -std=c++11 -g -o testGlobalSpatialIndex \
	testGlobalSpatialIndex.o ChunkData.o GlobalSpatialIndex.o GsidxContext.o \
	-L/usr/local/boost_1_69_0/stage/lib -lredis++ -lhiredis -pthread -lboost_unit_test_framework -lboost_system

testGlobalSpatialIndex.o : GlobalSpatialIndex.o
	g++ -std=c++11 -g -I/usr/local/boost_1_69_0 -c testGlobalSpatialIndex.cc

GsidxContext.o : GlobalSpatialIndex.o
	g++ -std=c++11 -g -fPIC -I/usr/local/boost_1_69_0 -c GsidxContext.cc

GlobalSpatialIndex.o : GlobalSpatialIndex.cc ChunkData.o
	g++ -std=c++11 -g -fPIC -I/usr/local/boost_1_69_0 -c GlobalSpatialIndex.cc

ChunkData.o : ChunkData.cc
	g++ -std=c++11 -g -fPIC -I/usr/local/boost_1_69_0 -c ChunkData.cc

clean :
	rm app app.o GlobalSpatialIndex.o

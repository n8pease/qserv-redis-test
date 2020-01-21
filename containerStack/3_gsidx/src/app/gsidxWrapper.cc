#include <pybind11/pybind11.h>
#include <pybind11/functional.h>

#include "GsidxContext.h"


namespace py = pybind11;

int add(int i, int j) {
    return i + j;
}

namespace lsst {
namespace qserv {
namespace gsidx {


PYBIND11_MODULE(gsidx, m) {

    m.def("add", &add, "A function which adds two numbers");

    py::class_<GsidxContext>(m, "GsidxContext")
        .def(py::init<std::string const&>())
        .def("gsidx", &GsidxContext::gsidx, py::return_value_policy::reference_internal);

    py::class_<GlobalSpatialIndex> globalSpatialIndex(m, "GlobalSpatialIndex");
    globalSpatialIndex.def("set", &GlobalSpatialIndex::set)
        .def("get", &GlobalSpatialIndex::get);

    py::enum_<GlobalSpatialIndex::Err>(globalSpatialIndex, "GlobalSpatialIndex")
        .value("SUCCESS", GlobalSpatialIndex::Err::SUCCESS)
        .value("FAIL", GlobalSpatialIndex::Err::FAIL);

    py::class_<ChunkData>(m, "ChunkData")
        .def("chunkId", &ChunkData::chunkId)
        .def("subChunkId", &ChunkData::subChunkId)
        .def("__repr__", &ChunkData::toString);
}


}}}

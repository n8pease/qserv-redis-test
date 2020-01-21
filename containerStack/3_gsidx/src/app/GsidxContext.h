/*
 * LSST Data Management System
 *
 * This product includes software developed by the
 * LSST Project (http://www.lsst.org/).
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the LSST License Statement and
 * the GNU General Public License along with this program.  If not,
 * see <http://www.lsstcorp.org/LegalNotices/>.
 */

#ifndef LSST_QSERV_GSIDX_GSIDXCONTEXT_H
#define LSST_QSERV_GSIDX_GSIDXCONTEXT_H

// System headers
#include <thread>

// Third party headers
#include <boost/asio.hpp>

// Qserv headers
#include "GlobalSpatialIndex.h"

// Forward declarations


namespace lsst {
namespace qserv {
namespace gsidx {

/**
 * Class GsidxContext provides a single-threaded boost io_service (aka io_service) for executing asynchronous
 * calls.
 */
class GsidxContext {
public:

    GsidxContext(std::string const& name);

    ~GsidxContext();

    GlobalSpatialIndex& gsidx() { return _gsidx; }

private:
    boost::asio::io_service _io_service;
    boost::asio::executor_work_guard<boost::asio::io_service::executor_type> _ioWorkGuard;
    std::thread _workThread;
    GlobalSpatialIndex _gsidx;
};


}}} // namespace lsst::qserv::gsidx

#endif // LSST_QSERV_GSIDX_GSIDXCONTEXT_H



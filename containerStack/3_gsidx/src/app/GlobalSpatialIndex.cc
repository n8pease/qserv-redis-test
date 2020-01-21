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

// Class header
#include "GlobalSpatialIndex.h"

// System headers
#include <iostream>
#include <stdexcept>

// Third-party headers
#include <boost/asio.hpp>
#include <boost/lexical_cast.hpp>
// I guess `make install` is putting redis in a system directory?
// TODO is probably needs to go someplace more appropriate for 'real' qserv use, later on...
#include <sw/redis++/redis++.h>

// Qserv headers


namespace lsst {
namespace qserv {
namespace gsidx {


GlobalSpatialIndex::GlobalSpatialIndex(std::string const& name, boost::asio::io_context& io_context) :
        _name(name),
        _io_context(io_context)
{
    try {
        // todo the redis-cluster name and port must come from configuration. TBD how.
        _redisCluster = std::make_shared<sw::redis::RedisCluster>("tcp://" + _name);
    } catch (sw::redis::Error const& err) {
        // TBD WTD
        std::cout << "redis exception: " << err.what() << std::endl;
    }
}


std::vector<std::string> GlobalSpatialIndex::scan(std::string const& pattern) {
    auto cursor = 0LL;
    auto count = 500;
    std::vector<std::string> scanVec;
    while (true) {
        cursor = _redisCluster->scan(cursor, pattern, std::back_inserter(scanVec));
        if (cursor == 0) {
            break;
        }
    }
    return scanVec;
}


void GlobalSpatialIndex::set(unsigned long long objectId, unsigned long chunkId, unsigned short subChunkId,
                             std::function<void (Err)> onComplete) {
    _io_context.dispatch([this, objectId, chunkId, subChunkId, onComplete] () {
        auto idAndField = _getSubIdAndField(objectId);
        auto chunkAndSubchunk = _combineChunkData(chunkId, subChunkId);
        try {
            this->_redisCluster->hset(std::to_string(idAndField.first),
                                      std::to_string(idAndField.second),
                                      chunkAndSubchunk);
        } catch (sw::redis::Error const& err) {
            onComplete(FAIL);
            return;
        }
        onComplete(SUCCESS);
    });
}


ChunkData GlobalSpatialIndex::get(unsigned long long objectId) {
    auto idAndField = _getSubIdAndField(objectId);
    // the following line might throw a sw::redis::Error (inherits from std::exception)
    sw::redis::OptionalString chunkData = _redisCluster->hget(std::to_string(idAndField.first), std::to_string(idAndField.second));
    return _splitChunkData(chunkData.value());
}


std::pair<unsigned long long, short> GlobalSpatialIndex::_getSubIdAndField(unsigned long long objectId) {
    return std::make_pair<unsigned long long, short>(objectId / 100, objectId % 100);
}


ChunkData GlobalSpatialIndex::_splitChunkData(std::string chunkData) {
    auto dotLocation = chunkData.find(".");
    if (std::string::npos == dotLocation) {
        throw std::runtime_error(
            "Received invalid or badly formatted chunk data from secondary index storage: " + chunkData);
    }
    ChunkData chunk;
    try {
        chunk.setChunkId(boost::lexical_cast<unsigned long>(chunkData.substr(0, dotLocation)));
        chunk.setSubChunkId(boost::lexical_cast<unsigned short>(chunkData.substr(dotLocation+1)));
    } catch (boost::bad_lexical_cast const& err) {
        throw std::runtime_error(
            "Received invalid or badly formatted chunk data from secondary index storage: " + chunkData);
    }
    return chunk;
}


std::string GlobalSpatialIndex::_combineChunkData(unsigned long long chunkId, unsigned short subChunkId) {
    return std::to_string(chunkId) + "." + std::to_string(subChunkId);
}


}}} // namespace lsst::qserv::gsidx

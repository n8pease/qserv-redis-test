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

#ifndef LSST_QSERV_GSIDX_CHUNKDATA_H
#define LSST_QSERV_GSIDX_CHUNKDATA_H

// System headers
#include <string>


namespace lsst {
namespace qserv {
namespace gsidx {


// I couldn't find an existing class that contained this data (if it exists it's better not to create a
// duplicate type) but TODO ask around to verify if something alreday exists or not.
class ChunkData {
public:
    ChunkData() = default;

    ChunkData(unsigned long chunkId, unsigned short subChunkId)
    : _chunkId(chunkId), _subChunkId(subChunkId) {}

    // Get the chunkId
    unsigned long chunkId() const { return _chunkId; }

    // Get the subChunkId
    unsigned short subChunkId() const { return _subChunkId; }

    // Set the chunkId
    void setChunkId(unsigned long chunkId) { _chunkId = chunkId; }

    // Set the subChunkId
    void setSubChunkId(unsigned long subChunkId) { _subChunkId = subChunkId; }

    // Represent object as a string (this is particularly useful in Python)
    std::string toString() const;

private:
    unsigned long _chunkId;
    unsigned short _subChunkId;
};


}}} // namespace lsst::qserv::gsidx


#endif // LSST_QSERV_GSIDX_CHUNKDATA_H

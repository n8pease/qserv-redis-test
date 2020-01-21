#include <iostream>
#include <thread>
#include <vector>

#include <boost/asio.hpp>
#include <sw/redis++/redis++.h>

#include "GlobalSpatialIndex.h"

using namespace sw::redis;

int main (int argc, char *argv[]) {
    boost::asio::io_context io;
    auto ioWorkGuard = boost::asio::make_work_guard(io); // prevents io from exiting when there is no work to do.
    auto workThread = std::thread([&io] () { io.run(); });
    lsst::qserv::gsidx::GlobalSpatialIndex gsidx(io);

    gsidx.set(1, 2, 3);
    std::cout << "resetting" << std::endl;
    ioWorkGuard.reset();
    std::cout << "joining" << std::endl;
    workThread.join();
    std::cout << "so long, cake eaters!" << std::endl;

    // boost::asio::steady_timer t(io, boost::asio::chrono::seconds(5));

    // t.wait();

    // std::cout << "hello from boost!";

    // try {
    //     // ***** Redis Cluster *****

    //     // Create a RedisCluster object, which is movable but NOT copyable.
    //     auto redis_cluster = RedisCluster("tcp://redis-cluster:6379");

    //     // RedisCluster has similar interfaces as Redis.
    //     redis_cluster.set("key", "value");
    //     auto val = redis_cluster.get("key");
    //     if (val) {
    //         std::cout << *val << std::endl;
    //     }   // else key doesn't exist.

    //     // Keys with hash-tag.
    //     redis_cluster.set("key{tag}1", "val1");
    //     redis_cluster.set("key{tag}2", "val2");
    //     redis_cluster.set("key{tag}3", "val3");

    //     std::vector<OptionalString> hash_tag_res;
    //     redis_cluster.mget({"key{tag}1", "key{tag}2", "key{tag}3"},
    //             std::back_inserter(hash_tag_res));

    // } catch (const Error &e) {
    //     std::cout << "error!";
    // }
}

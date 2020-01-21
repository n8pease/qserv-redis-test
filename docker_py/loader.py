import random
from rediscluster import RedisCluster
import sys

NUM_OBJECT_ID = pow(2, 64)
NUM_CHUNK_ID = pow(2, 32)
NUM_SUB_CHUNK_ID = pow(2, 16)

class RedisInterface:

    UseOptimization = True

    def __init__(self):
        '''Requires at least one node for cluster discovery. Multiple nodes is recommended.'''
        startup_nodes = [{"host": "redis-cluster", "port": "6379"}]

        # Note: See note on Python 3 for decode_responses behaviour
        self.rc = RedisCluster(startup_nodes=startup_nodes, decode_responses=True)
        

    def _get_hash_key_field(self, key):
        """For a given key, get the (key, field) combo for insert and get out of a hash value."""
        return (int(key/100), key%100)


    def hash_set(self, key, value):
        key, field = self._get_hash_key_field(key)
        self.rc.hset(str(key), str(field), str(value))


    def hash_get(self, key):
        key, field = self._get_hash_key_field(key)
        return self.rc.hget(str(key), str(field))


    def loadrange(self, low: int, high: int, count: int):
        """Load an aproximate number of keys in a given range.

        Parameters
        ----------
        low : int
            The starting value
        high : int
            The highest value
        count : int
            The value of keys to be loaded (becasue of remainders there may be an extra key)
        """
        interval = (high - low) / count
        for i in range(low, high, (int((high - low)/ count))):
            key = i
            value = random.randrange(0, pow(2, 64)) # choose a random number up to 64 bits, assuming we can pack chunk+subchunk into that.
            self.hash_set(key, int(value))


if __name__ == '__main__':
    print(sys.argv)
    redisInterface = RedisInterface()
    redisInterface.loadrange(int(sys.argv[1]), int(sys.argv[2]), int(sys.argv[3]))



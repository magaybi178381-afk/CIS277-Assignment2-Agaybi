#include "MemoryPool.h"
#include "Queue.h"

class PacketQueue
{
public:
    PacketQueue(std::size_t blockSize, std::size_t blockCount);

    bool receive(std::size_t id, const unsigned char* bytes, std::size_t length);
    bool processNext(std::size_t& id, std::vector<unsigned char>& bytes);

    std::size_t pending() const;
    std::size_t availableBlocks() const;
};

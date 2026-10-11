#include "PacketQueue.h"

#include <cstring>

PacketQueue::PacketQueue(
    std::size_t blockSize,
    std::size_t blockCount
)
    : pool(blockSize, blockCount),
      queue(blockCount)
{
}

bool PacketQueue::receive(
    std::size_t id,
    const unsigned char* bytes,
    std::size_t length
)
{
    if (bytes == nullptr)
    {
        return false;
    }

    if (length == 0)
    {
        return false;
    }

    if (length > pool.blockSize())
    {
        return false;
    }

    if (queue.full())
    {
        return false;
    }

    if (pool.availableBlocks() == 0)
    {
        return false;
    }

    void* block = pool.allocate();

    if (block == nullptr)
    {
        return false;
    }

    std::memcpy(block, bytes, length);

    PacketDescriptor packet;

    packet.id = id;
    packet.black = block;
    packet.length = length;

    if(!queue.enqueue(packet))
    {
        pool.deallocate(block);
        return false;
    }

    return true;
}
        

#include "MemoryPool.h"

MemoryPool::MemoryPool(size_t blockSize, size_t blockCount)
{
    blockS = blockSize;
    blockC = blockCount;

    memory = new unsigned char[blockS * blockC];

    allocated = new bool[blockC];

    for (size_t i = 0; i < blockC; i++)
    {
        allocated[i] = false;

        void* block = memory + i * blockS;

        freeStack.push(block);
    }
}

MemoryPool::~MemoryPool()
{
    delete[] memory;
    delete[] allocated;
}

void* MemoryPool::allocate()
{
    if (freeStack.empty())
    {
        return nullptr;
    }

    void* block = freeStack.pop();

    unsigned char* address =
        static_cast<unsigned char*>(block);

    size_t index =
        (address - memory) / blockS;

    allocated[index] = true;

    return block;
}

bool MemoryPool::deallocate(void* ptr)
{
    if (ptr == nullptr)
    {
        return false;
    }

    unsigned char* address =
        static_cast<unsigned char*>(ptr);

    if (address < memory ||
        address >= memory + blockS * blockC)
    {
        return false;
    }

    size_t index =
        (address - memory) / blockS;

    if ((address - memory) % blockS != 0)
    {
        return false;
    }

    if (!allocated[index])
    {
        return false;
    }

    allocated[index] = false;

    freeStack.push(ptr);

    return true;
}

size_t MemoryPool::availableBlocks() const
{
    return freeStack.size();
}

size_t MemoryPool::allocatedBlocks() const
{
    return blockC - freeStack.size();
}

size_t MemoryPool::blockSize() const
{
    return blockS;
}

size_t MemoryPool::capacity() const
{
    return blockS * blockC;
}

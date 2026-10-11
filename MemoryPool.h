#ifndef MEMORYPOOL_H
#define MEMORYPOOL_H

#include <cstddef>
#include "Stack.h"

class MemoryPool
{
private:
    std::size_t blockSize_;
    std::size_t blockCount_;

    unsigned char* memory;

    Stack<void*> freeStack;

    bool* allocated;

public:
    MemoryPool(std::size_t blockSize, std::size_t blockCount);
    ~MemoryPool();

    void* allocate();
    bool deallocate(void* ptr);

    std::size_t availableBlocks() const;
    std::size_t allocatedBlocks() const;
    std::size_t blockSize() const;
    std::size_t capacity() const;
};

#endif

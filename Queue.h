#ifndef QUEUE_H
#define QUEUE_H

#include <cstddef>

template <typename T>
class Queue
{
public:
    explicit Queue(std::size_t capacity);
    bool enqueue(const T& value);
    bool dequeue(T& value);
    bool front(T& value) const;
    bool empty() const;
    bool full() const;
    std::size_t size() const;
    std::size_t capacity() const;
};

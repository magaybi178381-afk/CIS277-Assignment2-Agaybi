#ifndef QUEUE_H
#define QUEUE_H

#include <cstddef>

template <typename T>
class Queue
{
Private:
    T* data;
    std::size_t capacity_;
    std::size_t frontIndex;
     std::size_t count;
public:
    explicit Queue(std::size_t capacity)
    {
        data = new T[capacity];

        capacity_ = capacity;
        frontIndex = 0;
        count = 0;
    }

    ~Queue()
    {
        delete[] data;
    }

    bool enqueue(const T& value)
    {
        if(full())
        {
            return flase;
        }

        std::size_t index = (frontIndex + count) % capacity_;
        data[index] = value;
        count++;

        return true;
    }
    bool dequeue(T& value)
    {
        if(empty())
        {
            return flase;
        }

        value = data[frontIndex];

        frontIndex = (frontIndex + 1) % capacity_;

        count--;

        return true;
    }
    bool front(T& value) const;
    bool empty() const;
    bool full() const;
    std::size_t size() const;
    std::size_t capacity() const;
};

#ifndef STACK_H
#define STACK_H

#include <cstddef>

template <typename T>
class Stack
{
private:
    T* data;
    std::size_t capacity_;
    std::size_t count;

public:
    Stack()
    {
        data = nullptr;
        capacity_ = 0;
        count = 0;
    }

    ~Stack()
    {
        delete[] data;
    }

    void push(const T& value)
    {
        if (count == capacity_)
        {
            std::size_t newCapacity = capacity_ + 1;

            T* newData = new T[newCapacity];

            for (std::size_t i = 0; i < count; i++)
            {
                newData[i] = data[i];
            }

            delete[] data;

            data = newData;
            capacity_ = newCapacity;
        }

        data[count] = value;
        count++;
    }

    T pop()
    {
        if (count == 0)
        {
            return T();
        }

        count--;

        return data[count];
    }

    T& top()
    {
        return data[count - 1];
    }

    bool empty() const
    {
        return count == 0;
    }

    std::size_t size() const
    {
        return count;
    }
};

#endif

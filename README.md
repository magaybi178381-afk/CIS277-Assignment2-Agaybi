# CIS-277 Assignment 2: Network Packet Arrival Queue
# CIS-277 Assignment 2: Network Packet Arrival Queue

## Student

Marc Agaybi

## Design

The program uses a fixed-capacity circular array for the Queue.

The queue keeps track of three values:

- `frontIndex` — the position of the oldest item.
- `count` — the number of items currently in the queue.
- `capacity_` — the maximum number of items.

When a new item is added, the program calculates its position using:

```text
(frontIndex + count) % capacity
```

When an item is removed, `frontIndex` moves forward using:

```text
(frontIndex + 1) % capacity
```

The `%` operator allows the queue to wrap around to the beginning of the array without moving the other elements.

The Queue is responsible for maintaining the FIFO order of packet descriptors.

The MemoryPool is responsible for providing and recycling the memory blocks that hold the packet bytes. The MemoryPool uses the Stack to manage its available blocks.

The Queue and MemoryPool have different responsibilities. The Queue controls packet arrival order, while the MemoryPool controls available memory blocks.

The MemoryPool may reuse blocks in LIFO order, but this does not change the FIFO order of the packet Queue.

## How to Compile

```text
g++ -std=c++23 -Wall -Wextra -pedantic main.cpp PacketQueue.cpp MemoryPool.cpp -o packet_queue
```

## How to Run

```text
./packet_queue
```

## Tests and Results

The program was tested with the following cases:

| Test | Expected Result | Actual Result |
|---|---|---|
| Queue with integers | Items are returned FIFO | Passed |
| Queue with strings | Items are returned FIFO | Passed |
| Queue wraparound | New item uses wrapped array position | Passed |
| `front()` | Shows first item without removing it | Passed |
| Full queue | `enqueue()` returns false | Passed |
| Empty queue | `dequeue()` returns false | Passed |
| Receive three packets | Packets are stored in arrival order | Passed |
| Process packets | Packets are returned FIFO | Passed |
| Receive after processing | New packet can reuse released memory | Passed |
| `0x00` and `0xFF` | Binary values are preserved | Passed |
| Length of 1 | Packet is accepted | Passed |
| Length equal to block size | Packet is accepted | Passed |
| Packet larger than block size | Packet is rejected | Passed |
| Full packet queue | Additional packet is rejected | Passed |
| Process empty queue | Returns false and leaves outputs unchanged | Passed |

## Analysis Questions

### 1. Why must packet service be FIFO even though free-block reuse is LIFO?

Packets must be processed in the order they arrived. The Queue provides FIFO ordering. The MemoryPool only manages which memory block is available. Even if the MemoryPool reuses the most recently released block first, it does not change the order of the packet descriptors in the Queue.

### 2. How does your circular array wrap without shifting all waiting packets?

The queue uses the `%` operator to calculate the next position. When an index reaches the end of the array, it wraps back to index zero.

For example:

```text
(frontIndex + count) % capacity
```

This allows new items to use available positions at the beginning of the array without moving the existing items.

### 3. What happens at queue overflow and underflow, and why must those attempts leave state unchanged?

When the queue is full, `enqueue()` returns `false` and does not add an item.

When the queue is empty, `dequeue()` and `front()` return `false` and do not change the output argument.

The state must remain unchanged so that a failed operation does not corrupt or change the queue.

### 4. What are the time complexities of queue operations and of `receive`/`processNext` when the packet has `length` bytes?

The Queue operations are O(1) because they only update indexes and the element count.

`receive()` and `processNext()` are O(length) because the packet bytes must be copied. The Queue and MemoryPool operations themselves are O(1), but copying the packet requires time proportional to its length.

### 5. Why must `processNext` copy bytes out before returning the block to the pool?

The block belongs to the MemoryPool. After it is returned to the pool, it can be reused for another packet. Therefore, `processNext()` must copy the packet bytes into the output vector before releasing the block.

## AI Use

I used AI to help explain C++ concepts, review the assignment requirements, and help write and check parts of the implementation.

I checked the code by compiling it with C++23 on onlinegdb and running the required tests and demonstrations. I also checked the queue behavior, packet order, binary data, pool reuse, queue overflow, and empty queue behavior.

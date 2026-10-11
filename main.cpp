#include <iostream>
#include <string>
#include <vector>

#include "Queue.h"
#include "PacketQueue.h"

void testQueue()
{
    std::cout << "===== Queue Tests =====\n\n";

    Queue<int> numbers(3);

    std::cout << "Integer Queue:\n";

    std::cout << "Enqueue 1: "
              << numbers.enqueue(1) << "\n";

    std::cout << "Enqueue 2: "
              << numbers.enqueue(2) << "\n";

    std::cout << "Enqueue 3: "
              << numbers.enqueue(3) << "\n";

    std::cout << "Enqueue 4: "
              << numbers.enqueue(4) << "\n";

    int value;

    numbers.front(value);

    std::cout << "Front: "
              << value << "\n";

    numbers.dequeue(value);

    std::cout << "Dequeue: "
              << value << "\n";

    numbers.enqueue(4);

    std::cout << "Enqueue 4 after dequeue: "
              << numbers.size()
              << " items\n";

    while (!numbers.empty())
    {
        numbers.dequeue(value);

        std::cout << "Dequeue: "
                  << value << "\n";
    }

    std::cout << "Dequeue empty queue: "
              << numbers.dequeue(value)
              << "\n\n";


    Queue<std::string> words(2);

    std::cout << "String Queue:\n";

    words.enqueue("Hello");
    words.enqueue("World");

    std::string word;

    words.front(word);

    std::cout << "Front: "
              << word
              << "\n";

    words.dequeue(word);

    std::cout << "Dequeue: "
              << word
              << "\n\n";
}


void printBytes(
    const std::vector<unsigned char>& bytes
)
{
    std::cout << "Bytes: ";

    for (unsigned char byte : bytes)
    {
        std::cout << std::hex
                  << static_cast<int>(byte)
                  << " ";
    }

    std::cout << std::dec << "\n";
}


int main()
{
    testQueue();

    std::cout << "===== Packet Queue =====\n\n";

    PacketQueue packets(8, 3);

    unsigned char packet1[] =
    {
        0x00, 0x01, 0x02, 0xFF
    };

    unsigned char packet2[] =
    {
        0x10, 0x20, 0x30
    };

    unsigned char packet3[] =
    {
        0xAA, 0xBB, 0xCC, 0xDD, 0xFF
    };

    std::cout << "Receive packet 1: "
              << packets.receive(101, packet1, sizeof(packet1))
              << "\n";

    std::cout << "Receive packet 2: "
              << packets.receive(102, packet2, sizeof(packet2))
              << "\n";

    std::cout << "Receive packet 3: "
              << packets.receive(103, packet3, sizeof(packet3))
              << "\n";

    std::cout << "Pending: "
              << packets.pending()
              << "\n";

    std::cout << "Available blocks: "
              << packets.availableBlocks()
              << "\n\n";


    unsigned char packet4[] =
    {
        0x44, 0x55
    };

    std::cout << "Receive packet 4 while queue is full: "
              << packets.receive(104, packet4, sizeof(packet4))
              << "\n";

    std::cout << "Pending after failed receive: "
              << packets.pending()
              << "\n\n";


    std::size_t id = 0;
    std::vector<unsigned char> bytes;

    packets.processNext(id, bytes);

    std::cout << "Processed packet ID: "
              << id
              << "\n";

    printBytes(bytes);

    std::cout << "Pending: "
              << packets.pending()
              << "\n";

    std::cout << "Available blocks: "
              << packets.availableBlocks()
              << "\n\n";


    std::cout << "Receive packet 4 after processing packet 1: "
              << packets.receive(104, packet4, sizeof(packet4))
              << "\n";

    std::cout << "Pending: "
              << packets.pending()
              << "\n\n";


    std::cout << "Processing remaining packets:\n";

    while (packets.pending() > 0)
    {
        packets.processNext(id, bytes);

        std::cout << "Processed packet ID: "
                  << id
                  << "\n";

        printBytes(bytes);
    }

    std::cout << "\n";


    id = 999;

    bytes.clear();
    bytes.push_back(0xAA);

    bool result = packets.processNext(id, bytes);

    std::cout << "Process empty queue: "
              << result
              << "\n";

    std::cout << "ID after failed process: "
              << id
              << "\n";

    std::cout << "Bytes after failed process: ";

    printBytes(bytes);

    std::cout << "\n";


    unsigned char oneByte[] =
    {
        0xFF
    };

    std::cout << "Receive length 1: "
              << packets.receive(
                     105,
                     oneByte,
                     sizeof(oneByte)
                 )
              << "\n";

    packets.processNext(id, bytes);

    std::cout << "Processed ID: "
              << id
              << "\n";

    printBytes(bytes);

    std::cout << "\n";


    unsigned char exactBlock[] =
    {
        0x00, 0x01, 0x02, 0x03,
        0x04, 0x05, 0x06, 0xFF
    };

    std::cout << "Receive exactly blockSize bytes: "
              << packets.receive(
                     106,
                     exactBlock,
                     sizeof(exactBlock)
                 )
              << "\n";

    packets.processNext(id, bytes);

    std::cout << "Processed ID: "
              << id
              << "\n";

    printBytes(bytes);

    std::cout << "\n";


    unsigned char tooLarge[] =
    {
        0x00, 0x01, 0x02,
        0x03, 0x04, 0x05,
        0x06, 0x07, 0x08
    };

    std::cout << "Receive packet larger than block: "
              << packets.receive(
                     107,
                     tooLarge,
                     sizeof(tooLarge)
                 )
              << "\n";

    std::cout << "\n";

    std::cout << "Final pending: "
              << packets.pending()
              << "\n";

    std::cout << "Final available blocks: "
              << packets.availableBlocks()
              << "\n";

    return 0;
}

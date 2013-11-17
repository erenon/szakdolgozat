#include <atomic>
#include <thread>
#include <cassert>

template <typename T>
class SpscQueue
{
    enum { maxSize = 100 };
    
    std::atomic<size_t> _writeIndex;
    T _buffer[maxSize];
    std::atomic<size_t> _readIndex;

    SpscQueue(const SpscQueue &) = delete;
    SpscQueue(SpscQueue &&)      = delete;
    const SpscQueue& operator=(const SpscQueue&) = delete;
    
public:
    SpscQueue(void)
        :_writeIndex(0), _readIndex(0)
    {}    

    bool push(const T& t) {
        size_t writeIndex = _writeIndex.load();
        size_t next = (writeIndex + 1) % maxSize;

        if (next == _readIndex.load()) {
            return false;   // full buffer
        }

        _buffer[writeIndex] = t;

        _writeIndex.store(next);

        return true;
    }

    bool pop(T& ret) {
        size_t writeIndex = _writeIndex.load();
        size_t readIndex  = _readIndex.load();
        
        if (writeIndex == readIndex) {
            return false; // empty buffer
        }

        ret = _buffer[readIndex];
        
        size_t next = (readIndex + 1) % maxSize;
        _readIndex.store(next);
        
        return true;
    }
};

typedef int Item;
typedef SpscQueue<Item> Queue;
const Item g_iterCount = 1000000;

void producer(Queue& q) {
    for (Item i = 0; i < g_iterCount; ++i) {
        while (!q.push(i));
    }
}

void consumer(Queue& q) {
    for (Item i = 0; i < g_iterCount; ++i) {
        Item popped;
        while (!q.pop(popped));
        assert(popped == i);
    }
}

int main() {
    Queue q;
    std::thread prodThread(producer, std::ref(q));
    std::thread consThread(consumer, std::ref(q));
    
    prodThread.join();
    consThread.join();
    return 0;
}

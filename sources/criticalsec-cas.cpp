#include <atomic>
#include <iostream>

void doProtected() {}

typedef std::atomic<bool> Lock;

void startCritical(Lock& lock) {
    bool unlocked = false;
    while (!lock.compare_exchange_weak(unlocked, true));
}

void stopCritical(Lock& lock) { lock.store(false); }

int main() {
    Lock lock(false);
    
    std::cout << std::boolalpha << lock.load() << std::endl;

    startCritical(lock);
        std::cout << std::boolalpha << lock.load() << std::endl;
        doProtected();
    stopCritical(lock);
    
    std::cout << std::boolalpha << lock.load() << std::endl;
    
    return 0;
}

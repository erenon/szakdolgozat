#include <mutex>

std::mutex m1;
std::mutex m2;
std::mutex m3;

void doProtectedOperation() {}

int main() {
    // example.1
{
    std::lock(m1, m2, m3);
    
    doProtectedOperation();
    
    m1.unlock();
    m2.unlock();
    m3.unlock();
}
    // example.1
    
    // example.2
{
    std::lock(m1, m2, m3);
    
    std::lock_guard<std::mutex> lock1(m1, std::adopt_lock);
    std::lock_guard<std::mutex> lock2(m2, std::adopt_lock);
    std::lock_guard<std::mutex> lock3(m3, std::adopt_lock);
    
    doProtectedOperation();
}
    // example.2

    return 0;
}

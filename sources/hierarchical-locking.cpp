#include <stdexcept>
#include <mutex>
#include <stack>
#include <thread>

thread_local std::stack<std::size_t> lockedOrders;

template <typename BasicLockable>
class OrderedLockable {
public:
    OrderedLockable(BasicLockable& resource, std::size_t order)
        :_resource(resource),
         _order(order)
    {}
    
    void lock() {
        if (lockedOrders.top() > _order) {
            throw std::logic_error("Invalid locking order");
        }
        _resource.lock();
        lockedOrders.push(_order);
    }
    
    void unlock() {
        lockedOrders.pop();
        _resource.unlock();
    }
    
    std::size_t getOrder() {
        return _order;
    }
    
private:
    BasicLockable& _resource;
    std::size_t _order;
};

int main() {
    std::mutex m1;
    std::mutex m2;
    OrderedLockable<std::mutex> om1(m1, 1);
    OrderedLockable<std::mutex> om2(m1, 2);
    
    om1.lock();
    om2.lock();
    om2.unlock();
    om1.unlock();
    
    try {
        om2.lock();
        om1.lock();
        om1.unlock();    
        om2.unlock();
        
        return 1;
    } catch (const std::logic_error&) {
        // ok, let it pass
    }
    
    return 0;
}

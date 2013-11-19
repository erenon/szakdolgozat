#include <memory>
#include <thread>
#include <iostream>
#include <cassert>

struct Task {
    int data;
    
    void execute() {
        std::cout << "Task data: " << data << std::endl;
    }
};

typedef std::unique_ptr<Task> TaskPtr;

void taskProcessor(TaskPtr taskPtr) {
    taskPtr->execute();
}

int main() {
    TaskPtr taskPtr(new Task{1});
    std::thread processor(taskProcessor, std::move(taskPtr));

    assert(taskPtr.get() == nullptr);

    processor.join();
    return 0;
}

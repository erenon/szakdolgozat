void doProtected() {}

// HIBAS KOD

void startCritical(bool& lock) {
    while (lock);
    
    lock = true;
}

void stopCritical(bool& lock) {
    lock = false;
}

int main() {
    bool lock = false;

    startCritical(lock);
        doProtected();
    stopCritical(lock);
    
    return 0;
}

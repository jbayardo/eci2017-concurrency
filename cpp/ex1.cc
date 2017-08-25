#include <iostream>
#include <thread>
#include <atomic>
#include <functional>
#include <chrono>

void dekker(std::atomic<int> &x, std::atomic<int> &y, std::atomic<int> &r) {
    // Without this sleep here, my computer never gets the desired scheduling. The problem is that one thread finishes
    // way faster than the other, and thus we always get the same result.
    std::this_thread::sleep_for(std::chrono::milliseconds(5));
    // The following are not data races because we are using atomic variables. We are, nevertheless, using a relaxed
    // memory store order, which means that any of the operations could happen before the other in the separate threads.
    x.store(1, std::memory_order_relaxed);
    // The store into `r` can be done with std::memory_order_relaxed because there is a direct dependency on `y`, which
    // means it should never be reordered by the compiler.
    r.store(y.load(std::memory_order_relaxed), std::memory_order_relaxed);
}

int main() {
    std::atomic<int> x, y, r1, r2;
    while (true) {
        x = y = r1 = r2 = 0;

        std::thread t1(dekker, std::ref(x), std::ref(y), std::ref(r1));
        std::thread t2(dekker, std::ref(y), std::ref(x), std::ref(r2));
        t2.join();
        t1.join();

        if (r1.load() == 0 && r2.load() == 0) {
            std::cout << "Found condition!" << std::endl;
            exit(-1);
        }
    }

    return 0;
}
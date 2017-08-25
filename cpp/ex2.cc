#include <iostream>
#include <thread>
#include <atomic>
#include <functional>
#include <chrono>

void dekker(std::atomic<int> &x, std::atomic<int> &y, std::atomic<int> &r) {
    // Without this sleep here, my computer runs one thread entirely before the other one. The problem is that one
    // thread finishes way faster than the other, and thus we always get the same result.
    std::this_thread::sleep_for(std::chrono::milliseconds(5));
    // This code forbids the undesired result because the generated assembler is equivalent to the SB+syncs example for
    // x86-64 and PPC. Running the example for a very long time does not finish, which gives a tiny bit of confidence
    // that it actually works in practice.
    x.store(1, std::memory_order_release);
    std::atomic_thread_fence(std::memory_order_seq_cst);
    r.store(y.load(std::memory_order_consume), std::memory_order_release);
}

int main() {
    std::atomic<int> x, y, r1, r2;
    while (true) {
        x = y = r1 = r2 = 0;

        std::thread t1(dekker, std::ref(x), std::ref(y), std::ref(r1));
        std::thread t2(dekker, std::ref(y), std::ref(x), std::ref(r2));
        t2.join();
        t1.join();

        if (r1.load(std::memory_order_seq_cst) == 0 && r2.load(std::memory_order_seq_cst) == 0) {
            std::cout << "ERROR! Found forbidden condition." << std::endl;
            exit(-1);
        }
    }

    return 0;
}
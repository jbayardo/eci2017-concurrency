#include "relacy/relacy_std.hpp"

int happened = 0;

struct race_test : rl::test_suite<race_test, 2> {
    std::atomic<int> x;
    std::atomic<int> y;
    std::atomic<int> r1;
    std::atomic<int> r2;

    void before() {
        x($) = 0;
        y($) = 0;
        r1($) = 0;
        r2($) = 0;
    }

    void thread(unsigned thread_index) {
        if (thread_index == 0) {
            x.store(1, std::memory_order_release);
            std::atomic_thread_fence(std::memory_order_seq_cst);
            r1.store(y.load(std::memory_order_consume), std::memory_order_relaxed);
        } else {
            y.store(1, std::memory_order_release);
            std::atomic_thread_fence(std::memory_order_seq_cst);
            r2.store(x.load(std::memory_order_consume), std::memory_order_relaxed);
        }
    }

    void after() {
        if (r1.load(std::memory_order_seq_cst) == 0 && r2.load(std::memory_order_seq_cst) == 0) {
            happened++;
        }
    }
};

int main() {
    rl::simulate<race_test>();
    std::cout << "Forbidden condition happened: " << happened << std::endl;
}
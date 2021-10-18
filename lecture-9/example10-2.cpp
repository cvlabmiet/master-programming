#include <atomic>
#include <future>
#include <iostream>
#include <thread>

#include <boost/lockfree/queue.hpp>

int main()
{
    boost::lockfree::queue<int> q;
    std::atomic<int> sum = 0;

    auto produce = [&q]() {
        for (int i = 1; i <= 100; ++i)
        {
            q.push(i);
            std::this_thread::yield();
        }
    };

    std::function<int(decltype(sum)&)> consume = [&q](auto& x) {
        int count = 0;
        while (q.consume_one([&x](int i){ x += i; }))
            ++count;
        return count;
    };

    std::thread t1{produce};
    auto t2 = std::async(consume, std::ref(sum));
    auto t3 = std::async(consume, std::ref(sum));
    t1.join();

    std::cout << "Thread2 count " << t2.get() << "\n"
              << "Thread3 count " << t3.get() << "\n"
              << "Sum " << sum << "\n";
    q.consume_all([&sum](int i){ sum += i; });
    std::cout << sum << std::endl;
}

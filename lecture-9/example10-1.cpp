#include <iostream>
#include <memory>
#include <mutex>
#include <thread>

#include <boost/thread/tss.hpp>

int main(int argc, const char**)
{
    std::mutex mutex;

    auto helper = [](auto& ptr) {
        if (!ptr.get())
        {
            ptr.reset(new bool{true});
            std::cout << "done" << '\n';
        }
    };

    auto worker = [&mutex, &helper, flag = argc > 1]() {
        static boost::thread_specific_ptr<bool> ptr1;
        static std::shared_ptr<bool> ptr2;
        std::lock_guard lock{mutex};
        if (flag)
            helper(ptr2);
        else
            helper(ptr1);
    };

    std::thread t[] = {std::thread{worker}, std::thread{worker}, std::thread{worker}};
    for (auto& x : t)
        x.join();
}

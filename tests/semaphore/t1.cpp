#include <srook/thread.hpp>
#include <srook/mutex.hpp>
#include <srook/semaphore.hpp>
#include <srook/condition_variable.hpp>
#include <iostream>

srook::condition_variable cv;
bool is_started = false;
srook::mutex m;
srook::semaphore sm(2);

void f()
{
    {
        srook::unique_lock<srook::mutex> lk(m);
        cv.wait(lk, []{ return is_started; });
        std::cout << __func__ << ": " << srook::this_thread::get_id() << std::endl;
    }

    sm.down();
    srook::lock_guard<srook::semaphore> smlk(sm, srook::adopt_lock);

    {
        srook::lock_guard<srook::mutex> lk(m);
        std::cout << __func__ << ": " << srook::this_thread::get_id() << ": get lock" << std::endl;
    }
}

void g()
{
    {
        srook::lock_guard<srook::mutex> lk(m);
        is_started = true;
        std::cout << __func__ << ": " << srook::this_thread::get_id() << std::endl;
    }
    sm.down_all();
    cv.notify_all();

    using namespace srook::mutexes::includes;
    srook::this_thread::sleep_for(chrono::seconds(3));
    sm.up_all();
}

int main()
{
    std::cout << "                                                              get lock"   << std::endl;
    std::cout << "  f -> try to get resource but all resource is downed by g ------*----->" << std::endl;
    std::cout << " /                                                               |"       << std::endl;
    std::cout << "g -------------------- sleep for 3 seconds ------------------> up_all-->" << std::endl;
    std::cout << " \\                                                               |"       << std::endl;
    std::cout << "  f -> try to get resource but all resource is downed by g ------*----->" << std::endl;
    std::cout << "                                                              get lock"   << std::endl;
    srook::thread th1(f), th2(f), th3(g);
    th1.join(); th2.join(); th3.join();
}

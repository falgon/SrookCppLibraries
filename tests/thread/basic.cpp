// #define SROOK_CONFIG_THREAD_ENABLE_PHYSICAL_CONCURRENCY 1
#include <iostream>
#include <srook/mutex.hpp>
#include <srook/thread.hpp>
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
#    include <boost/bind.hpp>
#endif

srook::mutex m;

#ifdef SROOK_CONFIG_THREAD_ENABLE_PHYSICAL_CONCURRENCY
void ext()
{
    std::cout << srook::thread::physical_concurrency() << std::endl;
}
#endif

struct X {
    void operator()() const
    {
        srook::lock_guard<srook::mutex> lk(m);
		std::cout << srook::this_thread::get_id() << std::endl;
    }
};

void f(int x) 
{
	srook::lock_guard<srook::mutex> lk(m);
	std::cout << x << std::endl;
}

void tests()
{
    X x;
    srook::thread th1(x), th2(x);
    th1.join();
	th2.join();
	
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
	srook::thread th3(f, 42);
#else
	srook::thread th3(boost::bind(f, 42));
#endif
	th3.join();

#ifdef SROOK_CONFIG_THREAD_ENABLE_PHYSICAL_CONCURRENCY
	ext();
#endif
}

int main()
{
	tests();
}

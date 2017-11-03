#include <srook/mutex.hpp>
#include <srook/thread.hpp>
#include <iostream>

srook::once_flag once;
int data = 0;

void init(int x)
{
	data = x; 
}

void init()
{
	data = 42;
}

void thread_proc()
{
#if SROOK_CPLUSPLUS < SROOK_CPLUSPLUS11_CONSTANT
	srook::call_once(once, static_cast<void (*)()>(&init));
#else
	srook::call_once(once, static_cast<void (*)(int)>(&init), 42);
#endif
}

int main()
{
	srook::thread th1(thread_proc), th2(thread_proc), th3(thread_proc);
	th1.join(); th2.join(); th3.join();
	std::cout << data << std::endl;
}

#include <srook/mutex.hpp>

using namespace srook::mutexes::includes;

srook::recursive_timed_mutex rtm;

void f()
{
	if (rtm.try_lock_for(chrono::seconds(3))) {
		rtm.unlock();
	}
}

void test1()
{
	for(std::size_t i = 0; i < 10; ++i) rtm.lock();
	for(std::size_t i = 0; i < 10; ++i) rtm.unlock();
}

void test2()
{
	if (!rtm.try_lock_until(chrono::system_clock::now() + chrono::seconds(3))) {
		// ...
		return ;
	}
	f();
	rtm.unlock();
}

int main()
{
	test1();
	test2();
}

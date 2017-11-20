#include <srook/semaphore/semaphore.hpp>
#include <srook/semaphore/timed_semaphore.hpp>
#include <srook/semaphore/binary_semaphore.hpp>
#include <srook/thread.hpp>

srook::semaphore sm;
srook::timed_semaphore ts;
srook::binary_semaphore bs;

void f(srook::unique_lock<srook::semaphore> lk)
{
	lk.unlock();
}

void g(srook::unique_lock<srook::timed_semaphore> lk)
{
	lk.unlock();
}

void h(srook::unique_lock<srook::binary_semaphore> lk)
{
	lk.unlock();
}

int main()
{
	{
		srook::unique_lock<srook::semaphore> lk(sm, srook::defer_lock);
		lk.lock();
		srook::thread th(f, srook::move(lk));
		th.join();
	}
	{
		using namespace srook::mutexes::includes;
		srook::unique_lock<srook::timed_semaphore> lk(ts, chrono::seconds(2));
		srook::thread th(g, srook::move(lk));
		th.join();
	}
	{
		srook::unique_lock<srook::binary_semaphore> lk(bs);
		srook::thread th(h, srook::move(lk));
		th.join();
	}
}

// #define SROOK_CONFIG_DISABLE_DEPRECATED_OF_ATTRIBUTE_MESSAGES 1
// #define SROOK_CONFIG_ENABLE_CPP03_IMPLICIT_MOVE_CONSTRUCTIBLE 1

// when the environment is C++11 or later, srook::mutexes::includes points the components of std namespace
// when the environment is C++03 or earlier, srook::mutexes::includes points the components of boost namespace.

#include <srook/mutex.hpp>
#include <cassert>

srook::mutex m;
srook::recursive_mutex rm;
srook::timed_mutex tm;

srook::mutexes::includes::mutex libm;
srook::mutexes::includes::recursive_mutex librm;
srook::mutexes::includes::timed_mutex libtm;
srook::mutexes::includes::recursive_timed_mutex librtm;

namespace compatibility {	 
	void basic()
	{
		{
			srook::unique_lock<srook::mutexes::includes::mutex> lk1(libm);
			srook::unique_lock<srook::mutexes::includes::recursive_mutex> lk2(librm);
			srook::unique_lock<srook::mutexes::includes::timed_mutex> lk3(libtm);
			srook::unique_lock<srook::mutexes::includes::recursive_timed_mutex> lk4(librtm);
		}
		{
			srook::mutexes::includes::unique_lock<srook::mutex> lk1(m);
			srook::unique_lock<srook::mutex> lk2(srook::move(lk1));
		}		
		{
			srook::mutexes::includes::unique_lock<srook::mutex> lk1(m);
			srook::unique_lock<srook::mutex> lk2;
			lk2 = srook::move(lk1);
		}
	}

	void lock_tags()
	{
		{
			srook::mutexes::includes::unique_lock<srook::mutex> lk1(m, srook::mutexes::includes::defer_lock);
			srook::unique_lock<srook::mutex> lk2(srook::move(lk1));
			lk2.lock();
		}
		{
			srook::mutexes::includes::unique_lock<srook::mutex> lk1(m, srook::mutexes::includes::try_to_lock);
			srook::unique_lock<srook::mutex> lk2(srook::move(lk1));
			if (!lk2) {
				// ...
			}
		}
		{
			m.lock();
			srook::mutexes::includes::unique_lock<srook::mutex> lk1(m, srook::mutexes::includes::adopt_lock);
			srook::unique_lock<srook::mutex> lk2(srook::move(lk2));
		}
	}

	void timed() 
	{
		using namespace srook::mutexes::includes;

		{
			srook::unique_lock<srook::timed_mutex> lk(tm, srook::defer_lock);

			if (!lk.try_lock_for(chrono::seconds(3))) {
				// ...
			}
		}
		{
			srook::unique_lock<srook::timed_mutex> lk(tm, srook::defer_lock);

			if(!lk.try_lock_until(chrono::system_clock::now() + chrono::seconds(3))) {
				// ...
			}
		}
	}
}

void unique_lock_test()
{
	{
		srook::unique_lock<srook::mutex> lk1(m);
		srook::unique_lock<srook::mutex> lk2(srook::move(lk1));
	}
	{
		srook::unique_lock<srook::recursive_mutex> lk1(rm);
	}
	{
		srook::unique_lock<srook::timed_mutex> lk1(tm);
	}

	compatibility::basic();
	compatibility::lock_tags();
	compatibility::timed();
	
	{
		srook::unique_lock<srook::mutex> lk1(m), lk2;
		lk1.swap(lk2);
		std::swap(lk1, lk2);
	}
	{
		srook::unique_lock<srook::mutex> lk1(m, srook::defer_lock);
		assert(!lk1);
		lk1.lock();
		assert(lk1);
	}
	{
		srook::unique_lock<srook::mutex> lk1(m);
		srook::mutex* mptr = lk1.release();
		mptr->unlock();
	}
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS17_CONSTANT
	{
		srook::unique_lock lk1(m);
		srook::unique_lock lk2 = srook::move(lk1);
	}
#endif
}

int main()
{
	unique_lock_test();
}

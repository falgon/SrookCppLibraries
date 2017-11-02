#include <srook/mutex.hpp>
#include <iostream>

int main()
{
	using namespace srook::mutexes::includes;
		
	srook::timed_mutex m;
	m.lock();
	m.unlock();

	if (m.try_lock_for(chrono::seconds(3))) {
		m.unlock();
	} else {
		std::cerr << "time outed" << std::endl;
		return EXIT_FAILURE;
	}

	if (m.try_lock_until(chrono::system_clock::now() + chrono::seconds(3))) {
		m.unlock();
	} else {
		std::cerr << "time outed" << std::endl;
		return EXIT_FAILURE;
	}
}

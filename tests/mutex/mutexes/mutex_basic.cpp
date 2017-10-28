// #define SROOK_CONFIG_ENABLE_CPP03_IMPLICIT_MOVE_CONSTRUCTIBLE 1
#include <srook/mutex.hpp>
#include <srook/config/attribute/maybe_unused.hpp>

void mutex_test()
{
	srook::mutex m;

	m.lock();
	m.unlock();

	if(m.try_lock()) {
		m.unlock();
	}

	SROOK_ATTRIBUTE_UNUSED srook::mutex::native_handle_type mptr = m.native_handle();
}

int main()
{
	mutex_test();
}

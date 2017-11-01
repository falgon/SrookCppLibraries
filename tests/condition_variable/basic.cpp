// #define SROOK_CONFIG_ENABLE_CPP03_IMPLICIT_MOVE_CONSTRUCTIBLE 1
#include "detail/test_config.hpp"

typedef X test_type;

void basic()
{
	test_type x;

	thread th1(MEM_FN(&test_type::set_data1), REF(x));
	thread th2(MEM_FN(&test_type::wait_data1), REF(x));

	th1.join();
	th2.join();
}

void thread_exit()
{
	test_type x;

	thread th1(MEM_FN(&test_type::set_data2), REF(x));
	thread th2(MEM_FN(&test_type::wait_data1), REF(x));

	th1.join();
	th2.join();
}

void thread_wait_for()
{
	test_type x;

	thread th1(MEM_FN(&test_type::set_data1), REF(x));
	thread th2(MEM_FN(&test_type::wait_for), REF(x));

	th1.join();
	th2.join();
}

void thread_wait_until()
{
	test_type x;

	thread th1(MEM_FN(&test_type::set_data1), REF(x));
	thread th2(MEM_FN(&test_type::wait_until), REF(x));

	th1.join();
	th2.join();
}

int main()
{
	basic();
	thread_exit();
	thread_wait_for();
	thread_wait_until();
}

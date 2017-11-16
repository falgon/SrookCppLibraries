#include <iostream>
#include <srook/config/feature.hpp>
#include <srook/thread.hpp>
#include <srook/thread/safe/container/stack.hpp>
#include <srook/type_traits.hpp>

srook::mutex output_mtx;
typedef srook::thread_safe::container::stack<int>
    default_stack_type;
typedef srook::thread_safe::container::stack<int, std::deque<int>, srook::thread_safe::container::behavior::no_wait_pushed>
    nowait_stack_type;

template <class T>
void guard_print(T&& v)
{
    srook::lock_guard<srook::mutex> lk(output_mtx);
    std::cout << srook::forward<T>(v) << std::endl;
}

namespace pop_test {

default_stack_type st1;
nowait_stack_type st2;

SROOK_ST_ASSERT(
    (srook::type_traits::detail::Land<
        srook::is_same<
            decltype(st1), 
            srook::thread_safe::container::stack<int, std::deque<int>, srook::thread_safe::container::behavior::wait_pushed> 
        > 
     >::value));

void thread1()
{
    guard_print(__func__);
    srook::libraries::optional<int> opt = st1.pop(); // waits until pushed onto the stack.
    guard_print(opt.value_or(-1)); // only when aborted -1
}

void thread2()
{
    guard_print(__func__);
	guard_print("waiting 3 seconds...");
	srook::this_thread::sleep_for(srook::mutexes::includes::chrono::seconds(3));
    st1.push(42);
}

void thread3()
{
    guard_print(__func__);
    srook::libraries::optional<int> opt = st2.pop();
    guard_print(opt.value_or(-1)); // the result is always -1 because st2 is empty.
}

void exec1()
{
    srook::thread th1(thread1), th2(thread2);
    th1.join();
    th2.join();
}

void exec2()
{
    srook::thread th1(thread3);
    th1.join();
}
} // namespace pop_test

namespace top_test {

default_stack_type st1;
nowait_stack_type st2;

void thread4()
{
    guard_print(__func__);
    guard_print(st1.top()); // waits until pushed onto the stack
}

void thread5()
{
    guard_print(__func__);
	guard_print("waiting 3 seconds...");
	srook::this_thread::sleep_for(srook::mutexes::includes::chrono::seconds(3));
    st1.push(42);
}

void thread6()
{
    guard_print(__func__);
	if (!st2.empty()) st2.top(); // never exec this statement because st2 is empty
}

void exec1()
{
    srook::thread th1(thread4), th2(thread5);
    th1.join();
    th2.join();
}

void exec2()
{
	srook::thread th1(thread6);
	th1.join();
}

} // namespace top_test

namespace abort_test {

default_stack_type st1; // srook::thread_safe::container::stack::abort exists only when the type is 
// srook::thread_safe::container::stack<T, C, srook::thread_safe::container::behavior::wait_pushed>

void thread7()
{
	guard_print(__func__);
	try {
		st1.pop();
	} catch (const std::exception& e) {
		guard_print(e.what());
	}
}

void thread8()
{
	guard_print(__func__);
	guard_print("waiting 3 seconds... (after that will abort)");
	srook::this_thread::sleep_for(srook::mutexes::includes::chrono::seconds(3));
	st1.abort();
}

void exec1()
{
	srook::thread th1(thread7), th2(thread8);
	th1.join();
	th2.join();
}

} // namespace abort_test

namespace swap_test {

default_stack_type st1;
default_stack_type st2;

nowait_stack_type st3;
nowait_stack_type st4;

void thread9()
{
	guard_print(__func__);
	st1.push(42);
	st1.swap(st2);
	if (!st1.empty()) guard_print(st1.top()); // If this statement is executed, the value is always 53.
}

void thread10()
{
	guard_print(__func__);
	st2.push(53);
	guard_print(st2.top()); // 42 or 53
}

void thread11()
{
	guard_print(__func__);
	st3.push(42);
	st3.swap(st4);
	if (!st3.empty()) guard_print(st3.top()); // If this statement is executed, the value is always 53.
}

void thread12()
{
	guard_print(__func__);
	st4.push(53);
	guard_print(st4.top()); // 42 or 53
}

void exec1()
{
	srook::thread th1(thread9), th2(thread10);
	th1.join();
	th2.join();
}

void exec2()
{
	srook::thread th1(thread11), th2(thread12);
	th1.join();
	th2.join();
}

} // namespace swap

int main()
{
    pop_test::exec1();
    pop_test::exec2();
    
	top_test::exec1();
	top_test::exec2();

	abort_test::exec1();

	swap_test::exec1();
	swap_test::exec2();
}

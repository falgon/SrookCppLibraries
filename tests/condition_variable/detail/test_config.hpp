#ifndef INCLUDED_TEST_CONDITION_VARIABLE_DETAIL_TEST_CONFIG_HPP
#define INCLUDED_TEST_CONDITION_VARIABLE_DETAIL_TEST_CONFIG_HPP

#include <srook/condition_variable.hpp>
#include <srook/mutex.hpp>
#include <srook/config/feature/decltype.hpp>
#include <srook/config/libraries/optional.hpp>
#include <srook/config/feature/static_assert.hpp>
#include <srook/type_traits/true_false_type.hpp>
#include <srook/utility/void_t.hpp>
#include <thread>
#include <string>
#include <iostream>

#if SROOK_CPLUSPLUS < SROOK_CPLUSPLUS11_CONSTANT
#	include <boost/ref.hpp>
#endif

class X {
	srook::mutex m;
	srook::condition_variable cv;
	srook::libraries::optional<std::string> data_;
#if SROOK_CPLUSPLUS < SROOK_CPLUSPLUS11_CONSTANT
	struct Waiter {
		explicit Waiter(X* x) : x_(x) {}
		bool operator()() const 
		{
			return bool(x_->data_);
		}
	private:
		const X* const x_;
	};
#endif
public:
	void set_data1()
	{
		{
			srook::lock_guard<srook::mutex> lk(m);
			data_ = "ok";
		}
		cv.notify_one();
	}

	void set_data2()
	{
		srook::unique_lock<srook::mutex> lk(m);
		data_ = "ok";
		srook::notify_all_at_thread_exit(cv, srook::move(lk));
	}

	void wait_data1()
	{
		srook::unique_lock<srook::mutex> lk(m);
		cv.wait(lk, 
#if SROOK_CPLUSPLUS < SROOK_CPLUSPLUS11_CONSTANT
				Waiter(this)
#else
				[this] { return bool(data_); }
#endif
		);
		std::cout << data_.value_or("what") << std::endl;
	}

	void wait_for()
	{
		using namespace
#if SROOK_CPLUSPLUS < SROOK_CPLUSPLUS11_CONSTANT
			boost
#else
			std
#endif
			;

		srook::unique_lock<srook::mutex> lk(m);
		while (!data_) {
			srook::cv_status result = cv.wait_for(lk, chrono::seconds(3));
			if (result == srook::cv_status::timeout) {
				std::cerr << "timeout" << std::endl;
				return;
			}
		}
		std::cout << data_.value_or("what") << std::endl;
	}

	void wait_until()
	{
		using namespace
#if SROOK_CPLUSPLUS < SROOK_CPLUSPLUS11_CONSTANT
			boost
#else
			std
#endif
			;

		srook::unique_lock<srook::mutex> lk(m);
		while(!data_) {
			chrono::steady_clock::time_point tp = chrono::steady_clock::now() + chrono::seconds(3);
			srook::cv_status result = cv.wait_until(lk, tp);
			if (result == srook::cv_status::timeout) {
				std::cerr << "timeout" << std::endl;
				return ;
			}
		}
		std::cout << data_.value_or("what") << std::endl;
	}
};

#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
#	define MEM_FN std::mem_fn
#	define REF std::ref
#else
#	define MEM_FN std::mem_fun_ref
#	define REF boost::ref
#endif

	using
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
	std
#else
	boost
#endif
	::thread;

#endif

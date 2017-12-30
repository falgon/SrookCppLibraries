#define BOOST_TEST_MAIN
#include <boost/test/included/unit_test.hpp>
#include <srook/thread.hpp>
#include <srook/thread/safe/memory/singleton.hpp>
#include <srook/thread/safe/container/queue.hpp>
#include <srook/scope/unique_resource.hpp>
#include <vector>
#include <random>
#include <new>
#include <cassert>

struct dummy_resource {};

template <class T>
srook::unique_resource<dummy_resource, void (*)(dummy_resource)> make_destroyer() 
{
    return srook::make_unique_resource(dummy_resource{}, +[](dummy_resource){ T::destroy(); }); 
}

template <class T>
T linear_rand()
{
    static std::random_device seed_gen;
    static std::minstd_rand engine(seed_gen());
    static std::uniform_int_distribution<T> dist(srook::numeric_limits<T>::min(), srook::numeric_limits<T>::max());
    return dist(engine);
}

namespace ns {

srook::thread_safe::container::stack<int*, std::deque<int*>, srook::thread_safe::container::behavior::no_wait_pushed> sst;
srook::thread_safe::container::stack<int*, std::deque<int*>, srook::thread_safe::container::behavior::no_wait_pushed> smt;
std::size_t instance_counter = 0;

class instance_counter_resource : public srook::pmr::memory_resource {
protected:
    void* do_allocate(std::size_t bytes, std::size_t) override 
    { 
        ++instance_counter; // Exclusion control is not necessary because singleton already got the lock internally before this is called.
        return ::operator new(bytes); 
    }
    void do_deallocate(void* p, std::size_t, std::size_t) override { return ::operator delete(p); }
    bool do_is_equal(const srook::pmr::memory_resource::other_type& other) const noexcept override { return this == &other; }
};

SROOK_CONSTEXPR std::size_t max = 32;
typedef srook::thread_safe::memory::singleton_adaptor<srook::pmr::singleton<int>> safe_singleton;
typedef srook::thread_safe::memory::singleton_adaptor<srook::mayers_singleton<int>> safe_mayers_singleton; // It is thread-safe without wrapping with adapter.

void t1()
{
    srook::pmr::polymorphic_allocator<int> po(srook::pmr::new_delete_resource());
    for (std::size_t i = 0; i < max; ++i) sst.push(srook::addressof(safe_singleton::instance(po, 42)));
}

void t2()
{
    for (std::size_t i = 0; i < max; ++i) smt.push(srook::addressof(safe_mayers_singleton::instance(42)));
}

void t3()
{
    static instance_counter_resource icr;
    srook::pmr::polymorphic_allocator<int> po(&icr);
    for (std::size_t i = 0; i < max; ++i) {
        SROOK_ATTRIBUTE_UNUSED int& r = safe_singleton::instance(po, 42); // The member function `instance` has the nodiscard attribute specidied.
    }
}

} // namespace ns

BOOST_AUTO_TEST_SUITE(srsingleton_adaptor_test)

BOOST_AUTO_TEST_CASE(test1)
{
    assert(ns::sst.empty());
    assert(ns::smt.empty());

    const auto rs = make_destroyer<ns::safe_singleton>();
    srook::pmr::polymorphic_allocator<int> po(srook::pmr::new_delete_resource());
    int& r1 = ns::safe_singleton::instance(po, 42);
    BOOST_CHECK_EQUAL(r1, 42);

    int& r2 = ns::safe_mayers_singleton::instance(42);
    BOOST_CHECK_EQUAL(r2, 42);

    srook::thread th1(ns::t1), th2(ns::t1), th3(ns::t1), th4(ns::t1);
    srook::thread th5(ns::t2), th6(ns::t2), th7(ns::t2), th8(ns::t2);
    th1.join(); th2.join(); th3.join(); th4.join();
    th5.join(); th6.join(); th7.join(); th8.join();

    while (!ns::sst.empty()) {
        BOOST_CHECK_EQUAL(ns::sst.top(), &r1);
        ns::sst.pop();

        BOOST_CHECK_EQUAL(ns::smt.top(), &r2);
        ns::smt.pop();
    }
}

BOOST_AUTO_TEST_CASE(test2)
{
    assert(ns::sst.empty());
    assert(ns::smt.empty());

    const auto rs = make_destroyer<ns::safe_singleton>();

    srook::thread th1(ns::t1), th2(ns::t1), th3(ns::t1), th4(ns::t1);
    srook::thread th5(ns::t2), th6(ns::t2), th7(ns::t2), th8(ns::t2);
    th1.join(); th2.join(); th3.join(); th4.join();
    th5.join(); th6.join(); th7.join(); th8.join();

    while (!ns::sst.empty()) {
        {
            int* dp = ns::sst.top();
            ns::sst.pop();
            if (!ns::sst.empty()) BOOST_CHECK_EQUAL(dp, ns::sst.top());
        }
        {
            int* dp = ns::smt.top();
            ns::smt.pop();
            if (!ns::smt.empty()) BOOST_CHECK_EQUAL(dp, ns::smt.top());
        }
    }   
}

BOOST_AUTO_TEST_CASE(test3)
{
    const auto rs = make_destroyer<ns::safe_singleton>();
    srook::thread th1(ns::t3), th2(ns::t3), th3(ns::t3), th4(ns::t3);
    th1.join(); th2.join(); th3.join(); th4.join();   
    BOOST_CHECK_EQUAL(ns::instance_counter, 1);
}

BOOST_AUTO_TEST_SUITE_END()

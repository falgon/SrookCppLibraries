#define BOOST_TEST_MAIN
#define SROOK_CONFIG_SUPURESS_VARIADIC_MACROS_WARNING 1
#include <boost/test/included/unit_test.hpp>
#include <boost/range/algorithm/equal.hpp>
#include <srook/scope/unique_resource.hpp>
#include <srook/memory_resource.hpp>
#include <srook/type_traits.hpp>
#include <srook/limits/numeric_limits.hpp>
#include <vector>
#include <random>
#include <srook/memory/singleton.hpp>

BOOST_AUTO_TEST_SUITE(srsingleton_test)

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

BOOST_AUTO_TEST_CASE(singleton_check1)
{
    typedef srook::singleton<int> int_singleton;
    const auto dest = make_destroyer<int_singleton>(); // for exception safety

    auto& i = int_singleton::instance(linear_rand<SROOK_DEDUCED_TYPENAME int_singleton::value_type>());
    auto& j = int_singleton::instance(linear_rand<SROOK_DEDUCED_TYPENAME int_singleton::value_type>());
    BOOST_CHECK_EQUAL(&i, &j);
    BOOST_CHECK_EQUAL(i, j);
}

BOOST_AUTO_TEST_CASE(singleton_check2)
{
    typedef srook::singleton<std::vector<int>> vec_singleton;
    const auto dest = make_destroyer<vec_singleton>(); // for exception safety
   
    SROOK_CONSTEXPR std::size_t size = 4;
    const auto init_value = linear_rand<SROOK_DEDUCED_TYPENAME vec_singleton::value_type::value_type>();
    auto& v1 = vec_singleton::instance(size, init_value);
    auto& v2 = vec_singleton::instance(size, linear_rand<SROOK_DEDUCED_TYPENAME vec_singleton::value_type::value_type>());

    std::vector<SROOK_DEDUCED_TYPENAME vec_singleton::value_type::value_type> check_v(size, init_value);

    BOOST_CHECK_EQUAL(v1.size(), size);
    BOOST_TEST(boost::equal(v1, check_v));
    BOOST_TEST(boost::equal(v1, v2));
    BOOST_CHECK_EQUAL(&v1, &v2);
}

BOOST_AUTO_TEST_CASE(singleton_check3)
{
    typedef srook::pmr::singleton<int> pmr_int_singleton;
    const auto dest = make_destroyer<pmr_int_singleton>(); // for exception safety
    
    srook::pmr::polymorphic_allocator<int> po(srook::pmr::get_default_resource());
    auto& i = pmr_int_singleton::instance(po, linear_rand<SROOK_DEDUCED_TYPENAME pmr_int_singleton::value_type>());
    auto& j = pmr_int_singleton::instance(linear_rand<SROOK_DEDUCED_TYPENAME pmr_int_singleton::value_type>());

    BOOST_CHECK_EQUAL(i, j);
    BOOST_CHECK_EQUAL(&i, &j);
}

BOOST_AUTO_TEST_CASE(singleton_check4)
{
    typedef srook::pmr::singleton<int> pmr_int_singleton;
    const auto dest = make_destroyer<pmr_int_singleton>(); // for exception safety

    srook::pmr::polymorphic_allocator<int> po(srook::pmr::null_memory_resource());

    try {
        SROOK_ATTRIBUTE_UNUSED auto& i = pmr_int_singleton::instance(po, linear_rand<SROOK_DEDUCED_TYPENAME pmr_int_singleton::value_type>()); // always throw std::bad_alloc
    } catch (const std::bad_alloc&) {}
}

BOOST_AUTO_TEST_SUITE_END()

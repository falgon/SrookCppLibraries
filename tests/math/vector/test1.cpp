#define BOOST_TEST_MAIN
#include <boost/test/included/unit_test.hpp>
#include <srook/math/vector.hpp>
#include <srook/type_traits/is_same.hpp>
#include <srook/type_traits/detail/logical.hpp>
#include <srook/type_traits/decay.hpp>
#include <srook/tmpl/vt/map.hpp>
#include <srook/math/constants/algorithm/abs.hpp>

BOOST_AUTO_TEST_SUITE(srook_math_vector_test)

BOOST_AUTO_TEST_CASE(vector_construct)
{
    srook::math::vector<int, double> vec0;
    SROOK_ST_ASSERT(std::tuple_size<SROOK_DECLTYPE(vec0)>::value == 2);
    SROOK_ST_ASSERT(srook::type_traits::detail::Land<
        srook::is_same<SROOK_DEDUCED_TYPENAME std::tuple_element<0, SROOK_DECLTYPE(vec0)>::type, int>, srook::is_same<SROOK_DEDUCED_TYPENAME std::tuple_element<1, SROOK_DECLTYPE(vec0)>::type, double>
    >::value);
    BOOST_CHECK_EQUAL(vec0.get<0>(), 0);
    BOOST_CHECK_EQUAL(vec0.get<1>(), 0.0);

    constexpr auto vec1 = 
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS17_CONSTANT
        srook::math::vector(1, 2.f, 3.0)
#else
        srook::math::make_vector(1, 2.f, 3.0)
#endif
        ;
    SROOK_ST_ASSERT(srook::is_same<SROOK_DECLTYPE(vec1), const srook::math::vector<int, float, double>>::value);
    SROOK_ST_ASSERT(vec1.get<0>() == 1);
    SROOK_ST_ASSERT(vec1.get<1>() == 2.f);
    SROOK_ST_ASSERT(vec1.get<2>() == 3.0);
    SROOK_ST_ASSERT(srook::tmpl::vt::and_<SROOK_DEDUCED_TYPENAME srook::tmpl::vt::map<srook::is_equality_comparable, srook::tmpl::vt::packer<SROOK_DECLTYPE(vec0), SROOK_DECLTYPE(vec1)>>::type>::value);
}

BOOST_AUTO_TEST_CASE(vector_copy_construct)
{
    constexpr auto vec0 = srook::math::make_vector(1, 2.f, 3.0);
    constexpr auto vec1 = vec0;
    SROOK_ST_ASSERT(srook::is_same<SROOK_DECLTYPE(vec0), SROOK_DECLTYPE(vec1)>::value);
    SROOK_ST_ASSERT(vec0 == vec1);
}

BOOST_AUTO_TEST_CASE(vector_assign)
{
    constexpr auto vec0 = srook::math::make_vector(1, 2.f);
    srook::math::vector<int, float> vec1;
    vec1 = vec0;
    BOOST_CHECK_EQUAL(vec0, vec1);
}

BOOST_AUTO_TEST_CASE(vector_length_equality)
{
    typedef srook::numeric_limits<srook::floatmax_t> result_float;
    auto vec0 = srook::math::make_vector(4.0, 3.0);
    BOOST_TEST(srook::math::abs(vec0.length() - 5) < result_float::epsilon());
    SROOK_ST_ASSERT(srook::math::abs(srook::math::make_vector(12, 5).length() - 13) < result_float::epsilon());
    SROOK_ST_ASSERT(srook::math::abs(srook::math::make_vector(8, 15).length() - 17) < result_float::epsilon());
    
    BOOST_TEST(!vec0.is_unit());
    if (vec0.normalize()) { // When vec0.length() == 0, it returns false.
        BOOST_TEST(vec0.is_unit());
        BOOST_TEST(srook::math::abs(vec0.get<0>() - 0.8) < srook::numeric_limits<double>::epsilon());
        BOOST_TEST(srook::math::abs(vec0.get<1>() - 0.6) < srook::numeric_limits<double>::epsilon());
    }
    srook::math::make_vector(4.0, 3.0).get_normalized<double>() >>= [](const auto& normalized_vec) { // When vec0.length() == 0, it returns nullopt. Otherwise, it returns optional<vector<...>>.
        BOOST_CHECK_EQUAL(normalized_vec, srook::math::make_vector(0.8, 0.6)); // This equivalence is handled appropriately about floating error.
        return srook::make_optional(normalized_vec);
    };
}

BOOST_AUTO_TEST_CASE(vector_dot_product)
{
    SROOK_ST_ASSERT(!srook::math::make_vector(3, 5).dot_product(5, -3));
    SROOK_ST_ASSERT(srook::math::make_vector(1, 2).dot_product(3, 4) == 11);
    SROOK_ST_ASSERT(srook::math::make_vector(1, 2).dot_product(-2, 3) == 4);
}

BOOST_AUTO_TEST_CASE(vector_cross_product)
{
    SROOK_ST_ASSERT(srook::math::make_vector(1, 2, 3).cross_product(4, 5, 6) == srook::math::make_vector(-3, 6, -3));
}

BOOST_AUTO_TEST_CASE(vector_projection)
{
    SROOK_ST_ASSERT(srook::math::make_vector(1.f, 2.f, 2.f).projection(4.f, 0.f, 3.f) == srook::math::make_vector(1.6f, .0f, 1.2f));
}

BOOST_AUTO_TEST_CASE(vector_perpendicular)
{
    SROOK_ST_ASSERT(srook::math::make_vector(1.f, 2.f, 2.f).perpendicular(4.f, 0.f, 3.f) == srook::math::make_vector(-0.6f, 2.f, .8f));
}

BOOST_AUTO_TEST_SUITE_END()

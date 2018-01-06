#define BOOST_TEST_MAIN
#include <boost/test/included/unit_test.hpp>
#include <boost/range/algorithm/fill.hpp>
#include <srook/cstring/memcpy.hpp>
#include <srook/cstring/avx/has_intel_knl_features.hpp>

BOOST_AUTO_TEST_SUITE(avx512_test)

BOOST_AUTO_TEST_CASE(avx512_test1)
{
    char s[2][256]{};
    boost::fill(s[1], 'a');
    srook::cstring::memcpy(s[0], s[1], 256);
    BOOST_TEST(boost::equal(s[0], s[1]));
}

BOOST_AUTO_TEST_CASE(avx512_test2)
{
    using namespace srook::cstring::avx;
#if defined(SROOK_CONFIG_ENABLE_AVX512_MEMCPY) && defined(__AVX512F__)
    BOOST_TEST(has_intel_knl_features())
#else
    BOOST_TEST(!has_intel_knl_features())
#endif
    ;
}

BOOST_AUTO_TEST_SUITE_END()

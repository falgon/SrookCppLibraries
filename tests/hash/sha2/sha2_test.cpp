#define BOOST_TEST_MAIN
#define SROOK_CONFIG_ENABLE_PMR_PRIORITY 1
#include <boost/test/included/unit_test.hpp>
#include <boost/range/algorithm/equal.hpp>
#include <srook/hash/sha2.hpp>
#include <srook/thread.hpp>
#include <vector>

BOOST_AUTO_TEST_SUITE(srook_hash_sha_tests)

namespace detail {

const std::string test1 = "abc";
const std::string test2 = "";

template <std::size_t, std::size_t = 0> 
struct validated_value;

template <>
struct validated_value<224> {
    static SROOK_CONSTEXPR const char* value1= "23097d223405d8228642a477bda255b32aadbce4bda0b3f7e36c9da7";
    static SROOK_CONSTEXPR const char* value2 = "d14a028c2a3a2bc9476102bb288234c415a2b01f828ea62ac5b3e42f";
};

template <>
struct validated_value<256> {
    static SROOK_CONSTEXPR const char* value1 = "ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad";
    static SROOK_CONSTEXPR const char* value2 = "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855";
};

template <>
struct validated_value<384> {
    static SROOK_CONSTEXPR const char* value1 = 
        "cb00753f45a35e8bb5a03d699ac65007272c32ab0eded1631a8b605a43ff5bed"
        "8086072ba1e7cc2358baeca134c825a7";
    static SROOK_CONSTEXPR const char* value2 = 
        "38b060a751ac96384cd9327eb1b1e36a21fdb71114be07434c0cc7bf63f6e1da"
        "274edebfe76f65fbd51ad2f14898b95b";
};

template <>
struct validated_value<512, 0> {
    static SROOK_CONSTEXPR const char* value1 = 
        "ddaf35a193617abacc417349ae20413112e6fa4e89a97ea20a9eeee64b55d39a"
        "2192992a274fc1a836ba3c23a3feebbd454d4423643ce80e2a9ac94fa54ca49f";
    static SROOK_CONSTEXPR const char* value2 =
        "cf83e1357eefb8bdf1542850d66d8007d620e4050b5715dc83f4a921d36ce9ce"
        "47d0d13c5d85f2b0ff8318d2877eec2f63b931bd47417a81a538327af927da3e";
};

template <>
struct validated_value<512, 224> {
    static SROOK_CONSTEXPR const char* value1 =
        "4634270f707b6a54daae7530460842e20e37ed265ceee9a43e8924aa";
    static SROOK_CONSTEXPR const char* value2 = 
        "6ed0dd02806fa89e25de060c19d3ac86cabb87d6a0ddd05c333b84f4";
};

template <>
struct validated_value<512, 256> {
    static SROOK_CONSTEXPR const char* value1 = 
        "53048e2681941ef99b2e29b76b4c7dabe4c2d0c634fc6d46e0e2f13107e7af23";
    static SROOK_CONSTEXPR const char* value2 = 
        "c672b8d1ef56ed28ab87c3622c5114069bdd3ad7b8f9737498d0c01ecef0967a";
};

template <std::size_t x, std::size_t y = 0>
void tester1()
{
    using namespace detail;
    typedef srook::hash::sha2<x, y> sha2_type;
    sha2_type sha2_hash1(srook::begin(test1), srook::end(test1));
    sha2_type sha2_hash2(srook::begin(test2), srook::end(test2));
    
    {
        std::string result1 = sha2_hash1.str();
        std::string result2 = sha2_hash2.str();
#ifdef __GNUC__ 
#   if __GNUC_MINOR__ <= 2 && __GNUC_PATCHLEVEL__ <= 0 && __GNUC__ <= 7

        srook::pmr::string result3 = sha2_hash1.pmr_str(srook::pmr::new_delete_resource());
        srook::pmr::polymorphic_allocator<srook::pmr::string::value_type> pa(srook::pmr::get_default_resource());
        srook::pmr::string result4 = sha2_hash2.pmr_str(pa);
#   endif
#endif

        BOOST_CHECK_EQUAL(result1, (validated_value<x, y>::value1));
        BOOST_CHECK_EQUAL(result2, (validated_value<x, y>::value2));
#ifdef __GNUC__
#   if __GNUC_MINOR__ <= 2 && __GNUC_PATCHLEVEL__ <= 0 && __GNUC__ <= 7
        BOOST_CHECK_EQUAL(result3, (validated_value<x, y>::value1));
        BOOST_CHECK_EQUAL(result4, (validated_value<x, y>::value2));
#   endif
#endif
    }
    {
        auto result = sha2_hash1(); // byte code
        SROOK_ST_ASSERT((
            srook::is_same<
                SROOK_DECLTYPE(result), 
                srook::array<SROOK_DEDUCED_TYPENAME sha2_type::value_type, sha2_type::message_digest_size>
            >::value
        ));
        BOOST_CHECK_EQUAL(result.size(), sha2_type::message_digest_size);
    }
    {
        std::vector<SROOK_DEDUCED_TYPENAME sha2_type::value_type> ar(sha2_type::message_digest_size);
        sha2_hash1(ar); // byte copy
        sha2_hash1(ar, SROOK_DEDUCED_TYPENAME sha2_type::to_character()); // string
        BOOST_TEST(boost::equal(ar, std::string(validated_value<x, y>::value1)));
    }
    {
        typedef srook::hash::sha2<x, y, std::vector<char>::iterator> sha2_vec_type;
        std::vector<char> v(srook::begin(test1), srook::end(test1));
        sha2_vec_type vecsha(srook::begin(v), srook::end(v));
        BOOST_CHECK_EQUAL(vecsha.str(), (validated_value<x, y>::value1));
    }
}

template <std::size_t x, std::size_t y = 0>
void tester2()
{
    using namespace detail;
    typedef srook::hash::sha2<x, y> sha2_type;    
    sha2_type sha2_hash(srook::begin(test1), srook::end(test1));

    std::string s1, s2;
    const auto lam = [](const sha2_type& sha, std::string& s) { s.assign(sha.str()); };
    srook::thread th1(lam, std::cref(sha2_hash), std::ref(s1)), th2(lam, std::cref(sha2_hash), std::ref(s2));
    th1.join(); th2.join();
    BOOST_CHECK_EQUAL(s1, s2); // never interleaving
    BOOST_CHECK_EQUAL(s1, (validated_value<x, y>::value1));
}

template <std::size_t x, std::size_t y = 0>
void tester3()
{
    using namespace detail;
    {
        auto r = srook::hash::make_sha2<x, y>(srook::begin(test1), srook::end(test1));
        BOOST_CHECK_EQUAL(r.str(), (validated_value<x, y>::value1));
    }
    {
        auto r = srook::hash::make_sha2<x, y>(test1);
        BOOST_CHECK_EQUAL(r.str(), (validated_value<x, y>::value1));
    }
    {
        srook::hash::sha2<x, y> r(test1);
        BOOST_CHECK_EQUAL(r.str(), (validated_value<x, y>::value1));
    }
}

void tester4()
{
    using namespace srook::hash::hash_literals;
    auto r224 = "abc"_sha224;
    BOOST_CHECK_EQUAL(r224.str(), (validated_value<224>::value1));

    auto r256 = "abc"_sha256;
    BOOST_CHECK_EQUAL(r256.str(), (validated_value<256>::value1));

    auto r384 = "abc"_sha384;
    BOOST_CHECK_EQUAL(r384.str(), (validated_value<384>::value1));

    auto r512 = "abc"_sha512;
    BOOST_CHECK_EQUAL(r512.str(), (validated_value<512>::value1));

    auto r512_224 = "abc"_sha512_224;
    BOOST_CHECK_EQUAL(r512_224.str(), (validated_value<512, 224>::value1));

    auto r512_256 = "abc"_sha512_256;
    BOOST_CHECK_EQUAL(r512_256.str(), (validated_value<512, 256>::value1));
}

template <std::size_t x, std::size_t y = 0>
void tester5()
{
    srook::hash::sha2<x, y> r(test1);
    BOOST_CHECK_EQUAL(r.str(), (validated_value<x, y>::value1));

    const auto f = [](auto& sha) { 
        sha.assign(test2); // == sha.assign(srook::begin(test2), srook::end(test2))
        BOOST_CHECK_EQUAL(sha.str(), (validated_value<x, y>::value2));
    };
    srook::thread th1(f, std::ref(r)), th2(f, std::ref(r));
    th1.join(); th2.join();
}

template <std::size_t x, std::size_t y = 0>
void invoke_tester()
{
    tester1<x, y>();
    tester2<x, y>();
    tester3<x, y>();
}

} // namespace detail

BOOST_AUTO_TEST_CASE(srook_hash_sha224_test)
{
    using namespace detail;
    invoke_tester<224>();
}

BOOST_AUTO_TEST_CASE(srook_hash_sha256_test)
{
    using namespace detail;
    invoke_tester<256>();
}

BOOST_AUTO_TEST_CASE(srook_hash_sha384_test)
{
    using namespace detail;
    invoke_tester<384>();
}

BOOST_AUTO_TEST_CASE(srook_hash_sha512_test)
{
    using namespace detail;
    invoke_tester<512>();
}

BOOST_AUTO_TEST_CASE(srook_hash_sha512_224_test)
{
    using namespace detail;
    invoke_tester<512, 224>();
}

BOOST_AUTO_TEST_CASE(srook_hash_sha512_256_test)
{
    using namespace detail;
    invoke_tester<512, 256>();
}

BOOST_AUTO_TEST_CASE(srook_hash_literals_test)
{
    using namespace detail;
    tester4();
}

BOOST_AUTO_TEST_SUITE_END()

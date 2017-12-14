#define BOOST_TEST_MAIN
#include <boost/test/included/unit_test.hpp>
#include <srook/expected/expected.hpp>
#include <srook/string/string_view.hpp>

BOOST_AUTO_TEST_SUITE(srexpected_test)

BOOST_AUTO_TEST_CASE(expected1)
{
    srook::expected<int, std::error_code> e;
    BOOST_TEST(!e.any_valid());
    
    e.emplace(42);
    BOOST_TEST((e.any_valid() && e.valid() && e.has_value() && bool(e)));
    BOOST_CHECK_EQUAL(*e, 42);
    BOOST_CHECK_EQUAL(e.value(), 42);

    e.emplace(std::error_code(static_cast<int>(std::errc::invalid_argument), std::generic_category()));
    BOOST_TEST((e.any_valid() && !e.valid() && !e.has_value() && !bool(e)));
    BOOST_CHECK_EQUAL(e.error().value(), static_cast<int>(std::errc::invalid_argument));

    e.reset();
    BOOST_TEST((!e.any_valid() && !e.valid() && !e.has_value() && !bool(e)));

    try {
        e.value(); // throw srook::exception::bad_expected_access
    } catch (const std::exception& exp) {
        BOOST_TEST(!srook::string_view(exp.what()).compare("bad expected access"));
    }
}

BOOST_AUTO_TEST_CASE(expected2)
{
    srook::expected<int, std::error_code> e1{42};
    BOOST_TEST((e1.any_valid() && e1.valid() && e1.has_value() && bool(e1)));
    BOOST_CHECK_EQUAL(*e1, 42);
    BOOST_CHECK_EQUAL(e1.value(), 42);
#if 0
    e1.error(); // assertation and abort
#endif
    srook::expected<int, std::error_code> e2{std::error_code(static_cast<int>(std::errc::invalid_argument), std::generic_category())};
    BOOST_TEST((e2.any_valid() && !e2.valid() && !e2.has_value() && !bool(e2)));
    BOOST_CHECK_EQUAL(e2.error().value(), static_cast<int>(std::errc::invalid_argument));
}

BOOST_AUTO_TEST_CASE(expected3)
{
    srook::expected<int, std::error_code> e{std::error_code(static_cast<int>(std::errc::invalid_argument), std::generic_category())};
    try {
        e.value(); // throw std::error_code
    } catch (const std::error_code& er) {
        BOOST_CHECK_EQUAL(er.value(), static_cast<int>(std::errc::invalid_argument));
    }

    e = 42;
    BOOST_TEST(bool(e));
    BOOST_CHECK_EQUAL(*e, 42);

    e.emplace(std::error_code(static_cast<int>(std::errc::invalid_argument), std::generic_category()));
    BOOST_TEST((!bool(e) && e.any_valid()));
    BOOST_CHECK_EQUAL(e.error().value(), static_cast<int>(std::errc::invalid_argument));
}

BOOST_AUTO_TEST_CASE(expected4)
{
    srook::expected<int> e;

    SROOK_ST_ASSERT((srook::is_same<SROOK_DEDUCED_TYPENAME SROOK_DECLTYPE(e)::value_type, int>::value));
    SROOK_ST_ASSERT((srook::is_same<SROOK_DEDUCED_TYPENAME SROOK_DECLTYPE(e)::error_type, std::exception_ptr>::value));

    try {
        SROOK_THROW std::runtime_error("test_error");
    } catch (...) {
        e = std::current_exception();
    }

    try {
        e.value(); // std::rethrow_exception is called internally
    } catch (const std::exception& ex) {
        BOOST_TEST(!srook::string_view(ex.what()).compare("test_error"));
    }
}

BOOST_AUTO_TEST_CASE(expected5)
{
    auto f = [](int x){ return srook::make_expected<int, std::error_code>(x); };
    auto g = [](int){ return srook::make_unexpected(std::error_code(static_cast<int>(std::errc::invalid_argument), std::generic_category())); };

    int a = 42;
    auto e = f(a) >>= [=](int x) {
        return f(x) >>= [=](int y) {
            return f(y) >>= [=](int z) {
                return g(z) >>= [=](int aa) {
                    return srook::make_expected<int, std::error_code>(aa);  
                };  
            };  
        };    
    };
    BOOST_CHECK_EQUAL(e.error().value(), static_cast<int>(std::errc::invalid_argument));

    e = f(a) >>= [=](int x) {
        return f(x) >>= [=](int y) {
            return f(y) >>= [=](int z) {
                return f(z);
            };
        };
    };
    BOOST_CHECK_EQUAL(e.value(), 42);
}

BOOST_AUTO_TEST_CASE(expected6)
{
    srook::expected<int> e1 = 42, e2 = 53;
    e1.swap(e2);
    BOOST_CHECK_EQUAL(*e2, 42);
    BOOST_CHECK_EQUAL(*e1, 53);
    BOOST_TEST((bool(e1) && bool(e2)));

    e1.reset();
    e1.swap(e2);
    BOOST_CHECK_EQUAL(*e1, 42);
    BOOST_TEST(!bool(e2));

    e1.swap(e2);
    BOOST_TEST(!bool(e1));
    BOOST_CHECK_EQUAL(*e2, 42);
}

BOOST_AUTO_TEST_SUITE_END()

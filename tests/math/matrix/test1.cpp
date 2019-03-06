#define BOOST_TEST_MAIN
#include <boost/test/included/unit_test.hpp>
#include <srook/math/matrix.hpp>

BOOST_AUTO_TEST_SUITE(srook_math_matrix_test)

namespace sm = srook::math;
namespace stv = srook::tmpl::vt;

BOOST_AUTO_TEST_CASE(matrix_construct)
{
    typedef sm::row<int, int> r2;
    typedef stv::transfer_t<sm::matrix, stv::replicate_t<2, stv::transfer_t<sm::row, stv::replicate_t<2, int>>>> mtx2x2_int; // 2 x 2, int matrix type

    constexpr mtx2x2_int m1 {
       r2{ 1, 3 },
       r2{ 4, 2 }
    };
    SROOK_ATTRIBUTE_UNUSED constexpr auto m2 = m1;

    constexpr mtx2x2_int m3 { // initialized as like the above.
        1, 3,
        4, 2
    };
    SROOK_ST_ASSERT(m1 == m2 && m1 == m3);
}

/*

int main()
{
    constexpr srook::math::matrix<
        srook::math::row<int, int, int, int>,
        srook::math::row<int, int, int, int>,
        srook::math::row<int, int, int, int>,
        srook::math::row<int, int, int, int>
    > m1 {
        1, 2, 7, 6,
        2, 4, 4, 2,
        1, 8, 5, 2,
        2, 4, 3, 3
    };

    constexpr auto res = m1.compute_equations(srook::math::make_vector(6, 2, 12, 5), srook::math::gaussian_elimination_eq());
    std::cout << res << std::endl;

    constexpr srook::math::matrix<
        srook::math::row<int, int, int>,
        srook::math::row<int, int, int>,
        srook::math::row<int, int, int>
    > m2 {
        2, 2, 1,
        3, 0, 2,
        4, 3, 2
    };
    constexpr auto inv = m2.inverse();
    std::cout << inv << std::endl;

    constexpr auto det = m2.determinant();
    std::cout << det << std::endl;
}*/

BOOST_AUTO_TEST_SUITE_END()

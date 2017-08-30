// Copyright (C) 2017 roki
//
// This is a mandelbrot fractal ploter by C++ template MetaProgramming. 
// However, this ploter unfortunately DOES NOT work on practial machines, because it needs huge amount of memories.
// Therefore, this ploter is ornamental.
//
//

#include <srook/config/cpp_predefined/feature_testing.hpp>
#include <srook/math/constants/algorithm/pow.hpp>
#include <srook/mpl/constant_sequence/algorithm/explicit_concat.hpp>
#include <srook/mpl/variadic_player.hpp>
#include <srook/type_traits/any_constant.hpp>
#include <srook/type_traits/enable_if.hpp>
#include <srook/type_traits/true_false_type.hpp>

namespace srook {
inline namespace mpl {
namespace fractal {
inline namespace v1 {
namespace detail {

template <class, class,
	  class = any_constant<double, 0, realvalue_compute::convert_type<double>>,
	  class = any_constant<double, 0, realvalue_compute::convert_type<double>>,
	  std::size_t = 0, std::size_t = 1000, class = SROOK_NULLPTR_T>
struct is_mandelbrot;

template <class AA, class BB>
struct Checkpower
    : std::conditional<(math::pow(AA::value, AA::value) + math::pow(BB::value, BB::value) > 10), std::true_type, std::false_type> {
};

template <class AnyConstant_x, class AnyConstant_y, class AnyConstant_a, class AnyConstant_b, std::size_t i, std::size_t last>
struct is_mandelbrot<AnyConstant_x, AnyConstant_y, AnyConstant_a, AnyConstant_b, i, last, typename enable_if<(i < last), SROOK_NULLPTR_T>::type> {
private:
    typedef
	typename realvalue_compute::Plus<
	    typename realvalue_compute::Minus<
		typename realvalue_compute::Multiplies<AnyConstant_a, AnyConstant_a>::type,
		typename realvalue_compute::Multiplies<AnyConstant_b, AnyConstant_b>::type>::type,
	    AnyConstant_x>::type
	    AA_type;

    typedef
	typename realvalue_compute::Plus<
	    typename realvalue_compute::Multiplies<
		any_constant<double, 2, realvalue_compute::convert_type<double>>,
		typename realvalue_compute::Multiplies<AnyConstant_a, AnyConstant_b>::type>::type,
	    AnyConstant_y>::type
	    BB_type;

    static constexpr double aa = AA_type::value;
    static constexpr double bb = BB_type::value;
public:
    typedef
	typename std::conditional<
	    ((srook::math::pow(aa,aa)) + (srook::math::pow(bb,bb)) > 10),
	    SROOK_TRUE_TYPE,
	    typename is_mandelbrot<AnyConstant_x, AnyConstant_y, AA_type, BB_type, (i + 1), last>::type>::type
	    type;

    static constexpr bool value = type::value;
};

template <class AnyConstant_x, class AnyConstant_y, class AnyConstant_a, class AnyConstant_b, std::size_t i, std::size_t last>
struct is_mandelbrot<AnyConstant_x, AnyConstant_y, AnyConstant_a, AnyConstant_b, i, last, typename enable_if<!(i < last), SROOK_NULLPTR_T>::type> {
    typedef SROOK_FALSE_TYPE type;
    static constexpr bool value = type::value;
};

template <class, class, class, class = SROOK_NULLPTR_T>
struct mandelbrot_impl2;
template <class AnyConstant_r, class AnyConstant_i, class AnyConstant_diff>
struct mandelbrot_impl2<AnyConstant_r, AnyConstant_i, AnyConstant_diff, typename srook::enable_if<(AnyConstant_i::value < 1), SROOK_NULLPTR_T>::type> {
    typedef
	typename Concat<
	    typename std::conditional<
		is_mandelbrot<AnyConstant_r, AnyConstant_i>::value,
		pack<AnyConstant_r, AnyConstant_i>,
		pack<>>::type,
	    typename mandelbrot_impl2<AnyConstant_r, typename realvalue_compute::Plus<AnyConstant_i, AnyConstant_diff>::type, AnyConstant_diff>::type>::type
	    type;
};
template <class AnyConstant_r, class AnyConstant_i, class AnyConstant_diff>
struct mandelbrot_impl2<AnyConstant_r, AnyConstant_i, AnyConstant_diff, typename srook::enable_if<!(AnyConstant_i::value < 1), SROOK_NULLPTR_T>::type> {
    typedef pack<> type;
};

template <class, class, class, class = SROOK_NULLPTR_T>
struct mandelbrot_impl1;
template <class AnyConstant_r, class AnyConstant_i, class AnyConstant_diff>
struct mandelbrot_impl1<AnyConstant_r, AnyConstant_i, AnyConstant_diff, typename srook::enable_if<(AnyConstant_r::value < 1), SROOK_NULLPTR_T>::type> {
    typedef
	typename Concat<
	    typename mandelbrot_impl2<AnyConstant_r, AnyConstant_i, AnyConstant_diff>::type,
	    typename mandelbrot_impl1<typename realvalue_compute::Plus<AnyConstant_r, AnyConstant_diff>::type, AnyConstant_i, AnyConstant_diff>::type>::type
	    type;
};
template <class AnyConstant_r, class AnyConstant_i, class AnyConstant_diff>
struct mandelbrot_impl1<AnyConstant_r, AnyConstant_i, AnyConstant_diff, typename srook::enable_if<!(AnyConstant_r::value < 1), SROOK_NULLPTR_T>::type> {
    typedef pack<> type;
};

} // namespace detail

template <
    class R = any_constant<double, -2, realvalue_compute::convert_type<double>>,
    class I = any_constant<double, -1, realvalue_compute::convert_type<double>>,
    class Diff = any_constant<double, 5, realvalue_compute::Divides_value<double, int, 10>>>
struct mandelbrot {
    typedef typename detail::mandelbrot_impl1<R, I, Diff>::type type;
};

#if SROOK_CPP_ALIAS_TEMPLATES
template <
    class R = any_constant<double, -2, realvalue_compute::convert_type<double>>,
    class I = any_constant<double, -1, realvalue_compute::convert_type<double>>,
    class Diff = any_constant<double, 5, realvalue_compute::Divides_value<double, int, 1000>>>
using mandelbrot_t = typename mandelbrot<R, I, Diff>::type;
#endif

} // namespace v1
} // namespace fractal
} // namespace mpl
} // namespace srook

#include <iostream>
#include <srook/mpl/variadic_types/algorithm/unwrap_pack_from_value.hpp>

int main()
{
    using type = srook::fractal::mandelbrot_t<>;
    constexpr auto a = srook::unwrap_costable::array<type>::value;
    for (auto &&v : a) std::cout << v << " ";
	std::cout << '\n';
}

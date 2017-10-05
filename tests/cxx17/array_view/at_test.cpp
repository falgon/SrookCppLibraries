#include "array_view_test.hpp"
ARRAY_VIEW_TEST

using namespace srook;

template <class T, class... Ts>
struct is_all_same : std::bool_constant<conjunction_v<is_same<T, Ts>...>> {};

constexpr void at_test1()
{
	using at_type = test_type1::at_type<0>;

	static_assert(
			is_all_same<
				add_const_t<test_type1::element_type>, 
				test_type1::result_type, 
				decltype(at_type::value),
				decltype(test_type1::at_v<0>),
				add_const_t<decltype(test_type1::at(integral_constant<int, 0>()))>,
				add_const_t<decltype(test_type1().instance_at(integral_constant<int, 0>()))>,
				add_const_t<decltype(test_type1()[integral_constant<int, 0>()])>
			>::value
	);
	
	static_assert( 
			at_type::value.value() == 2 &&  // lazy evaluation
			test_type1::at_v<1>.value() == 3 && // common access
			test_type1::at_v<5>.value_or(42) == 42 // out of range
	);
	static_assert( 
			test_type1::at(integral_constant<int, 0>()).value() == 2 &&
			test_type1::at(std::integral_constant<int, 0>()).value() == 2
	);

	constexpr test_type1 av = test_type1{};
	static_assert( av.template instance_at<0>().value() == 2 );
	static_assert( 
			av.instance_at(integral_constant<int, 0>()).value() == 2 &&
			av.instance_at(std::integral_constant<int, 0>()).value() == 2
	);
	static_assert( 
			av[ integral_constant<int, 0>() ].value() == 2 &&
			av[ std::integral_constant<int, 0>() ].value() == 2
	);
}

constexpr void at_test2()
{
	using at_type = test_type2::at_type<0>;

	static_assert(
			is_all_same<
				test_type2::element_type,
				test_type2::result_type,
				decltype(at_type::value),
				decltype(test_type2::at_v<0>),
				add_const_t<decltype(test_type2::at(integral_constant<int, 0>()))>,
				add_const_t<decltype(test_type2().instance_at(integral_constant<int, 0>()))>,
				add_const_t<decltype(test_type2()[integral_constant<int, 0>()])>
			>::value
	);

	static_assert(
			at_type::value == 2 && // lazy evaluation
			test_type2::at_v<1> == 3  // common access
			// test_type2::at_v<5> // out of range (cannot compile)
	);
	static_assert(
			test_type2::at(integral_constant<int, 0>()) == 2 &&
			test_type2::at(std::integral_constant<int, 0>()) == 2
	);

	constexpr test_type2 av = test_type2{};
	static_assert( av.template instance_at<0>() == 2 );
	static_assert(
			av.instance_at(integral_constant<int, 0>()) == 2 &&
			av.instance_at(std::integral_constant<int, 0>()) == 2
	);
	static_assert(
			av[ integral_constant<int, 0>() ] == 2 &&
			av[ std::integral_constant<int, 0>() ] == 2
	);
}

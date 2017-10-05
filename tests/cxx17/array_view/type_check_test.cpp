#include "array_view_test.hpp"
ARRAY_VIEW_TEST

using namespace srook;

constexpr void test1()
{
	static_assert(
			type_traits::detail::Land<
				is_same<test_type1::value_type, test_type1::pointer>,
				is_same<test_type1::pointer, test_type1::const_pointer>,
				is_same<remove_pointer_t<test_type1::value_type>&, test_type1::reference>,
				is_same<test_type1::reference, test_type1::const_reference>,
				is_default_constructible<test_type1>
			>::value
	);
}

constexpr void test2()
{
	static_assert(
			type_traits::detail::Land<
				is_same<test_type2::value_type, test_type2::pointer>,
				is_same<test_type2::pointer, test_type2::const_pointer>,
				is_same<remove_pointer_t<test_type1::value_type>&, test_type2::reference>,
				is_same<test_type2::reference, test_type1::const_reference>,
				is_default_constructible<test_type2>
			>::value
	);
}

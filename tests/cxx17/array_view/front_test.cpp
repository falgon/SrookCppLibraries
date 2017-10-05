#include "array_view_test.hpp"
ARRAY_VIEW_TEST
using namespace srook;

constexpr void test1()
{
	static_assert(
			test_type1::front() == 2 &&
			test_type1::front_v == 2 &&
			test_type1{}.instance_front() == 2
	);
}

#include<srook/mpl/math/four_arithmetic_operations_parser.hpp>

static constexpr const char
	exp0[] = "2*2*2+2",
	exp1[] = "3*3+3/3",
	exp2[] = "5*5/5+5",
	exp3[] = "(8+8)/8+8",
	exp4[] = "(9*9+9)/9";

static constexpr const int 
	tests0 = 2 * 2 * 2 + 2,
	tests1 = 3 * 3 + 3 / 3,
	tests2 = 5 * 5 / 5 + 5,
	tests3 = (8 + 8) / 8 + 8,
	tests4 = (9 * 9 + 9) / 9;

template<const char* e,int t>
constexpr int check()
{
	static_assert(srook::math::four_arithmetic_operations_parser::calculator_t<const char,e>::value == t && t == 10,"");
#if !defined(SROOK_IS_CXX11_EARLIER) and __cplusplus >= 201402L
	constexpr auto result_cxx14 = srook::math::four_arithmetic_operations_parser::calculator_v<const char,e>;
	static_assert(result_cxx14 == t && t == 10,"");
#if __cplusplus >= 201703L
	constexpr auto result_cxx17 = srook::math::four_arithmetic_operations_parser::calculator<e>;
	static_assert(result_cxx17 == t && t == 10,"");
#endif
#endif
	return 42; // for C++11
}

int main()
{
	check<exp0,tests0>();
	check<exp1,tests1>();
	check<exp2,tests2>();
	check<exp3,tests3>();
	check<exp4,tests4>();
}

#include "array_view_test.hpp"
using namespace srook;
using type = test_type3;

int main()
{
	using namespace std::string_literals;

	assert( (std::string(type::substr_type<0, 3>()) == "foo") );
	assert( (std::string(type::substr_type<0, 2>()) == "fo") );
}

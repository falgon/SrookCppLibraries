#include<srook/cxx17/mpl/any_pack/any_pack.hpp>
#include<srook/type_traits/type_constant.hpp>
#include<srook/algorithm/for_each.hpp>
#include<tuple>
#include<iostream>

template<std::size_t,class,class> struct FizzBuzz;
template<std::size_t i>
struct FizzBuzz<i,srook::any_pack<>,srook::any_pack<>> 
	: srook::type_constant<
		std::conditional_t<
			i % 15 == 0,
			srook::any_pack<'f','i','z','z','b','u','z','z'>,
			std::conditional_t<
				i % 5 == 0,
				srook::any_pack<'b','u','z','z'>,
				std::conditional_t<
					i % 3 == 0,
					srook::any_pack<'f','i','z','z'>,
					srook::any_pack<i>
				>
			>
		>
	>{};

int main()
{
	srook::for_each(srook::any_pack<>::for_type_until<1,51,FizzBuzz>::constant_range<std::tuple>,[](const auto& x){std::cout << x << ' ';});
	std::cout << std::endl;
}

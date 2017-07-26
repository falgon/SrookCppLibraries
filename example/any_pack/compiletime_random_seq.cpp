#include<srook/cxx17/mpl/any_pack/any_pack.hpp>
#include<srook/algorithm/for_each.hpp>
#include<iostream>

template<class F>
void linear(F&& disp) noexcept
{
	// minstd_rand0
	using minstd_rand0_type_25seq = srook::any_pack<>::make_random_sequence<25,srook::random::minstd_rand0<>>;
	// minstd_rand
	using minstd_rand_type_25seq = srook::any_pack<>::make_random_sequence<25,srook::random::minstd_rand<>>;
	srook::for_each(minstd_rand0_type_25seq::template constant_range<std::tuple>,disp); std::cout << std::endl;
	srook::for_each(minstd_rand_type_25seq::template constant_range<std::tuple>,disp); std::cout << std::endl;
	
	// uniform int distribution
	using between_0_to_100_random_50seq_linear = 
		srook::any_pack<>::make_random_sequence<50,srook::random::uniform_int_distribution<srook::random::minstd_rand<>,0,100>>;
	srook::for_each(between_0_to_100_random_50seq_linear::template constant_range<std::tuple>,[](const auto& x){std::cout << x << " ";}); std::cout << std::endl;

	// independence call
	static constexpr std::uint_fast32_t minstd_rand_result = srook::random::minstd_rand<>::result;
	using next = srook::random::minstd_rand<>::next_type;
	static constexpr std::uint_fast32_t minstd_rand_next_result = next::result;
	std::cout << minstd_rand_result << std::endl;
	std::cout << minstd_rand_next_result << std::endl;
}

template<class F>
void xorshift(F&& disp) noexcept
{
	// XOR32
	using XOR32 = srook::any_pack<>::make_random_sequence<25,srook::random::Xorshift32<>>;
	// XOR64
	using XOR64 = srook::any_pack<>::make_random_sequence<25,srook::random::Xorshift64<>>;
	// XOR96
	using XOR96 = srook::any_pack<>::make_random_sequence<25,srook::random::Xorshift96<>>;
	// XOR128
	using XOR128 = srook::any_pack<>::make_random_sequence<25,srook::random::Xorshift128<>>;
	srook::for_each(XOR32::template constant_range<std::tuple>,disp); std::cout << std::endl;
	srook::for_each(XOR64::template constant_range<std::tuple>,disp); std::cout << std::endl;
	srook::for_each(XOR96::template constant_range<std::tuple>,disp); std::cout << std::endl;
	srook::for_each(XOR128::template constant_range<std::tuple>,disp); std::cout << std::endl;

	// uniform int distribution
	using between_0_to_100_random_50seq_xor = srook::any_pack<>::make_random_sequence<50,srook::random::uniform_int_distribution<srook::random::Xorshift32<>,0,100>>;
	srook::for_each(between_0_to_100_random_50seq_xor::template constant_range<std::tuple>,disp); std::cout << std::endl;

	// independence call
	static constexpr std::uint_fast32_t Xor64_result = srook::random::Xorshift96<>::result;
	using next = srook::random::Xorshift64<>::next_type;
	static constexpr std::uint_fast32_t Xor64_next_result = next::result;
	std::cout << Xor64_result << std::endl;
	std::cout << Xor64_next_result << std::endl;
}

int main()
{
	constexpr auto disp = [](const auto& x){std::cout << x << " ";};
	linear(disp);
	//xorshift(disp);
}

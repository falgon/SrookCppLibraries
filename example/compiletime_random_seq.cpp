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

	// discard
	using discart_type = srook::random::minstd_rand<>::discard_type<10>;
	static constexpr std::uint_fast32_t discard_value = discart_type::result;
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

	// discard
	using discart_type = srook::random::Xorshift128<>::discard_type<10>;
	static constexpr std::uint_fast32_t discard_value = discart_type::result;
}

template<class F>
void mersenne_twister(F&& disp) noexcept
{
	using mt11213b_type = srook::any_pack<>::make_random_sequence<25,srook::random::mt11213b<>>;
	srook::for_each(mt11213b_type::template constant_range<std::tuple>,disp); std::cout << std::endl;
	
	using mt19937_type = srook::any_pack<>::make_random_sequence<25,srook::random::mt19937<>>;
	srook::for_each(mt19937_type::template constant_range<std::tuple>,disp); std::cout << std::endl;

	using mt19937_64_type = srook::any_pack<>::make_random_sequence<25,srook::random::mt19937_64<>>;
	srook::for_each(mt19937_64_type::template constant_range<std::tuple>,disp); std::cout << std::endl;

	// uniform int distribution
	using between_0_to_100_random_10seq_mt = srook::any_pack<>::make_random_sequence<10,srook::random::uniform_int_distribution<srook::random::mt19937<>,0,10>>;
	srook::for_each(between_0_to_100_random_10seq_mt::template constant_range<std::tuple>,disp); std::cout << std::endl;

	// independence call
	static constexpr std::uint_fast32_t mt_result = srook::random::mt19937<>::result;
	using next = srook::random::mt19937<>::next_type;
	static constexpr std::uint_fast32_t mt_next_result = next::result;
	std::cout << mt_result << std::endl;
	std::cout << mt_next_result << std::endl;

	// discard
	using discart_type = srook::random::mt19937<>::discard_type<10>;
	static constexpr std::uint_fast32_t discard_value = discart_type::result;
}

int main()
{
	constexpr auto disp = [](const auto& x){std::cout << x << " ";};
	linear(disp);
	xorshift(disp);
	mersenne_twister(disp);
}

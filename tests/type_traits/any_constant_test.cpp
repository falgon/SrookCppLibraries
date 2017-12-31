// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#include <srook/type_traits/any_constant.hpp>

struct Plus1729{
	explicit constexpr Plus1729() = default;
	template<class T>
	constexpr std::int32_t operator()(T&& v) const noexcept 
	{
		static_assert(std::is_convertible<typename std::decay<T>::type,std::int32_t>(),"");
		return std::int32_t(v + 1729);
	}
};

int main()
{
	{
		using type = srook::any_constant<std::int32_t,0,Plus1729>; // type of wrap about int32_t 1729

		constexpr std::int32_t v1 = type::value; // get value
		constexpr std::int32_t v2 = type(); // get value from implicit conversion
		constexpr std::int32_t v3 = type()(); // get value from operator()

		static_assert(v1 == v2 and v2 == v3 and v3 == 1729,"");
	}

	{
		constexpr double v = 
			srook::any_constant<
				double,
				42,
				srook::realvalue_compute::Plus<double,srook::any_constant<double,42,srook::realvalue_compute::Divides_value<double,int,1000>>> // means 0.042
			>::value; // 42 + 0.042

#include <srook/config/disable_warnings/push/Wfloat_equal.hpp>
		static_assert(std::is_same<typename std::decay<decltype(v)>::type,double>::value and 42.042 == v,"");
#include <srook/config/disable_warnings/pop.hpp>
	}

	{
		// 
		// written like in Polish Notation
		//

		constexpr double v =
#if SROOK_CPP_ALIAS_TEMPLATES
			srook::realvalue_compute::Plus_t<
				srook::realvalue_compute::Plus_t<
					srook::any_constant<double,42,srook::realvalue_compute::convert_type<double>>, // 42 -> 42.0
					srook::any_constant<double,42,srook::realvalue_compute::Divides_value<double,int,1000>> // means 0.042
				>, // type of wrap about 42 + 0.042
				srook::any_constant<double,314,srook::realvalue_compute::Divides_value<double,int,100>> // means 3.14
			>::value
#else
			srook::realvalue_compute::Plus<
				typename srook::realvalue_compute::Plus<
					srook::any_constant<double,42,srook::realvalue_compute::convert_type<double>>, // 42 -> 42.0
					srook::any_constant<double,42,srook::realvalue_compute::Divides_value<double,int,1000>> // means 0.042
				>::type, // type of wrap about 42 + 0.042
				srook::any_constant<double,314,srook::realvalue_compute::Divides_value<double,int,100>> // means 3.14
			>::type::value
#endif
			;

#include <srook/config/disable_warnings/push/Wfloat_equal.hpp>
			static_assert(v == 45.182,"");
#include <srook/config/disable_warnings/pop.hpp>
	}

	{
		//
		// written line in infix notation
		//

		constexpr double v = 
#if SROOK_CPP_ALIAS_TEMPLATES
			srook::any_constant<double,42,srook::realvalue_compute::convert_type<double>>::Plus_t<srook::any_constant<double,42,srook::realvalue_compute::Divides_value<double,int,1000>>>::value
#else
			srook::any_constant<double,42,srook::realvalue_compute::convert_type<double>>::Plus<srook::any_constant<double,42,srook::realvalue_compute::Divides_value<double,int,1000>>>::type::value
#endif
			;
#include <srook/config/disable_warnings/push/Wfloat_equal.hpp>
			static_assert(v == 42.042,"");
#include <srook/config/disable_warnings/pop.hpp>
	}

	{
		// 
		// mix
		//

		constexpr double v =
#if SROOK_CPP_ALIAS_TEMPLATES
			srook::any_constant<double,42,srook::realvalue_compute::convert_type<double>>::Plus_t<
				srook::realvalue_compute::Plus_t<
					srook::any_constant<double,42,srook::realvalue_compute::convert_type<double>>,
					srook::any_constant<double,42,srook::realvalue_compute::Divides_value<double,int,1000>>
				>
			>::value
#else
			srook::any_constant<double,42,srook::realvalue_compute::convert_type<double>>::Plus<
				typename srook::realvalue_compute::Plus<
					srook::any_constant<double,42,srook::realvalue_compute::convert_type<double>>,
					srook::any_constant<double,42,srook::realvalue_compute::Divides_value<double,int,1000>>
				>::type
			>::type::value
#endif
			;
#include <srook/config/disable_warnings/push/Wfloat_equal.hpp>
		static_assert(v == 84.042,"");
#include <srook/config/disable_warnings/pop.hpp>
	}
}

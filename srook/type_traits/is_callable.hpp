// Copyright (C) 2017 Roki
#ifndef INCLUDED_SROOK_TYPE_TRAITS_IS_CALLABLE
#define INCLUDED_SROOK_TYPE_TRAITS_IS_CALLABLE
#include<type_traits>

namespace srook{
inline namespace v1{

template<class T>
struct is_callable_impl{
private:
	typedef char(&yes)[1];
	typedef char(&no)[2];
	
	struct Fallback{
		void operator()();
	};
	struct derived:T,Fallback{};

	template<class U,U>
	struct Check;

	template<class>
	static yes test(...);
	template<class C>
	static no test(Check<void (Fallback::*)(),&C::operator()>*);
public:
	static constexpr bool value = sizeof(test<derived>(nullptr)) == sizeof(yes);
};

template<class T>
struct is_callable:std::conditional<std::is_class<T>::value,is_callable_impl<T>,std::false_type>::type{};

template<class T>
constexpr bool is_callable_v=is_callable<T>::value;

} // inline namespace v1
} // namespace srook

#endif

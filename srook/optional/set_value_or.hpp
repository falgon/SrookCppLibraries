#ifndef INCLUDED_SROOK_OPIONAL_SETTER_HPP
#define INCLUDED_SROOK_OPIONAL_SETTER_HPP
#if __has_include(<optional>)
#include<optional>
#	define OPTIONAL std::optional
#	define NULLOPT std::nullopt
#	define NULLOPT_T std::nullopt_t
#elif __has_include(<experimental/optional>)
#include<experimental/optional>
#	define OPTIONAL std::experimental::optional
#	define NULLOPT std::experimental::nullopt
#	define NULLOPT_T std::experimental::nullopt_t
#elif __has_include(<boost/optional.hpp>)
#	include<boost/optional.hpp>
#	define OPTIONAL boost::optional
#	define NULLOPT boost::none
#	define NULLOPT_T boost::none_t
#else
#	include<srook/optional.hpp>
#	define OPTIONAL srook::optional
#	define NULLOPT srook::nullopt
#	define NULLOPT_T srook::nullopt_t
#endif
#if defined(OPTIONAL) and defined(NULLOPT) and defined(NULLOPT_T)
#include<srook/config/require.hpp>
#include<srook/range/adaptor/adaptor_operator.hpp>
#include<memory>

namespace srook{
namespace adaptors{
namespace detail{

namespace{

template<class T>
struct setter{
	template<class U,REQUIRES(std::is_convertible<std::decay_t<U>,T>::value)>
	explicit constexpr setter(U&& value):value_(std::forward<U>(value)){}

	constexpr const T value(const OPTIONAL<T>& op)const noexcept(noexcept(std::declval<OPTIONAL<T>>().value_or(std::declval<T>())))
	{
		return op.value_or(value_);
	}

	static std::unique_ptr<setter<T>> data;
private:
	T value_;
};

template<class T>
std::unique_ptr<setter<T>> setter<T>::data={nullptr};

} // anonymouse namespace

#if __cplusplus >= 201703L

template<class U>
setter(U&&) -> setter<std::decay_t<U>>;

#endif

struct value_t final{
	template<class T>
	constexpr auto operator()(const OPTIONAL<T>& opt)const noexcept(noexcept(setter<T>::data?setter<T>::data->value(opt):opt.value()))
	-> decltype(setter<T>::data?setter<T>::data->value(opt):opt.value())
	{
		return setter<T>::data?setter<T>::data->value(opt):opt.value();
	}
};

} // namespace detail

//using detail::set_value_or;
detail::value_t value;

} // namespace adaptors

namespace optional{

template<class T>
void set_value_or(T&& t)noexcept(false)
{
	adaptors::detail::setter<std::decay_t<T>>::data.reset(new adaptors::detail::setter<std::decay_t<T>>(std::forward<T>(t)));
}

} // namespace optional

} // namespace srook

#undef OPTIONAL
#undef NULLOPT
#undef NULLOPT_T
#undef VARIABLE_TO_STRING
#endif
#endif

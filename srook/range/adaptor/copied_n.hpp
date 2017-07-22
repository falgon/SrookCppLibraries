// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_ADAPTOR_COPIED_N
#define INCLUDED_SROOK_ADAPTOR_COPIED_N
#include<srook/range/adaptor/adaptor_operator.hpp>
#include<iterator>
#include<srook/config/require.hpp>
#include<srook/type_traits/is_callable.hpp>

namespace srook{
namespace adaptors{
namespace detail{
inline namespace v1{

template<class Iterator>
struct copied_n_t{
	explicit constexpr copied_n_t(Iterator first,std::size_t n)
		:first_(std::move(first)),n_(std::move(n)){}
	template<class U>
	operator U()
	{
		return U(first_,std::next(first_,n_));
	}
private:
	Iterator first_;
	std::size_t n_;
};
template<class Iterator>
copied_n_t<std::decay_t<Iterator>> make_copied_n_t(Iterator&& first,std::size_t n)
{
	return copied_n_t<std::decay_t<Iterator>>(std::forward<Iterator>(first),std::move(n));
}

struct copied_n{
	explicit constexpr copied_n(std::size_t n)
		:n_(std::move(n)){}
	
	template<class Range,REQUIRES(std::is_const<std::remove_reference_t<Range>>::value)>
	constexpr copied_n_t<typename std::decay_t<Range>::const_iterator> operator()(Range&& r)
	{
		return make_copied_n_t(std::begin(r),std::move(n_));
	}
	template<class Range,REQUIRES(!std::is_const<std::remove_reference_t<Range>>::value)>
	constexpr copied_n_t<typename std::decay_t<Range>::iterator> operator()(Range&& r)
	{
		return make_copied_n_t(std::begin(r),std::move(n_));
	}
private:
	std::size_t n_;
};

} // inline namespace
} // namespace detail

using detail::copied_n;

} // namespace adaptors
} // namespace srook
#endif

// Copyright (C) 2017 roki
#ifndef SROOK_INCLUDED_MOVE_BACKWARD_HPP
#define SROOK_INCLUDED_MOVE_BACKWARD_HPP
#include<srook/range/adaptor/adaptor_operator.hpp>
#include<srook/config/require.hpp>
#include<srook/mpl/has_iterator.hpp>
#include<srook/iterator/range_iterator.hpp>
#include<algorithm>

namespace srook{
namespace pipealgo{
namespace detail{
inline namespace v1{

template<class Iterator>
struct move_backward_t{
	template<REQUIRES(!srook::mpl::has_iterator_v<Iterator>)>
	explicit constexpr move_backward_t(Iterator iter):iter_(std::move(iter)){}
	
	template<class R,REQUIRES(srook::mpl::has_iterator_v<std::decay_t<R>> || is_range_iterator_v<std::decay_t<R>>)>
	typename std::decay_t<R>::iterator operator()(R&& r)
	{
		return std::move_backward(r.begin(),r.end(),std::move(iter_));
	}
private:
	Iterator iter_;
};

template<class Iterator>
constexpr move_backward_t<std::decay_t<Iterator>> move_backward(Iterator&& iter)
{
	return move_backward_t<std::decay_t<Iterator>>(std::forward<Iterator>(iter));
}

} // inline namespace v1
} // namespace detail

using detail::move_backward;

} // namespace pipealgo
} // namespace srook
#endif

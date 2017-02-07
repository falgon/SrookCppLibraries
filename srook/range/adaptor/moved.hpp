#ifndef INCLUDED_SROOK_RANGE_ADAPTOR_MOVED
#define INCLUDED_SROOK_RANGE_ADAPTOR_MOVED
#include<srook/range/adaptor/adaptor_operator.hpp>
#include<srook/type_traits/has_iterator.hpp>
#include<srook/config/require.hpp>
#include<iterator>

namespace srook{
namespace adaptors{
namespace detail{
inline namespace v1{

template<class Iterator>
struct moved_t_impl{
	template<REQUIRES(!has_iterator_v<Iterator>)>
	explicit constexpr moved_t_impl(Iterator first,Iterator last)
		:first_(std::move(first)),last_(std::move(last)){}
	
	template<class Range,REQUIRES(has_iterator_v<std::decay_t<Range>> || is_range_iterator_v<std::decay_t<Range>>)>
	operator Range()const
	{
		return Range(std::make_move_iterator(first_),std::make_move_iterator(last_));
	}
private:
	Iterator first_,last_;
};

template<class Iterator>
constexpr moved_t_impl<std::decay_t<Iterator>> make_moved(Iterator&& first,Iterator&& last)
{
	return moved_t_impl<std::decay_t<Iterator>>(std::forward<Iterator>(first),std::forward<Iterator>(last));
}

const auto moved=[](auto&& r){return make_moved(r.begin(),r.end());};

} // inline namespace v1
} // namespace detail

using detail::moved;

} // namespace adaptors
} // namespace srook

#endif

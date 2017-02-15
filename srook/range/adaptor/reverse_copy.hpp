#ifndef INCLUDED_SROOK_RANGE_ALGORITHM_REVERSE_COPY_HPP
#define INCLUDED_SROOK_RANGE_ALGORITHM_REVERSE_COPY_HPP
#include<srook/iterator/range_iterator.hpp>
#include<srook/type_traits/has_iterator.hpp>
#include<srook/config/require.hpp>
#include<iterator>
#include<algorithm>

namespace srook{
namespace adaptors{
namespace detail{
inline namespace v1{

template<class Iterator>
struct reverse_copy_t{
	template<REQUIRES(!has_iterator_v<Iterator>)>
	explicit constexpr reverse_copy_t(Iterator iter):iter_(std::move(iter)){}

	template<class Range,REQUIRES(has_iterator_v<std::decay_t<Range>> || is_range_iterator_v<std::decay_t<Range>>)>
	Iterator operator()(Range&& r)
	{
		return
		std::reverse_copy(r.begin(),r.end(),std::move(iter_));
	}
private:
	Iterator iter_;
};

template<class Iterator,REQUIRES(!has_iterator_v<std::decay_t<Iterator>>)>
constexpr reverse_copy_t<std::decay_t<Iterator>> reverse_copy(Iterator&& iter)
{
	return reverse_copy_t<std::decay_t<Iterator>>(std::forward<Iterator>(iter));
}

template<class Range,REQUIRES(has_iterator_v<std::decay_t<Range>>)>
constexpr reverse_copy_t<typename std::decay_t<Range>::iterator> reverse_copy(Range&& r)
{
	return reverse_copy_t<typename std::decay_t<Range>::iterator>(r.begin());
}

} // inline namespace v1
} // namespace detail

using detail::reverse_copy;

} // namespace adaptors
} // namespace srook

#endif

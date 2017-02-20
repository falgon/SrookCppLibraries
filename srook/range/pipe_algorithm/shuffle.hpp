#ifndef INCLUDED_SROOK_RANGE_PIPE_ALGORITHM_SHUFFLE_HPP
#define INCLUDED_SROOK_RANGE_PIPE_ALGORITHM_SHUFFLE_HPP
#include<srook/type_traits/has_iterator.hpp>
#include<srook/config/require.hpp>
#include<srook/iterator/range_iterator.hpp>
#include<algorithm>

namespace srook{
namespace pipealgo{
namespace detail{
inline namespace v1{

template<class UniformRandomNumberGenerator>
struct shuffle_t{
	explicit constexpr shuffle_t(const UniformRandomNumberGenerator& g):g_(g){}
	
	template<
		class Range,
		REQUIRES(has_iterator_v<std::remove_reference_t<std::remove_cv_t<Range>>> or
				is_range_iterator_v<std::remove_reference_t<std::remove_cv_t<Range>>>
		)
	>
	Range&& operator()(Range&& r)
	{
		std::shuffle(r.begin(),r.end(),g_);
		return std::forward<Range>(r);
	}
private:
	UniformRandomNumberGenerator g_;
};

template<class UniformRandomNumberGenerator>
constexpr shuffle_t<std::remove_reference_t<std::remove_cv_t<UniformRandomNumberGenerator>>>
shuffle(UniformRandomNumberGenerator&& g)
{
	return shuffle_t<
		std::remove_reference_t<std::remove_cv_t<UniformRandomNumberGenerator>>
	>(std::forward<UniformRandomNumberGenerator>(g));
}

} // inline namespace v1
} // namespace detail

using detail::shuffle;

} // namespace pipealgo
} // namespace srook

#endif

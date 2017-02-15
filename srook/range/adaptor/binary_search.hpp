#ifndef INCLUDED_SROOK_ADAPTOR_BINARY_SEARCH_HPP
#define INCLUDED_SROOK_ADAPTOR_BINARY_SEARCH_HPP
#include<srook/range/adaptor/adaptor_operator.hpp>
#include<srook/type_traits/is_callable.hpp>
#include<srook/type_traits/has_iterator.hpp>
#include<srook/config/require.hpp>
#include<srook/iterator/range_iterator.hpp>
#include<algorithm>
namespace srook{
namespace adaptors{
namespace detail{
inline namespace v1{

template<class Target>
struct binary_search_t{
	explicit constexpr binary_search_t(const Target& t):target(t){}
	explicit constexpr binary_search_t(Target&& t):target(std::move(t)){}
	template<class Range,REQUIRES(has_iterator_v<std::decay_t<Range>> || is_range_iterator_v<std::decay_t<Range>>)>
	bool operator()(Range&& r)
	{
		return std::binary_search(r.cbegin(),r.cend(),std::move(target));
	}
private:
	Target target;
};
template<class Target>
constexpr binary_search_t<std::decay_t<Target>> binary_search(Target&& target)
{
	return binary_search_t<std::decay_t<Target>>(std::forward<Target>(target));
}

template<class Target,class Compare>
struct binary_search_t_compare{
	explicit constexpr binary_search_t_compare(const Target& t,const Compare& comp):target(t),cmp(comp){}
	explicit constexpr binary_search_t_compare(Target&& t,const Compare& comp):target(std::move(t)),cmp(comp){}
	explicit constexpr binary_search_t_compare(const Target& t,Compare&& comp):target(t),cmp(std::move(comp)){}
	explicit constexpr binary_search_t_compare(Target&& t,Compare&& comp):target(std::move(t)),cmp(std::move(comp)){}

	template<class Range>
	bool operator()(Range&& r)
	{
		return std::binary_search(r.cbegin(),r.cend(),std::move(target),std::move(cmp));
	}
private:
	Target target;
	Compare cmp;
};
template<class Target,class Compare>
constexpr binary_search_t_compare<std::decay_t<Target>,std::decay_t<Compare>> binary_search(Target&& target,Compare&& comp)
{
	return binary_search_t_compare<std::decay_t<Target>,std::decay_t<Compare>>(std::forward<Target>(target),std::forward<Compare>(comp));
}

} // inline namespace v1
} // namespace detail

using detail::binary_search;

} // namespace adaptors
} // namespace srook
#endif

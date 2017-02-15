#ifndef INCLUDED_SROOK_RANGE_ADAPTOR_GENERATE
#define INCLUDED_SROOK_RANGE_ADAPTOR_GENERATE
#include<srook/range/adaptor/adaptor_operator.hpp>
#include<srook/iterator/range_iterator.hpp>
#include<srook/type_traits/is_callable.hpp>
#include<srook/type_traits/has_iterator.hpp>
#include<srook/config/require.hpp>
#include<algorithm>

namespace srook{
namespace adaptors{
namespace detail{
inline namespace v1{

template<class Generator>
struct generate_t{
	template<REQUIRES(is_callable_v<Generator>)>
	explicit constexpr generate_t(Generator gen):gen_(std::move(gen)){}
	template<class Range,REQUIRES(has_iterator_v<std::decay_t<Range>> || is_range_iterator_v<std::decay_t<Range>>)>
	srook::range_iterator<typename std::decay_t<Range>::iterator> operator()(Range&& r)
	{
		std::generate(r.begin(),r.end(),std::move(gen_));
		return srook::make_range_iterator(r.begin(),r.end());
	}
private:
	Generator gen_;
};

template<class Generator>
constexpr generate_t<std::decay_t<Generator>> generate(Generator&& gen)
{
	return generate_t<std::decay_t<Generator>>(std::forward<Generator>(gen));
}

} // inline namespace v1
} // namesapce detail

using detail::generate;

} // namespace adaptors
} // namespace srook

#endif

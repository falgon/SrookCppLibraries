#ifndef SROOK_INCLUDED_ADAPTOR_OPERATOR
#define SROOK_INCLUDED_ADAPTOR_OPERATOR
#include<utility>
namespace srook{
namespace adaptors{
inline namespace v1{

template<class Range,class Function>
auto operator|(Range&& r,Function&& f)
{
	return f(std::forward<Range>(r));
}

} // inline namespace
} // namespace adaptors
} // namespace roki
#endif

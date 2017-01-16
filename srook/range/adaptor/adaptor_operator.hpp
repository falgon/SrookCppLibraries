#ifndef SROOK_INCLUDED_ADAPTOR_OPERATOR
#define SROOK_INCLUDED_ADAPTOR_OPERATOR
#include<utility>
namespace srook{

template<class Range,class Function>
auto operator|(Range&& r,Function&& f)
{
	return f(std::forward<Range>(r));
}

} // namespace roki
#endif

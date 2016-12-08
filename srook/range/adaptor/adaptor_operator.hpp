#ifndef SROOK_INCLUDED_ADAPTOR_OPERATOR
#define SROOK_INCLUDED_ADAPTOR_OPERATOR
namespace srook{

template<class Range,class Function>
auto operator|(Range& r,Function f){return f(r);}
template<class Range,class Function>
auto operator|(const Range& r,Function f){return f(r);}

} // namespace roki
#endif

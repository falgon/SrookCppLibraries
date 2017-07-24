#ifndef INCLUDED_SROOK_CXX17_TYPE_TRAITS_AUTO_CONSTANT_HPP
#define INCLUDED_SROOK_CXX17_TYPE_TRAITS_AUTO_CONSTANT_HPP

namespace srook{

template<auto v>
struct auto_constant{
	static constexpr decltype(auto) value = v;
};

} // namespace srook

#endif

// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_MPL_EXPRESSION
#define INCLUDED_SROOK_MPL_EXPRESSION
#include<utility>

namespace srook{
namespace detail{
namespace adl_firewall_expression{
inline namespace v1{

template<class L,class Operator,class R>
class Expression final{
	const L& l_;
	const R& r_;
public:
	explicit constexpr Expression(const L& l,const R& r)
		:l_(l),r_(r){}

	constexpr auto operator[](const std::size_t& index)const noexcept
	->decltype(Operator::apply(l_[index],r_[index]))
	{
		return Operator::apply(l_[index],r_[index]);
	}
};

struct Plus final{
	template<class T>
	static constexpr T apply(const T& lhs,const T& rhs){return lhs+rhs;}
};

struct Minus final{
	template<class T>
	static constexpr T apply(const T& lhs,const T& rhs){return lhs-rhs;}
};

struct Multiply final{
	template<class T>
	static constexpr T apply(const T& lhs,const T& rhs){return lhs*rhs;}
};

struct Division final{
	template<class T>
	static constexpr T apply(const T& lhs,const T& rhs){return rhs?lhs/rhs:0;}
};

template<class L,class R>
constexpr Expression<L,Plus,R> operator+(const L& l,const R& r)noexcept{return Expression<L,Plus,R>(l,r);}
template<class L,class R>
constexpr Expression<L,Minus,R> operator-(const L& l,const R& r)noexcept{return Expression<L,Minus,R>(l,r);}
template<class L,class R>
constexpr Expression<L,Multiply,R> operator*(const L& l,const R& r)noexcept{return Expression<L,Multiply,R>(l,r);}
template<class L,class R>
constexpr Expression<L,Division,R> operator/(const L& l,const R& r)noexcept{return Expression<L,Division,R>(l,r);}

} // inline namespace v1
} // namespace adl_firewall
} // namespace detail
} // namespace srook
#endif

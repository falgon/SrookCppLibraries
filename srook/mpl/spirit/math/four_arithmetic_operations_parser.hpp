#ifndef INCLUDED_SROOK_MPL_SPIRIT_MATH_FOUR_ARITHMETIC_OPERATIONS_PARSER_CALC_HPP
#define INCLUDED_SROOK_MPL_SPIRIT_MATH_FOUR_ARITHMETIC_OPERATIONS_PARSER_CALC_HPP

#include<utility>
#include<type_traits>
#include<srook/mpl/utility/ctoi.hpp>
#include<srook/config/compiler.hpp>
#include<srook/type_traits/type_constant.hpp>

namespace srook{
inline namespace mpl{
namespace spirit{
namespace math{
namespace four_arithmetic_operations_parser{
inline namespace v1{

namespace detail{

struct Plus{
	template<typename T>
	static constexpr T apply(T l,T r)noexcept{return l + r;}
};
struct Minus{
	template<typename T>
	static constexpr T apply(T l,T r)noexcept{return l - r;}
};
struct Multiply{
	template<typename T>
	static constexpr T apply(T l,T r)noexcept{return l * r;}
};
struct Division{
	template<typename T>
	static constexpr T apply(T l,T r)noexcept{return l / r;}
};

template<class charT,charT*,std::size_t,class result_type,result_type,bool,class = std::nullptr_t> struct Expr_impl;
template<class charT,charT*,std::size_t,class result_type> struct Expr;
template<class charT,charT*,std::size_t,class result_type,result_type,bool,class = std::nullptr_t> struct Term_impl;
template<class charT,charT*,std::size_t,class result_type> struct Term;
template<class charT,charT*,std::size_t,class result_type,bool> struct Factor_impl;
template<class charT,charT*,std::size_t,class result_type> struct Factor;
template<bool,class charT,charT*,std::size_t,class result_type,result_type> struct Number_impl;
template<class charT,charT*,std::size_t,class result_type> struct Number;

template<class charT,charT* s,std::size_t idx,class result_type,result_type val,bool b>
struct Expr_impl<charT,s,idx,result_type,val,b,typename std::enable_if<s[idx] == '+' or s[idx] == '-',std::nullptr_t>::type>{
private:
	static constexpr std::size_t i = idx + 1;
private:
	static constexpr result_type val_ = Term<charT,s,i,result_type>::value;
	static constexpr std::size_t idx_t = Term<charT,s,i,result_type>::index;
	static constexpr result_type val_t = std::conditional<b,Plus,Minus>::type::apply(val,val_);
public:
	static constexpr result_type value = Expr_impl<charT,s,idx_t,result_type,val_t,(s[idx_t] == '+')>::value;
	static constexpr std::size_t index = Expr_impl<charT,s,idx_t,result_type,val_t,(s[idx_t] == '+')>::index;
};
template<class charT,charT* s,std::size_t idx,class result_type,result_type val,bool b>
struct Expr_impl<charT,s,idx,result_type,val,b,typename std::enable_if<s[idx] != '+' and s[idx] != '-',std::nullptr_t>::type>{
	static constexpr result_type value = val;
	static constexpr std::size_t index = idx;
};
template<class charT,charT* exp,std::size_t idx,class result_type>
struct Expr{
private:
	static constexpr result_type val = Term<charT,exp,idx,result_type>::value;
	static constexpr std::size_t idx_t = Term<charT,exp,idx,result_type>::index;
	static constexpr bool b = exp[idx_t] == '+' or exp[idx_t] == '-';
public:
	static constexpr result_type value = b ? Expr_impl<charT,exp,idx_t,result_type,val,(exp[idx_t] == '+')>::value : val;
	static constexpr std::size_t index = b ? Expr_impl<charT,exp,idx_t,result_type,val,(exp[idx_t] == '+')>::index : idx_t;
};


template<class charT,charT* s,std::size_t idx,class result_type,result_type val,bool b>
struct Term_impl<charT,s,idx,result_type,val,b,typename std::enable_if<s[idx] == '*' or s[idx] == '/',std::nullptr_t>::type>{
private:
	static constexpr std::size_t i = idx + 1;
private:
	static constexpr result_type val_ = Factor<charT,s,i,result_type>::value;
	static constexpr std::size_t idx_t = Factor<charT,s,i,result_type>::index;
	static constexpr result_type val_t = std::conditional<b,Multiply,Division>::type::apply(val,val_);
public:
	static constexpr result_type value = Term_impl<charT,s,idx_t,result_type,val_t,(s[idx_t] == '*')>::value;
	static constexpr std::size_t index = Term_impl<charT,s,idx_t,result_type,val_t,(s[idx_t] == '/')>::index;
};
template<class charT,charT* s,std::size_t idx,class result_type,result_type val,bool b>
struct Term_impl<charT,s,idx,result_type,val,b,typename std::enable_if<s[idx] != '*' and s[idx] != '/',std::nullptr_t>::type>{
	static constexpr result_type value = val;
	static constexpr std::size_t index = idx;
};
template<class charT,charT* exp,std::size_t idx,class result_type>
struct Term{
private:
	static constexpr result_type val = Factor<charT,exp,idx,result_type>::value;
	static constexpr std::size_t idx_t = Factor<charT,exp,idx,result_type>::index;
	static constexpr bool b = exp[idx_t] == '*' or exp[idx_t] == '/';
public:
	static constexpr result_type value = b ? Term_impl<charT,exp,idx_t,result_type,val,(exp[idx_t] == '*')>::value : val;
	static constexpr std::size_t index = b ? Term_impl<charT,exp,idx_t,result_type,val,(exp[idx_t] == '*')>::index : idx_t;
};

template<class charT,charT* s,std::size_t idx,class result_type>
struct Factor_impl<charT,s,idx,result_type,false>{
	static constexpr result_type value = Expr<charT,s,idx,result_type>::value;
	static constexpr std::size_t index = Expr<charT,s,idx,result_type>::index + 1;
};
template<class charT,charT* s,std::size_t idx,class result_type>
struct Factor_impl<charT,s,idx,result_type,true>{
	static constexpr result_type value = Number<charT,s,idx - 1,result_type>::value;
	static constexpr std::size_t index = Number<charT,s,idx - 1,result_type>::index;
};
template<class charT,charT* s,std::size_t idx,class result_type>
struct Factor{
private:
	static constexpr OPTIONAL<unsigned short int> exp = ctoi<s[idx]>::value;
	static constexpr std::size_t i_cre = idx + 1;
public:
	static constexpr result_type value = Factor_impl<charT,s,i_cre,result_type,exp.has_value()>::value;
	static constexpr std::size_t index = Factor_impl<charT,s,i_cre,result_type,exp.has_value()>::index;
};

template<class charT,charT* s,std::size_t idx,class result_type,result_type n>
struct  Number_impl<true,charT,s,idx,result_type,n>{
private:
	static_assert(ctoi<s[idx]>::value,"Number_impl ctoi<s[idx]>::value is not number");
	static constexpr result_type val = n * 10 + ctoi<s[idx]>::value.value();
public:
	static constexpr result_type value = Number_impl<ctoi<s[idx + 1]>::value.has_value(),charT,s,idx + 1,result_type,val>::value;
	static constexpr std::size_t index = Number_impl<ctoi<s[idx + 1]>::value.has_value(),charT,s,idx + 1,result_type,val>::index;
};

template<class charT,charT* s,std::size_t idx,class result_type,result_type n>
struct Number_impl<false,charT,s,idx,result_type,n>{
	static constexpr result_type value = n;
	static constexpr std::size_t index = idx;
};

template<class charT,charT* s,std::size_t idx,class result_type>
struct Number{
private:
	static_assert(ctoi<s[idx]>::value,"Number ctoi<s[idx]>::value is not number");
public:
	static constexpr result_type value = Number_impl<ctoi<s[idx + 1]>::value.has_value(),charT,s,idx + 1,result_type,ctoi<s[idx]>::value.value()>::value;
	static constexpr std::size_t index = Number_impl<ctoi<s[idx + 1]>::value.has_value(),charT,s,idx + 1,result_type,ctoi<s[idx]>::value.value()>::index;
};

} // namespace detail

#if __cplusplus >= 201703L
template<auto s,class Result_t = int>
constexpr Result_t calculator = detail::Expr<std::remove_pointer_t<decltype(s)>,s,0,Result_t>::value;
#endif

#if !defined(SROOK_IS_CXX11_EARLIER) and __cplusplus >= 201402L
template<class charT,charT* s,class Result_t = int>
constexpr Result_t calculator_v = detail::Expr<charT,s,0,Result_t>::value;
#endif

template<class charT,charT* s,class Result_t = int>
struct calculator_t{
	static constexpr Result_t value = detail::Expr<charT,s,0,Result_t>::value;
};


} // inline namespace v1
} // four_arithmetic_operations_parser
} // namespace math
} // namespace spirit
} // inline namespace mpl
} // namespace srook

#endif

// Copyright (C) 2017 Roki
#ifndef INCLUDED_SROOK_DIGITS_VALUES
#define INCLUDED_SROOK_DIGITS_VALUES

#include<utility>
#include<memory>
#include<vector>
#include<cmath>
#include<algorithm>

#if __has_include(<boost/utility.hpp>)
#if __has_include(<boost/mpl/if.hpp>)
#include<boost/utility.hpp>
#include<boost/mpl/if.hpp>
using boost::noncopyable;
using boost::mpl::if_c;
#else
// self made boost noncopyable
namespace srook{
	class noncopyable{
	noncopyable(const noncopyable&)=delete;
	noncopyable& operator=(const noncopyable&)=delete;
protected:
	noncopyable()=default;
	~noncopyable()=default;
};

// self made boost.mpl.if_c
template<bool Condition,typename T1,typename T2>
struct if_c{
	using type=T2;
};
template<typename T1,typename T2>
struct if_c<true,T1,T2>{
	using type=T1;
};
} // namespace srook
using srook::noncopyable;
using srook::if_c;
#endif
#endif

namespace srook{
namespace srook_adl{ // protection from unintended ADL
inline namespace v1{

template<bool Condition,typename T1,typename T2>
using if_c_t=typename if_c<Condition,T1,T2>::type;


template<typename _Tp,class Not>
constexpr bool not_truely_type_v=!std::is_same<typename std::decay<_Tp>::type,Not>::value;


template<typename ResultType>
struct digits_values final:private noncopyable{
	using result_type=ResultType;
	
	digits_values()=default;

	template<class _Tp>
	using Check_t=typename std::enable_if<not_truely_type_v<_Tp,digits_values>&&
		!std::is_class<typename std::decay<_Tp>::type>::value&&
		not_truely_type_v<_Tp,float>&&
		not_truely_type_v<_Tp,double>>::type;

	template<class _Tp,class=Check_t<_Tp>>
	digits_values(_Tp x)
		:v(digit_calculation(x)?digit_calculation(x):1,digit_calculation(x)<=1?x:0)
	{
		const auto digit_=digit_calculation(x);
		if(!(digit_<=1)){
			auto ten_v=static_cast<std::size_t>(std::pow(10,digit_-1));
			for(std::size_t i=0; i<v.size(); ++i){
				v[i]=x/ten_v;
				x%=ten_v;
				ten_v/=10;
			}
		}
	}

	digits_values(digits_values&& oth)
	{
		v=std::move(oth.v);
	}

	digits_values& operator=(digits_values&&)=default;
	
	template<class _Tp,class=Check_t<_Tp>>
	digits_values& operator=(_Tp x)
	{
		auto digit_=digit_calculation(x);
		v.resize(digit_);
		if(!(digit_<=1)){
			auto ten_v=static_cast<std::size_t>(std::pow(10,digit_-1));
			for(std::size_t i=0; i<v.size(); ++i){
				v[i]=x/ten_v;
				x%=ten_v;
				ten_v/=10;
			}
		}
	}
	
	result_type operator[](const std::size_t& index)const
	{return v.at(index);}
	
	template<typename _ResultType>
	digits_values operator+(const digits_values<_ResultType>& oth)
	{
		const auto this_size=digit();
		const auto oth_size=oth.digit();	
		const auto max_v=std::max(this_size,oth_size);
		
		//using bigger_type=if_c_t<sizeof(_ResultType) < sizeof(result_type),result_type,_ResultType>;

		digits_values<bigger_type> result;
		result.v.reserve(max_v);

		if(max_v==this_size){
			std::copy(cbegin(),cend(),std::back_inserter(result.v));
			std::size_t counter=0;
			for(auto i=oth.cbegin(); i!=oth.cend(); ++i)result.v[counter++]+=*i;
		}else{
			std::copy(oth.cbegin(),oth.cend(),std::back_inserter(result.v));
			std::size_t counter=0;
			for(auto i=cbegin(); i!=cend(); ++i)result.v[counter++]+=*i;
		}

		return result;
	}

	typename std::vector<result_type>::const_iterator cbegin()const{return v.cbegin();}
	typename std::vector<result_type>::const_iterator cend()const{return v.cend();}
	typename std::vector<result_type>::iterator begin(){return v.begin();}
	typename std::vector<result_type>::iterator end(){return v.end();}
	typename std::vector<result_type>::reverse_iterator rbegin(){return v.rbegin();}
	typename std::vector<result_type>::reverse_iterator rend(){return v.rend();}

	inline std::size_t digit()const{return v.size();}
	
	auto real_value()
	{
		auto digit_=digit();
		auto ten_v=static_cast<std::size_t>(std::pow(10,digit_-1));
		unsigned long long int result=0;

		for(std::size_t i=0; i<digit_; ++i){
			result+=v[i]*ten_v;
			ten_v/=10;
		}
		return result;
	}
private:
	std::size_t digit_calculation(unsigned long long int x)const
	{return std::log10(x)+1;}

	template<typename Pointed_type>
	std::size_t digit_calculation(Pointed_type x)const
	{
		std::size_t result=0;
		for(; x!=0; ++result)x/=10;
		return result;
	}

	std::vector<result_type> v;
};

} // inline namespace v1
} // namespace srook_adl

template<class _Tp=unsigned short int>
using digits_values=srook_adl::digits_values<_Tp>;

} // namespace srook
#endif // include guard

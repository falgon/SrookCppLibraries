#ifndef INCLUDED_DIGITS_HPP
#define INCLUDED_DIGITS_HPP
#include<vector>
#include<cmath>
#include<type_traits>
#include<iostream>
#include<iterator>
#include<experimental/optional>
#include<functional>

namespace srook{
template<class L,class Operator,class R>
struct Expression{
	explicit Expression(const L& l,const R& r)noexcept
		:l_(l),r_(r),size_(l.size())
	{}
	auto operator[](const std::size_t index)const noexcept{return Operator::apply(l_[index],r_[index]);}
	constexpr std::size_t size()const{return size_;}
private:
	const L& l_;
	const R& r_;
	const std::size_t size_;
};

struct Plus{
	template<typename T>
	static T apply(T l,T r){return l+r;}
};
struct Minus{
	template<typename T>
	static T apply(T l,T r){return l-r;}
};
struct Multiple{
	template<typename T>
	static T apply(T l,T r){return l*r;}
};
struct Division{
	template<typename T>
	static T apply(T l,T r)
	{
		if(l)return l/r;
		else return l;
	}
};

template<class L,class R>
auto operator+(const L& l,const R& r){return Expression<L,Plus,R>(l,r);}
template<class L,class R>
auto operator-(const L& l,const R& r){return Expression<L,Minus,R>(l,r);}
template<class L,class R>
auto operator*(const L& l,const R& r){return Expression<L,Multiple,R>(l,r);}
template<class L,class R>
auto operator/(const L& l,const R& r){return Expression<L,Division,R>(l,r);}

namespace range_iterator_detail{
template<class Iterator>
struct range_iterator{
	using iterator=Iterator;
	using const_iterator=const iterator;
	using iterator_category=typename std::iterator_traits<iterator>::iterator_category;
	using value_type=typename std::iterator_traits<iterator>::value_type;
	using reference=typename std::iterator_traits<iterator>::reference;
	using pointer=typename std::iterator_traits<iterator>::pointer;
	using difference_type=typename std::iterator_traits<iterator>::difference_type;

	explicit range_iterator(Iterator first,Iterator last)noexcept
		:first_(first),last_(last){}
	iterator begin()const{return first_;}
	iterator end()const{return last_;}
	const_iterator cbegin()const{return first_;}
	const_iterator cend()const{return last_;}
protected:
	iterator first_,last_;
};

template<class Iterator>
range_iterator<Iterator> make_range_iterator(Iterator first,Iterator last){return range_iterator<Iterator>(first,last);}

template<class Predicate,class Iterator>
struct filter_iterator{
	using iterator=Iterator;
	using const_iterator=const iterator;
	using iterator_category=std::forward_iterator_tag;
	using value_type=typename std::iterator_traits<iterator>::value_type;
	using reference=typename std::iterator_traits<iterator>::reference;
	using pointer=typename std::iterator_traits<iterator>::pointer;
	using difference_type=typename std::iterator_traits<iterator>::difference_type;
	explicit filter_iterator(Predicate pred,Iterator first,Iterator last)noexcept
		:pred_(pred),first_(first),last_(last){skip();}
	filter_iterator& operator++()
	{
		++first_;
		skip();
		return *this;
	}
	filter_iterator& operator++(int)
	{
		filter_iterator tmp=*this;
		++first_;
		skip();
		return tmp;
	}
	value_type operator*()const{return *first_;}
	bool operator==(const filter_iterator& rhs)const{return first_==rhs.first_;}
	bool operator!=(const filter_iterator& rhs)const{return !operator==(rhs);}
private:
	void skip()noexcept{while(first_!=last_ && !pred_(*first_))++first_;}
	Predicate pred_;
	Iterator first_,last_;
};

template<class Predicate,class Iterator>
filter_iterator<Predicate,Iterator> make_filter_iterator(Predicate pred,Iterator first,Iterator last)
{
	return filter_iterator<Predicate,Iterator>(pred,first,last);
}

template<class Predicate>
struct filter_range_t{
	explicit filter_range_t(Predicate pred)noexcept:pred_(pred){}
	template<class Range>
	auto operator()(const Range& range)const
	{
		return make_range_iterator(make_filter_iterator(pred_,range.begin(),range.end()),make_filter_iterator(pred_,range.end(),range.end()));
	}
private:
	Predicate pred_;
};
template<class Predicate>
filter_range_t<Predicate> filterd(Predicate pred){return filter_range_t<Predicate>(pred);}

template<class Iterator>
struct copied_t{
	explicit copied_t(Iterator first,Iterator last)noexcept
		:first_(first),last_(last)
	{}
	template<class U>
	operator U()const{return U(first_,last_);}
private:
	Iterator first_,last_;
};

template<class Iterator>
copied_t<Iterator> make_copied_t(Iterator first,Iterator last){return copied_t<Iterator>(first,last);}

const auto print=[](const auto& r){
	std::copy(r.begin(),r.end(),std::ostream_iterator<typename std::remove_reference_t<decltype(r)>::value_type>(std::cout," "));
	std::cout<<std::endl;
	return r;
};
const auto copied=[](const auto& r){
	return make_copied_t(r.begin(),r.end());
};

template<class Range,class Functor>
auto operator|(const Range& r,const Functor f)
{
	return f(r);
}
}// namespace range_iterator_detail

using range_iterator_detail::print;
using range_iterator_detail::copied;
using range_iterator_detail::filterd;

struct digits final{
private:
	template<class,class=std::void_t<>>
	static constexpr bool has_iterator_category_v=false;
	template<class _Tp>
	static constexpr bool has_iterator_category_v<_Tp,std::void_t<typename _Tp::iterator_category>> =true;
public:
	using iterator=std::vector<std::size_t>::iterator;
	using const_iterator=std::vector<std::size_t>::const_iterator;
	using value_type=std::size_t;

	template<typename Integer,std::enable_if_t<std::is_integral<Integer>{},std::nullptr_t> =nullptr>
	explicit digits(Integer x)noexcept
		:size_(digits_calculation(x)),
		data_{digits_calculation(x)==1?static_cast<std::size_t>(x):0u}
	{
		if(!(size_==1)){
			data_.resize(size_);
			auto ten_v=static_cast<int>(std::pow(10,size_-1));
			for(std::size_t& value:data_){
				value=x/ten_v;
				x%=ten_v;
				ten_v/=10;
			}
		}
	}
	digits(const digits& oth)noexcept
		:size_(oth.size()),
		data_(oth.data_.cbegin(),oth.data_.cend())
	{}

	template<class Iterator,std::enable_if_t<has_iterator_category_v<Iterator>,std::nullptr_t> =nullptr>
	digits(Iterator first,Iterator last)noexcept
		:size_(std::distance(first,last)),
		data_(first,last)
	{}

	template<class L,class Operator,class R>
	digits(const Expression<L,Operator,R>& exp)noexcept
		:size_(exp.size()),
		data_(exp.size())
	{
		std::size_t index=0;
		for(auto& value:data_){
			value=exp[index++];
			if(digits_calculation(value)>1)effectivennes=false;
		}
	}

	template<class L,class Operator,class R>
	digits& operator=(const Expression<L,Operator,R>& exp)noexcept
	{
		size_=exp.size();
		data_.resize(size_);
		std::size_t i=0;
		for(auto& value:data_){
			value=exp[i++];
			if(digits_calculation(value)>1)effectivennes=false;
		}
		return *this;
	}

	std::size_t size()const noexcept{return size_;}
	
	auto operator[](const std::size_t index)const noexcept{return data_.at(index);}

	auto begin()const{return data_.begin();}
	auto end()const{return data_.end();}
	auto cbegin()const{return data_.cbegin();}
	auto cend()const{return data_.cend();}

	std::experimental::optional<unsigned long long int> real_value()const
	{
		if(effectivennes){
			unsigned long long int multi_ten=std::pow(10,size_);
			unsigned long long int result=0;
			for(auto& value:data_){
				result+=value*multi_ten;
				multi_ten/=10;
			}
			return result;
		}
		return std::experimental::nullopt;
	}

	digits& sort()
	{
		std::sort(data_.begin(),data_.end());
		return *this;
	}
	template<template<class>class Functor>
	digits& sort()
	{
		std::sort(data_.begin(),data_.end(),Functor<std::size_t>());
		return *this;
	}

private:
	template<typename Integer>
	std::size_t digits_calculation(Integer x)const{return std::log10(x)+1;}
	
	std::size_t size_;
	std::vector<std::size_t> data_;
	bool effectivennes=true;
};
} // namespace
#endif

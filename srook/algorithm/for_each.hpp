#ifndef INCLUDED_SROOK_ALGORITHM_FOREACH_HPP
#define INCLUDED_SROOK_ALGORITHM_FOREACH_HPP
#include<srook/config/require.hpp>
#include<srook/type_traits/has_iterator.hpp>
#include<srook/type_traits/is_callable.hpp>
#include<srook/iterator/range_iterator.hpp>
#include<type_traits>
#include<algorithm>
#include<tuple>
#include<initializer_list>

#include<iostream>
#define remove_ref_cv(x)\
	std::remove_reference_t<std::remove_cv_t<x>>

namespace srook{
inline namespace v1{

template<
	class Iterator,
	class Functor,
	REQUIRES(
			!has_iterator_v<remove_ref_cv(Iterator)> and
			is_callable_v<remove_ref_cv(Functor)>
	)
>
auto for_each(Iterator&& first,Iterator&& last,Functor&& functor) -> decltype(std::forward<Iterator>(first))
{
	std::for_each(std::forward<Iterator>(first),std::forward<Iterator>(last),std::forward<Functor>(functor));
	return std::forward<Iterator>(first);
}

template<
	class Range,
	class Functor,
	REQUIRES(
			(has_iterator_v<remove_ref_cv(Range)> or is_range_iterator_v<remove_ref_cv(Range)>) and
			is_callable_v<remove_ref_cv(Functor)>
	)
>
auto for_each(Range&& r,Functor&& functor) -> decltype(std::forward<Range>(r))
{
	std::for_each(std::begin(r),std::end(r),std::forward<Functor>(functor));
	return std::forward<Range>(r);
}

namespace{

template<class Functor>
void tuple_for_eacher(Functor&&){}
template<class Functor,class Head,class... Tail,REQUIRES(is_callable_v<remove_ref_cv(Functor)>)>
void tuple_for_eacher(Functor&& functor,Head&& head,Tail&&... tail)
{
	functor(std::forward<Head>(head));
	tuple_for_eacher(std::forward<Functor>(functor),std::forward<Tail>(tail)...);
}

template<class... Ts,class Functor,std::size_t... I,REQUIRES(is_callable_v<remove_ref_cv(Functor)>)>
std::tuple<Ts...>& tuple_for_eacher(std::tuple<Ts...>& t,Functor&& functor,const std::index_sequence<I...>&&)
{
	tuple_for_eacher(std::forward<Functor>(functor),std::get<I>(t)...);
	return t;
}

template<class... Ts,class Functor,std::size_t... I,REQUIRES(is_callable_v<remove_ref_cv(Functor)>)>
const std::tuple<Ts...>& tuple_for_eacher(const std::tuple<Ts...>& t,Functor&& functor,const std::index_sequence<I...>&&)
{
	tuple_for_eacher(std::forward<Functor>(functor),std::get<I>(t)...);
	return t;
}

} // anonymouse namespace

template<
	class Tuple,
	class Functor,
	REQUIRES(
			is_callable_v<remove_ref_cv(Functor)> 
			and
			!std::is_const<Tuple>::value
			and 
			(std::tuple_size<std::remove_reference_t<Tuple>>::value or !std::tuple_size<std::remove_reference_t<Tuple>>::value)
	)
>
auto for_each(Tuple&& t,Functor&& functor)
noexcept(noexcept(tuple_for_eacher(std::declval<decltype(static_cast<Tuple&&>(t))>(),std::declval<decltype(static_cast<Functor&&>(functor))>(),std::declval<std::make_index_sequence<std::tuple_size<std::decay_t<Tuple>>::value>>())))
-> decltype(tuple_for_eacher(std::forward<Tuple>(t),std::forward<Functor>(functor),std::make_index_sequence<std::tuple_size<std::decay_t<Tuple>>::value>()))
{
	return tuple_for_eacher(std::forward<Tuple>(t),std::forward<Functor>(functor),std::make_index_sequence<std::tuple_size<std::decay_t<Tuple>>::value>());
}

template<
	class... Ts,
	class Functor,
	REQUIRES(is_callable_v<remove_ref_cv(Functor)>)
>
auto for_each(const std::tuple<Ts...>& t,Functor&& functor)
noexcept(noexcept(tuple_for_eacher(t,std::declval<decltype(std::forward<Functor>(functor))>(),std::declval<std::make_index_sequence<std::tuple_size<std::tuple<Ts...>>::value>>())))
-> const std::tuple<Ts...>&
{
	return tuple_for_eacher(t,std::forward<Functor>(functor),std::make_index_sequence<std::tuple_size<std::tuple<Ts...>>::value>());
}

namespace{

template<class Range>
struct lvalue_counter{
	explicit constexpr lvalue_counter(Range& r,std::size_t value)
		:r_(r),value_(std::move(value)){}
	using reference_type=Range&;
protected:
	reference_type r_;
	std::size_t value_;
};
template<class Range>
struct rvalue_counter{
	explicit constexpr rvalue_counter(Range&& r,std::size_t value)
		:r_(std::move(r)),value_(std::move(value)){}
	using reference_type=Range&&;
protected:
	reference_type r_;
	std::size_t value_;
};

template<class Range>
using select_ref=typename std::conditional<std::is_lvalue_reference<Range>::value,lvalue_counter<remove_ref_cv(Range)>,rvalue_counter<remove_ref_cv(Range)>>::type;

template<class Range>
struct counter:select_ref<Range>{
	using select_ref<Range>::select_ref;
	using iterator=typename remove_ref_cv(Range)::iterator;
	using const_iterator=typename remove_ref_cv(Range)::const_iterator;

	iterator begin()const{return this->r_.begin();}
	iterator end()const{return this->r_.begin();}
	iterator begin(){return this->r_.begin();}
	iterator end(){return this->r_.end();}
	const_iterator cbegin()const{return this->r_.cbegin();}
	const_iterator cend()const{return this->r_.cend();}

	std::size_t& get_counter(){return this->value_;}
	typename select_ref<Range>::reference_type operator*(){return static_cast<typename select_ref<Range>::reference_type>(this->r_);}
};


template<bool,class Tuple>
struct counter_tuple{
	explicit constexpr counter_tuple(Tuple&& t,std::size_t value)
		:t_(std::move(t)),value_(std::move(value)){}
	
	Tuple&& operator*(){return std::move(t_);}
	std::size_t& get_counter(){return value_;}

	using reference_type=Tuple&&;
private:
	reference_type t_;
	std::size_t value_;
};

template<class Tuple>
struct counter_tuple<true,Tuple>{
	explicit constexpr counter_tuple(Tuple& t,std::size_t value)
		:t_(t),value_(std::move(value)){}
	
	Tuple& operator*(){return t_;}
	std::size_t& get_counter(){return value_;}

	using reference_type=Tuple&;
private:
	reference_type t_;
	std::size_t value_;
};

template<class Iterator>
struct counter_iters{
	explicit constexpr counter_iters(Iterator first,Iterator last,std::size_t value)
		:first_(std::move(first)),last_(std::move(last)),value_(std::move(value)){}
	
	using iterator=remove_ref_cv(Iterator);
	using const_iterator=const iterator;
	
	iterator begin()const{return first_;}
	iterator end()const{return last_;}
	iterator begin(){return first_;}
	iterator end(){return last_;}
	const_iterator cbegin()const{return first_;}
	const_iterator cend()const{return last_;}

	std::size_t& get_counter(){return value_;}
private:
	Iterator first_,last_;
	std::size_t value_;
};

template<class Functor>
void counting_for_eacher(std::size_t&,Functor&&){}

template<class Functor,class Head,class... Tail,REQUIRES(is_callable_v<remove_ref_cv(Functor)>)>
void counting_for_eacher(std::size_t& counter,Functor&& functor_,Head&& head,Tail&&... tail)
{
	functor_(std::forward<Head>(head),counter);
	counting_for_eacher(++counter,std::forward<Functor>(functor_),std::forward<Tail>(tail)...);
}

template<class Tuple,class Functor,std::size_t... I,REQUIRES(is_callable_v<remove_ref_cv(Functor)>)>
auto counting_for_eacher(Tuple&& t,std::size_t& counter,Functor&& functor,const std::index_sequence<I...>&&) -> decltype(std::forward<Tuple>(t))
{
	counting_for_eacher(counter,std::forward<Functor>(functor),std::get<I>(t)...);
	return std::forward<Tuple>(t);
}

} // anonymouse namespace

template<class Tuple>
constexpr auto make_counter(Tuple&& t,std::size_t value=0)
-> decltype(
		std::tuple_size<remove_ref_cv(Tuple)>::value,
		counter_tuple<std::is_lvalue_reference<Tuple>::value,Tuple>(std::forward<Tuple>(t),std::move(value))
)
{
	return counter_tuple<std::is_lvalue_reference<Tuple>::value,Tuple>(std::forward<Tuple>(t),std::move(value));
}

template<class Range,REQUIRES(has_iterator_v<remove_ref_cv(Range)> or is_range_iterator_v<remove_ref_cv(Range)>)>
constexpr auto make_counter(Range&& r,std::size_t value=0) -> counter<decltype(std::forward<Range>(r))>
{
	return counter<decltype(std::forward<Range>(r))>(std::forward<Range>(r),std::move(value));
}

template<class T>
constexpr auto make_counter(const std::initializer_list<T>& init_list,std::size_t value=0) -> counter<const std::initializer_list<T>&>
{
	return counter<const std::initializer_list<T>&>(init_list,std::move(value));
}

template<class Iterator,REQUIRES(not has_iterator_v<remove_ref_cv(Iterator)>)>
constexpr auto make_counter(Iterator&& first,Iterator&& last,std::size_t value=0) -> counter_iters<remove_ref_cv(Iterator)>
{
	return counter_iters<Iterator>(std::forward<Iterator>(first),std::forward<Iterator>(last),std::move(value));
}

template<
	bool b,
	class Tuple,
	class Functor,
	REQUIRES(is_callable_v<remove_ref_cv(Functor)>)
>
constexpr auto for_each(counter_tuple<b,Tuple> t,Functor&& functor) -> typename counter_tuple<b,Tuple>::reference_type
{
	return counting_for_eacher(std::forward<Tuple>(*t),t.get_counter(),std::forward<Functor>(functor),std::make_index_sequence<std::tuple_size<remove_ref_cv(Tuple)>::value>());
}

template<
	class Range,
	class Functor,
	REQUIRES(
			(has_iterator_v<remove_ref_cv(Range)> or is_range_iterator_v<remove_ref_cv(Range)>) and 
			is_callable_v<remove_ref_cv(Functor)>
	)
>
auto for_each(counter<Range> cr,Functor&& functor) -> typename counter<Range>::reference_type
{
	for(typename remove_ref_cv(decltype(cr))::iterator iter=std::begin(cr); iter!=std::end(cr); ++iter){
		functor(*iter,cr.get_counter());
		++cr.get_counter();
	}
	return *cr;
}

template<
	class Iterator,
	class Functor,
	REQUIRES(!has_iterator_v<remove_ref_cv(Iterator)> and is_callable_v<remove_ref_cv(Functor)>)
>
auto for_each(counter_iters<Iterator> cr,Functor&& functor) -> decltype(std::begin(cr))
{
	for(typename counter_iters<Iterator>::iterator iter=std::begin(cr); iter!=std::end(cr); ++iter){
		functor(*iter,cr.get_counter());
		++cr.get_counter();
	}
	return std::begin(cr);
}

template<
	class T,
	class Functor,
	REQUIRES(is_callable_v<remove_ref_cv(Functor)>)
>
auto for_each(std::initializer_list<T> init_list,Functor&& functor) -> decltype(std::begin(init_list))
{
	return for_each(std::begin(init_list),std::end(init_list),std::forward<Functor>(functor));
}


} // inline namespace v1
} // namespace srook

#undef remove_cv_t
#endif

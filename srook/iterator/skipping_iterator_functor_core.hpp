#ifndef INCLUDED_SROOK_SKIPPING_ITERATOR_CORE_HPP
#define INCLUDED_SROOK_SKIPPING_ITERATOR_CORE_HPP
#include<srook/type_traits/has_iterator.hpp>
#include<srook/type_traits/is_callable.hpp>
#include<srook/iterator/range_iterator.hpp>
#include<srook/config/require.hpp>
#include<srook/utility/lambda_wrapper.hpp>
#include<iterator>

namespace srook{
inline namespace v1{

template<class Iterator,class Predicate,class Skipper>
struct skipping_iterator_functor_core{
	using iterator_category=std::forward_iterator_tag;
	using iterator=Iterator;
	using const_iterator=iterator;
	using value_type=typename std::iterator_traits<Iterator>::value_type;
	using reference=typename std::iterator_traits<Iterator>::reference;
	using difference_type=typename std::iterator_traits<Iterator>::difference_type;
	using pointer=typename std::iterator_traits<Iterator>::pointer;

	template<REQUIRES(!has_iterator_v<Iterator> && is_callable_v<Predicate>)>
	explicit constexpr skipping_iterator_functor_core(Iterator first,Iterator last,Predicate pred,Skipper skipper)
		:first_(std::move(first)),last_(std::move(last)),pred_(std::move(pred)),skipper_(std::move(skipper))
	{
		skipper_(first_,last_,pred_);
	}
	iterator begin()const{return first_;}
	iterator end()const{return last_;}
	iterator begin(){return first_;}
	iterator end(){return last_;}
	const_iterator cbegin()const{return first_;}
	const_iterator cend()const{return last_;}
	reference operator*()const{return *first_;}
	reference operator*(){return *first_;}
	constexpr bool operator==(const skipping_iterator_functor_core& iter)const noexcept{return iter.first_==first_;}
	constexpr bool operator!=(const skipping_iterator_functor_core& iter)const noexcept{return !operator==(iter);}
	skipping_iterator_functor_core& operator++()
	{
		++first_;
		skipper_(first_,last_,pred_);
		return *this;
	}
	skipping_iterator_functor_core operator++(int)
	{
		skipping_iterator_functor_core tmp=*this;
		++first_;
		skipper_(first_,last_,pred_);
		return tmp;
	}

	void* operator new(std::size_t)=delete;
	void operator delete(void*)=delete;
protected:
	Iterator first_,last_;
	lambda_wrapper<Predicate> pred_;
	Skipper skipper_;
};

} // inline namespace v1
} // namespace srook

#endif

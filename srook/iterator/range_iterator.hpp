// Copyright (C) 2017 roki
#ifndef SROOK_INCLUDED_RANGE_ITERATOR
#define SROOK_INCLUDED_RANGE_ITERATOR
#include<iterator>
#include<type_traits>

namespace srook{
inline namespace v1{

struct Srook_range_iterator_type_{Srook_range_iterator_type_()=delete;};

template<class Iterator>
struct range_iterator final{
private:
	struct OnlyHeadAndTail_Iterator_Tag{OnlyHeadAndTail_Iterator_Tag()=delete;};
public:
	using iterator_category=OnlyHeadAndTail_Iterator_Tag;
	using iterator=Iterator;
	using const_iterator=iterator;
	using value_type=typename std::iterator_traits<iterator>::value_type;
	using pointer=typename std::iterator_traits<iterator>::pointer;
	using difference_type=typename std::iterator_traits<iterator>::difference_type;
	using reference=typename std::iterator_traits<iterator>::reference;

	using SROOK_RANGE_ITERATOR_TYPE=Srook_range_iterator_type_;
		
	explicit constexpr range_iterator(iterator&& first,iterator&& last)noexcept
		:first_(std::move(first)),last_(std::move(last)){}

	constexpr iterator begin()const noexcept{return first_;}
	constexpr iterator end()const noexcept{return last_;}
	constexpr const_iterator cbegin()const noexcept{return first_;}
	constexpr const_iterator cend()const noexcept{return last_;}
	constexpr iterator begin()noexcept{return first_;}
	constexpr iterator end()noexcept{return last_;}
private:
	iterator first_,last_;
};

template<class,class=std::void_t<>>
constexpr bool is_range_iterator_v = std::false_type::value;
template<class T>
constexpr bool is_range_iterator_v<T,std::void_t<typename T::SROOK_RANGE_ITERATOR_TYPE>> = std::true_type::value;

template<class Iterator>
constexpr range_iterator<Iterator> make_range_iterator(Iterator first,Iterator last)
{
	return range_iterator<Iterator>(std::move(first),std::move(last));
}

} // inline namespace v1
} // namespace
#endif

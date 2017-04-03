#ifndef INCLUDED_SROOK_RANGE_ALGORITHM_VECTOR_CALCULATOR_HPP
#define INCLUDED_SROOK_RANGE_ALGORITHM_VECTOR_CALCULATOR_HPP
#if __has_include(<type_traits>) and __cplusplus <= 201703L

#include<srook/optional.hpp>
#include<srook/range/adaptor/adaptor_operator.hpp>
#include<srook/config/require.hpp>
#include<iterator>
#include<type_traits>

namespace srook{
namespace pipealgo{
namespace detail{

template<class L,class Operator,class R>
struct Expression final{
private:
	const L& l_;
	const R& r_;
public:
	using last_type=R;
	using index_type=std::size_t;
	using result_type=decltype(Operator::apply(l_[index_type()],r_[index_type()]));

	constexpr Expression(const L& l,const R& r)noexcept:l_(l),r_(r){}

	constexpr decltype(l_.size()) size()const noexcept
	{
		return l_.size();
	}

	constexpr result_type operator[](index_type index)const
	{
		bool l_outof_range=l_.size()<=index;
		bool r_outof_range=r_.size()<=index;

		if(l_outof_range and r_outof_range)
			return static_cast<result_type>(0);
		else if(l_outof_range)
			return Operator::apply(static_cast<result_type>(0),r_[index]);
		else if(r_outof_range)
			return Operator::apply(l_[index],static_cast<result_type>(0));
		else
			return Operator::apply(l_[index],r_[index]);
	}
};

struct Plus final{
	template<class L,class R>
	static constexpr decltype(std::declval<L>()+std::declval<R>())
	apply(const L& l,const R& r)noexcept
	{
		return l+r;
	}
};

struct Minus final{
	template<class L,class R>
	static constexpr decltype(std::declval<L>()-std::declval<R>())
	apply(const L& l,const R& r)noexcept
	{
		return l-r;
	}
};

struct Multiply final{
	template<class L,class R>
	static constexpr decltype(std::declval<L>()*std::declval<R>())
	apply(const L& l,const R& r)noexcept
	{
		return l*r;
	}
};

struct Division final{
	template<class L,class R>
	static constexpr decltype(std::declval<L>()*std::declval<R>())
	apply(const L& l,const R& r)noexcept(false)
	{
		return l/r;
	}
};

template<class RightRange>
struct assign_range_and_range{
	explicit constexpr assign_range_and_range(const RightRange& right_range,typename RightRange::iterator iter)noexcept
		:right_range_(right_range),iter_(iter){}

	template<class LeftRange>
	LeftRange& operator()(LeftRange&& l)
	{
		if(!iter_)
			std::copy(std::begin(right_range_),std::next(right_range_.begin(),l.size()),std::begin(l));
		else
			std::copy(std::begin(right_range_),std::next(right_range_.begin(),l.size()),iter_);

		return l;
	}
private:
	const RightRange& right_range_;
	typename RightRange::iterator iter_;
};

template<class L,class Operator,class R,class Iterator>
struct assign_range_and_expression{
	explicit constexpr assign_range_and_expression(const Expression<L,Operator,R>& exp,Iterator iter)noexcept
		:exp_(exp),iter_(std::move(iter)){}

	template<class LeftRange>
	LeftRange& operator()(LeftRange&& l)
	{
		for(std::size_t i=0; i<exp_.size(); ++i)iter_++=exp_[i];
		++iter_;
		return l;
	}
private:
	const Expression<L,Operator,R>& exp_;
	Iterator iter_;
};

template<class L,class Operator,class R>
struct assign_range_and_expression<L,Operator,R,nullopt_t>{
	explicit constexpr assign_range_and_expression(const Expression<L,Operator,R>& exp)noexcept
		:exp_(exp){}

	template<class LeftRange>
	LeftRange& operator()(LeftRange&& l)
	{
		std::size_t i=0;
		for(typename std::remove_reference_t<LeftRange>::value_type& value:l)value=exp_[i++];
		return l;
	}
private:
	const Expression<L,Operator,R>& exp_;
};


} // namespace detail

namespace vector_calculator{

template<
	class LeftRange,
	class RightRange,
	REQUIRES(
		std::is_convertible<typename LeftRange::value_type,typename RightRange::value_type>::value
		and
		std::is_same<typename std::iterator_traits<typename LeftRange::iterator>::iterator_category,std::random_access_iterator_tag>::value
		and
		std::is_same<typename std::iterator_traits<typename RightRange::iterator>::iterator_category,std::random_access_iterator_tag>::value
	)
>
constexpr detail::Expression<LeftRange,detail::Plus,RightRange> 
operator+(const LeftRange& l,const RightRange& r)noexcept
{
	return detail::Expression<LeftRange,detail::Plus,RightRange>(l,r);
}

template<
	class... L,
	class RightRange,
	REQUIRES(
		std::is_same<typename std::iterator_traits<typename RightRange::iterator>::iterator_category,std::random_access_iterator_tag>::value
	)
>
constexpr detail::Expression<detail::Expression<L...>,detail::Plus,RightRange>
operator+(const detail::Expression<L...>& l,RightRange& r)noexcept
{
	return detail::Expression<detail::Expression<L...>,detail::Plus,RightRange>(l,r);
}

template<
	class LeftRange,
	class... R,
	REQUIRES(
		std::is_same<typename std::iterator_traits<typename LeftRange::iterator>::iterator_category,std::random_access_iterator_tag>::value
	)
>
constexpr detail::Expression<LeftRange,detail::Plus,detail::Expression<R...>>
operator+(const LeftRange& l,const detail::Expression<R...>& r)noexcept
{
	return detail::Expression<LeftRange,detail::Plus,detail::Expression<R...>>(l,r);
}

template<
	class LeftRange,
	class RightRange,
	REQUIRES(
		std::is_convertible<typename LeftRange::value_type,typename RightRange::value_type>::value
		and
		std::is_same<typename std::iterator_traits<typename LeftRange::iterator>::iterator_category,std::random_access_iterator_tag>::value
		and
		std::is_same<typename std::iterator_traits<typename RightRange::iterator>::iterator_category,std::random_access_iterator_tag>::value
	)
>
constexpr detail::Expression<LeftRange,detail::Minus,RightRange>
operator-(const LeftRange& l,const RightRange& r)noexcept
{
	return detail::Expression<LeftRange,detail::Minus,RightRange>(l,r);
}

template<
	class... L,
	class RightRange,
	REQUIRES(
		std::is_same<typename std::iterator_traits<typename RightRange::iterator>::iterator_category,std::random_access_iterator_tag>::value
	)
>
constexpr detail::Expression<detail::Expression<L...>,detail::Minus,RightRange>
operator-(const detail::Expression<L...>& l,const RightRange& r)noexcept
{
	return detail::Expression<detail::Expression<L...>,detail::Minus,RightRange>(l,r);
}

template<
	class LeftRange,
	class... R,
	REQUIRES(
		std::is_same<typename std::iterator_traits<typename LeftRange::iterator>::iterator_category,std::random_access_iterator_tag>::value
	)
>
constexpr detail::Expression<LeftRange,detail::Minus,detail::Expression<R...>>
operator-(const LeftRange& l,const detail::Expression<R...>& r)noexcept
{
	return detail::Expression<LeftRange,detail::Minus,detail::Expression<R...>>(l,r);
}

template<
	class LeftRange,
	class RightRange,
	REQUIRES(
		std::is_convertible<typename LeftRange::value_type,typename RightRange::value_type>::value
		and
		std::is_same<typename std::iterator_traits<typename LeftRange::iterator>::iterator_category,std::random_access_iterator_tag>::value
		and
		std::is_same<typename std::iterator_traits<typename RightRange::iterator>::iterator_category,std::random_access_iterator_tag>::value
	)
>
constexpr detail::Expression<LeftRange,detail::Multiply,RightRange>
operator*(const LeftRange& l,const RightRange& r)noexcept
{
	return detail::Expression<LeftRange,detail::Multiply,RightRange>(l,r);
}

template<
	class... L,
	class RightRange,
	REQUIRES(
			std::is_same<typename std::iterator_traits<typename RightRange::iterator>::iterator_category,std::random_access_iterator_tag>::value
	)
>
constexpr detail::Expression<detail::Expression<L...>,detail::Multiply,RightRange>
operator*(const detail::Expression<L...>& l,const RightRange& r)noexcept
{
	return detail::Expression<detail::Expression<L...>,detail::Multiply,RightRange>(l,r);
}

template<
	class LeftRange,
	class... R,
	REQUIRES(
			std::is_same<typename std::iterator_traits<typename LeftRange::iterator>::iterator_category,std::random_access_iterator_tag>::value
	)
>
constexpr detail::Expression<LeftRange,detail::Multiply,detail::Expression<R...>>
operator*(const LeftRange& l,const detail::Expression<R...>& r)noexcept
{
	return detail::Expression<LeftRange,detail::Multiply,detail::Expression<R...>>(l,r);
}

template<
	class LeftRange,
	class RightRange,
	REQUIRES(
			std::is_same<typename std::iterator_traits<typename LeftRange::iterator>::iterator_category,std::random_access_iterator_tag>::value
			and
			std::is_same<typename std::iterator_traits<typename RightRange::iterator>::iterator_category,std::random_access_iterator_tag>::value
			and
			std::is_convertible<typename LeftRange::value_type,typename RightRange::value_type>::value
	)
>
constexpr detail::Expression<LeftRange,detail::Division,RightRange>
operator/(const LeftRange& l,const RightRange& r)noexcept(false)
{
	return detail::Expression<LeftRange,detail::Division,RightRange>(l,r);
}

template<
	class... L,
	class RightRange,
	REQUIRES(
			std::is_same<typename std::iterator_traits<typename RightRange::iterator>::iterator_category,std::random_access_iterator_tag>::value
	)
>
constexpr detail::Expression<detail::Expression<L...>,detail::Division,RightRange>
operator/(const detail::Expression<L...>& l,const RightRange& r)noexcept(false)
{
	return detail::Expression<detail::Expression<L...>,detail::Division,RightRange>(l,r);
}

template<
	class LeftRange,
	class... R,
	REQUIRES(
			std::is_same<typename std::iterator_traits<typename LeftRange::iterator>::iterator_category,std::random_access_iterator_tag>::value
	)
>
constexpr detail::Expression<LeftRange,detail::Division,detail::Expression<R...>>
operator/(const LeftRange& l,const detail::Expression<R...>& r)noexcept(false)
{
	return detail::Expression<LeftRange,detail::Division,detail::Expression<R...>>(l,r);
}


} // namesapce vector_calculator

template<
	class RightRange,
	REQUIRES(std::is_same<typename std::iterator_traits<typename RightRange::iterator>::iterator_category,std::random_access_iterator_tag>::value)
>
constexpr detail::assign_range_and_range<RightRange>
assign(RightRange&& r,typename RightRange::iterator iter=nullptr)
{
	return detail::assign_range_and_range<std::remove_reference_t<RightRange>>(std::forward<RightRange>(r),std::move(iter));
}

template<
	class L,
	class Operator,
	class R
>
constexpr detail::assign_range_and_expression<L,Operator,R,nullopt_t>
assign(const detail::Expression<L,Operator,R>& exp)
{
	return detail::assign_range_and_expression<L,Operator,R,nullopt_t>(exp);
}

template<
	class L,
	class Operator,
	class R,
	class Iterator,
	REQUIRES(
			std::is_same<typename std::iterator_traits<Iterator>::iterator_category,std::random_access_iterator_tag>::value
			or
			std::is_same<typename std::iterator_traits<Iterator>::iterator_category,std::forward_iterator_tag>::value
			or
			std::is_same<typename std::iterator_traits<Iterator>::iterator_category,std::output_iterator_tag>::value
			or
			std::is_same<typename std::iterator_traits<Iterator>::iterator_category,std::bidirectional_iterator_tag>::value
	)
>
constexpr detail::assign_range_and_expression<L,Operator,R,Iterator>
assign(const detail::Expression<L,Operator,R>& exp,Iterator iter)
{
	return detail::assign_range_and_expression<L,Operator,R,Iterator>(exp,std::move(iter));
}

} // namespace pipealgo
} // namespace srook

#endif
#endif

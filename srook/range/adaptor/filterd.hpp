// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_ADAPTOR_FILTERD_HPP
#define INCLUDED_ADAPTOR_FILTERD_HPP
#include<srook/iterator/range_iterator.hpp>
#include<srook/iterator/range_iterators/filterd_iterator.hpp>
#include<srook/type_traits/is_callable.hpp>
#include<srook/config/require.hpp>
#include<type_traits>
#include<srook/iterator/range_iterator.hpp>

namespace srook{
namespace adaptors{
namespace detail{
inline namespace v1{

template<class Predicate>
struct range_filter{
    explicit constexpr range_filter(Predicate& predicate)noexcept
        :pred(predicate){}
    explicit constexpr range_filter(Predicate&& predicate)noexcept
        :pred(std::move(predicate)){}
    
    template<
		class Range,
		REQUIRES(std::is_const<std::remove_reference_t<Range>>::value)
	>
    constexpr range_iterator<
		filterd_iterator<Predicate,typename std::remove_cv_t<std::remove_reference_t<Range>>::const_iterator>
	>
	operator()(Range&& r)noexcept
    {
        return make_range_iterator(
            make_filterd_iterator(std::move(pred),std::begin(r),std::end(r)),
            make_filterd_iterator(std::move(pred),std::end(r),std::end(r))
        );
    }

	template<
		class Range,
		REQUIRES(!std::is_const<std::remove_reference_t<Range>>::value)
	>
	constexpr range_iterator<
		filterd_iterator<Predicate,typename std::remove_cv_t<std::remove_reference_t<Range>>::iterator>
	>
	operator()(Range&& r)noexcept
	{
		return make_range_iterator(
				make_filterd_iterator(std::move(pred),std::begin(r),std::end(r)),
				make_filterd_iterator(std::move(pred),std::end(r),std::end(r))
		);
	}

private:
	Predicate pred;
};

template<
	class Predicate,
	REQUIRES(is_callable_v<std::remove_cv_t<std::remove_reference_t<Predicate>>>)
>
constexpr range_filter<std::remove_cv_t<std::remove_reference_t<Predicate>>> 
filterd(Predicate&& pred)
{
    return range_filter<
        std::remove_cv_t<std::remove_reference_t<Predicate>>
    >(std::forward<Predicate>(pred));
}

} // inline namespace v1
} // namespace detail

using detail::filterd;

} // namespace adaptors
} // namespace srook
#endif

#ifndef SROOK_INCLUDED_RANGE_ADAPTOR_COPIED
#define SROOK_INCLUDED_RANGE_ADAPTOR_COPIED
#include<srook/range/adaptor/adaptor_operator.hpp>
#include<srook/iterator/range_iterator.hpp>
#include<type_traits>
namespace srook{

template<class Iterator>
struct copied_t{
	using value_type=typename std::iterator_traits<Iterator>::value_type;
	using pointer=typename std::iterator_traits<Iterator>::pointer;
	using difference_type=typename std::iterator_traits<Iterator>::difference_type;
	using reference=typename std::iterator_traits<Iterator>::reference;

	explicit constexpr copied_t(Iterator& first,Iterator last)noexcept
		:first_(first),last_(last){}
	explicit constexpr copied_t(Iterator&& first,Iterator&& last)noexcept
		:first_(std::move(first)),last_(std::move(last)){}
	template<class Range>
	constexpr operator Range()
	{
		return Range(first_,last_);
	}
private:
	const Iterator first_,last_;
};
template<class Iterator>
copied_t<std::remove_reference_t<Iterator>> make_copied_t(Iterator&& first,Iterator&& last)
{
	return copied_t<std::remove_reference_t<Iterator>>(std::forward<Iterator>(first),std::forward<Iterator>(last));
}
const auto copied=[](auto&& r)noexcept{return make_copied_t(r.cbegin(),r.cend());};

}
#endif

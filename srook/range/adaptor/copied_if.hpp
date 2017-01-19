#ifndef INCLUDED_SROOK_ADAPROT_COPIED_IF_HPP
#define INCLUDED_SROOK_ADAPROT_COPIED_IF_HPP
#include<srook/range/adaptor/adaptor_operator.hpp>
#include<srook/range/adaptor/filterd.hpp>
namespace srook{
namespace adaptors{
inline namespace v1{

template<class Iterator,class Predicate>
struct copied_if_t{
	explicit constexpr copied_if_t(Iterator first,Iterator last,Predicate pred)
		:first_(std::move(first)),last_(std::move(last)),pred_(std::move(pred)){}
	template<class U>
	operator U()
	{
		return U(
				srook::make_filterd_iterator(std::move(pred_),std::move(first_),std::move(last_)),
				srook::make_filterd_iterator(std::move(pred_),std::move(last_),std::move(last_))
		);
	}
private:
	Iterator first_,last_;
	Predicate pred_;
};
template<class Iterator,class Predicate>
constexpr copied_if_t<std::decay_t<Iterator>,std::decay_t<Predicate>>
make_copied_if_t(Iterator&& first,Iterator&& last,Predicate&& pred)
{
	return copied_if_t<
		std::decay_t<Iterator>,
		std::decay_t<Predicate>
	>(std::forward<Iterator>(first),std::forward<Iterator>(last),std::forward<Predicate>(pred));
}
template<class Predicate>
struct copied_ifer{
	explicit constexpr copied_ifer(Predicate pred)
		:pred_(std::move(pred)){}
	template<class Range>
	copied_if_t<typename std::decay_t<Range>::const_iterator,Predicate> operator()(Range&& r)
	{
		return make_copied_if_t(r.cbegin(),r.cend(),std::move(pred_));
	}
private:
	Predicate pred_;
};
template<class Predicate>
constexpr copied_ifer<std::decay_t<Predicate>> copied_if(Predicate&& pred)
{
	return copied_ifer<std::decay_t<Predicate>>(std::forward<Predicate>(pred));
}

} // inline namespace v1
} // namespace adaptors
} // namespace srook
#endif

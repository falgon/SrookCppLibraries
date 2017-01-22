#ifndef INCLUDED_ADAPTOR_FILTERD_HPP
#define INCLUDED_ADAPTOR_FILTERD_HPP
#include<srook/iterator/range_iterator.hpp>
#include<srook/iterator/filterd_iterator.hpp>

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
    
    template<class Range>
    constexpr range_iterator<
        filterd_iterator<
            Predicate,
            typename std::remove_reference_t<Range>::const_iterator
        >
    >
    operator()(Range&& r)noexcept
    {
        return make_range_iterator(
            make_filterd_iterator(std::move(pred),r.cbegin(),r.cend()),
            make_filterd_iterator(std::move(pred),r.cend(),r.cend())
        );
    }
private:
	Predicate pred;
};
template<class Predicate>
constexpr range_filter<std::remove_reference_t<Predicate>> 
filterd(Predicate&& pred)
{
    return range_filter<
        std::remove_reference_t<Predicate>
    >(std::forward<Predicate>(pred));
}

} // inline namespace v1
} // namespace detail

using detail::filterd;

} // namespace adaptors
} // namespace srook
#endif

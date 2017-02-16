#ifndef INCLUDED_SROOK_ADAPTORS_COPY_BACKWORD_HPP
#define INCLUDED_SROOK_ADAPTORS_COPY_BACKWORD_HPP
#include<srook/range/adaptor/adaptor_operator.hpp>
#include<srook/type_traits/has_iterator.hpp>
#include<srook/config/require.hpp>
#include<iterator>
namespace srook{
namespace adaptors{
namespace detail{
inline namespace v1{

template<class Iterator>
struct copied_backword_t{
	explicit constexpr copied_backword_t(Iterator first,Iterator last)
		:first_(std::move(first)),last_(std::move(last)){}
	template<class U>
	operator U()
	{
		return U(std::make_reverse_iterator(last_),std::make_reverse_iterator(first_));
	}
private:
	const Iterator first_,last_;
};
template<
	class Iterator,
	REQUIRES(!has_iterator_v<std::remove_reference_t<std::remove_cv_t<Iterator>>>)
>
copied_backword_t<Iterator> make_copied_backword(Iterator first,Iterator last)
{
	return copied_backword_t<Iterator>(std::move(first),std::move(last));
}
const auto copied_backward=[](auto&& r){return make_copied_backword(r.begin(),r.end());};

} // inline namespace v1
} // namespace detail

using detail::copied_backward;

} // namespace mpl
} // namespace srook
#endif

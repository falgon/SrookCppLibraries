#ifndef INCLUDED_ADAPTOR_PRINT_HPP
#define INCLUDED_ADAPTOR_PRINT_HPP
#include<iterator>
#include<iostream>
#include<srook/iterator/range_iterator.hpp>
#include<srook/range/adaptor/adaptor_operator.hpp>
#include<srook/type_traits/is_callable.hpp>
#include<srook/type_traits/has_iterator.hpp>
#include<srook/config/require.hpp>
#include<algorithm>

namespace srook{
namespace adaptors{
namespace detail{

inline namespace v1{

template<class OutputStream,class Delimiter_t>
struct print_t final{
	explicit constexpr print_t(OutputStream& outputstream,Delimiter_t&& delimiter)
		:outputstream_(outputstream),delimiter_(std::forward<Delimiter_t>(delimiter)){}
	
	template<class Range,REQUIRES(has_iterator_v<std::decay_t<Range>> || is_range_iterator_v<std::decay_t<Range>>)>
	range_iterator<typename std::remove_reference_t<Range>::iterator> operator()(Range&& r)
	{
		std::copy(r.begin(),r.end(),std::ostream_iterator<typename std::remove_reference_t<Range>::value_type>(outputstream_,delimiter_));
		return make_range_iterator(r.begin(),r.end());
	}
private:
	OutputStream& outputstream_;
	const Delimiter_t delimiter_;
};
template<class Ostream=decltype(std::cout),class Delimiter_t=const char*>
print_t<Ostream,Delimiter_t> print(Ostream& os=std::cout,Delimiter_t&& delimiter=" ")
{
	return print_t<Ostream,Delimiter_t>(os,std::forward<Delimiter_t>(delimiter));
}


} // inline namespace v1
} // namespace detail

using detail::print;

} // namespace adaptors
} // namespace srook

#endif

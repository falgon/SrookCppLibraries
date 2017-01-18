#ifndef INCLUDED_ADAPTOR_PRINT_HPP
#define INCLUDED_ADAPTOR_PRINT_HPP
#include<iterator>
#include<iostream>
#include<srook/iterator/range_iterator.hpp>
#if __has_include(<boost/range/algorithm/copy.hpp>)
#define POSSIBLE_TO_BOOST_COPY
#include<boost/range/algorithm/copy.hpp>
#elif 
#define POSSIBLE_TO_STD_COPY
#include<algorithm>
#endif

namespace srook{
namespace adaptors{
inline namespace v1{

template<class OutputStream,class Delimiter_t>
struct print_t final{
	explicit constexpr print_t(OutputStream& outputstream,const Delimiter_t& delimiter)
		:outputstream_(outputstream),delimiter_(delimiter){}
	explicit constexpr print_t(OutputStream& outputstream,Delimiter_t&& delimiter)
		:outputstream_(outputstream),delimiter_(std::forward<Delimiter_t>(delimiter)){}
	
	template<class Range>
	range_iterator<typename std::remove_reference_t<Range>::const_iterator> operator()(Range&& r)
	{
#ifdef POSSIBLE_TO_BOOST_COPY
		boost::copy(r,std::ostream_iterator<typename std::remove_reference_t<Range>::value_type>(outputstream_,delimiter_));
#endif 
#ifdef POSSIBLE_TO_STD_COPY
		std::copy(r.cbegin(),r.cend(),std::otream_iterator<typename std::remove_reference_t<Range>::value_type>(outputstream_,delimiter_));
#endif
		return make_range_iterator(r.cbegin(),r.cend());
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
} // namespace adaptors
} // namespace srook

#ifdef POSSIBLE_TO_BOOST_COPY
#undef POSSIBLE_TO_BOOST_COPY
#endif
#ifdef POSSIBLE_TO_STD_COPY
#undef POSSIBLE_TO_STD_COPY
#endif

#endif

#ifndef INCLUDED_SROOK_ITERATOR_OSTREAM_JOINER_HPP
#define INCLUDED_SROOK_ITERATOR_OSTREAM_JOINER_HPP

#if __cplusplus <= 201103L
#include<bits/c++14_warning.h>
#else

#include<type_traits>
#include<iterator>
#include<iosfwd>

namespace srook{
inline namespace fundamentals_v2{

template<class Delim,typename CharT = char,class Traits = std::char_traits<CharT>>
struct ostream_joiner{
	typedef CharT char_type;
	typedef Traits traits_type;
	typedef std::basic_ostream<CharT,Traits> ostream_type;
	typedef std::output_iterator_tag iterator_category;
	typedef void value_type;
	typedef void difference_type;
	typedef void pointer;
	typedef void reference;

	ostream_joiner(ostream_type& os,const Delim& delimiter)noexcept(std::is_nothrow_copy_constructible<Delim>::value)
		:out(std::addressof(os)),delim(delimiter){}
	ostream_joiner(ostream_type& os,Delim&& delimiter)noexcept(std::is_nothrow_move_constructible<Delim>::value)
		:out(std::addressof(os)),delim(std::move(delimiter)){}
	
	template<typename T>
	ostream_joiner<Delim,CharT,Traits>& operator=(const T& value)
	{
		if(!first) *out << delim;
		first = false;
		*out << value;
		return *this;
	}

	ostream_joiner<Delim,CharT,Traits>& operator*()noexcept{return *this;}
	ostream_joiner<Delim,CharT,Traits>& operator++()noexcept{return *this;}
	ostream_joiner<Delim,CharT,Traits>& operator++(int)noexcept{return *this;}
private:
	std::basic_ostream<CharT,Traits>* out;
	Delim delim;
	bool first = true;
};

template<typename CharT,class Traits,class Delim>
inline ostream_joiner<std::decay_t<Delim>,CharT,Traits> make_ostream_joiner(std::basic_ostream<CharT,Traits>& os,Delim&& delimiter)
{
	return {os,std::forward<Delim>(delimiter)};
}

} // inline namespace fundamentals_v2
} // namespace srook

#endif
#endif

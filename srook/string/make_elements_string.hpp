#ifndef INCLUDED_MAKE_ELEMENtS_STRING_HPP
#define INCLUDED_MAKE_ELEMENtS_STRING_HPP

#include<sstream>
#include<string>
#include<map>
#include<queue>
#include<stack>
#include<utility>

#if __has_include(<boost/fusion/adapted/std_tuple.hpp>)
#define POSSIBLE_TO_INCLUDE_BOOST_FUSION_STD_TUPLE
#endif
#if __has_include(<boost/fusion/include/for_each.hpp>)
#define POSSIBLE_TO_INCLUDE_BOOST_FUSION_FOR_EACH
#endif

#ifndef POSSIBLE_TO_INCLUDE_BOOST_FUSION_FOR_EACH
#ifndef POSSIBLE_TO_INCLUDE_BOOST_FUSION_STD_TUPLE
#define IMPOSSIBLE_TO_INCLUDE_BOOST
#endif
#endif

#ifndef IMPOSSIBLE_TO_INCLUDE_BOOST
#include<boost/fusion/adapted/std_tuple.hpp>
#include<boost/fusion/include/for_each.hpp>
#endif

namespace srook{
inline namespace v1{

inline namespace from_iterator{

template<char _delimiter=' ',class ForwardIterator>
constexpr auto make_elements_string(ForwardIterator first,const ForwardIterator& last)
	->decltype(typename ForwardIterator::iterator_category(),std::string())
{
	std::ostringstream result;
	for(; first!=last; ++first)result<<*first<<_delimiter;
	std::string s=std::move(result.str());
	s.pop_back();
	return s;
}

template<char _delimiter=' ',class Pointer>
constexpr auto make_elements_string(Pointer* first,Pointer* last)
	->std::string
{
	std::ostringstream result;
	for(; first!=last; ++first)result<<*first<<_delimiter;
	std::string s=std::move(result.str());
	s.pop_back();
	return s;
}

} // inline namespace from_iterator

inline namespace from_string{
std::ostringstream os;

constexpr void transfer_ostream_parpack(const char){}

template<class First,class...Rest>
constexpr void transfer_ostream_parpack
(const char _delimiter,const First& first,const Rest&... rest)
{
	os<<first<<_delimiter;
	transfer_ostream_parpack(_delimiter,rest...);
}

template<char _delimiter=' ',class... Args>
constexpr decltype(auto) make_elements_string(const Args&... str)
{
	transfer_ostream_parpack(_delimiter,str...);
	std::string s=std::move(os.str());
	s.pop_back();
	os.str("");
	os.clear(std::stringstream::goodbit);
	return s;
}

} // inline namespace from_string

inline namespace from_range{

template<char _delimiter=' ',class Container>
constexpr std::string make_elements_string(const Container& c)
{
	std::ostringstream result;
	for(auto&& it:c)result<<it<<_delimiter;
	std::string s=std::move(result.str());
	s.pop_back();
	return s;
}

template<char _delimiter=' ',class FirstType,class SecondType>
constexpr std::string make_elements_string(const std::map<FirstType,SecondType>& m)
{
	std::ostringstream result;
	for(auto&& it:m)result<<'['<<it.first<<' '<<it.second<<']'<<_delimiter;
	std::string s=std::move(result.str());
	s.pop_back();
	return s;
}

template<char _delimiter=' ',class FirstType,class SecondType>
constexpr std::string make_elements_string(const std::multimap<FirstType,SecondType>& m)
{
	std::ostringstream result;
	for(auto&& it:m)result<<'['<<it.first<<' '<<it.second<<']'<<_delimiter;
	std::string s=std::move(result.str());
	s.pop_back();
	return s;
}

template<char _delimiter=' ',class FirstType,class SecondType>
constexpr std::string make_elements_string(const std::pair<FirstType,SecondType>& p)
{
	std::ostringstream result;
	result<<'['<<p.first<<' '<<p.second<<']'<<_delimiter;
	std::string s=std::move(result.str());
	s.pop_back();
	return s;
}

template<char _delimiter=' ',
	class Container_Addapter_Tp,class Container=std::deque<Container_Addapter_Tp>>
constexpr std::string make_elements_string(std::queue<Container_Addapter_Tp,Container> q)
{
	std::ostringstream result;
	while(!q.empty()){
		result<<q.front()<<_delimiter;
		q.pop();
	}
	std::string s=std::move(result.str());
	s.pop_back();
	return s;
}

template<char _delimiter=' ',
	class Container_Addapter_Tp,class Container=std::deque<Container_Addapter_Tp>>
constexpr std::string make_elements_string(std::stack<Container_Addapter_Tp,Container> st)
{
	std::ostringstream result;
	while(!st.empty()){
		result<<st.top()<<_delimiter;
		st.pop();
	}
	std::string s=std::move(result.str());
	s.pop_back();
	return s;
}

#ifndef IMPOSSIBLE_TO_INCLUDE_BOOST
template<char _delimiter=' ',class... Args>
constexpr std::string make_elements_string(const std::tuple<Args...>& tp)
{
	std::ostringstream os;
	boost::fusion::for_each(tp,[&os](auto x){os<<x<<_delimiter;});
	std::string s=std::move(os.str());
	s.pop_back();
	return s;
}
#endif
} // inline namespace from_range

inline namespace mkelm_str_iota_nm{
template<class _Tp>
struct mk_elements_string_iota_pair_type final{
	_Tp first;
	const _Tp last;
	
	mk_elements_string_iota_pair_type(const _Tp& x,const _Tp& y):first(x),last(y){}
	mk_elements_string_iota_pair_type(mk_elements_string_iota_pair_type&&)=default;
	~mk_elements_string_iota_pair_type()=default;
	mk_elements_string_iota_pair_type(const mk_elements_string_iota_pair_type&)=delete;
	mk_elements_string_iota_pair_type operator=(const mk_elements_string_iota_pair_type&)=delete;
	mk_elements_string_iota_pair_type operator=(mk_elements_string_iota_pair_type&&)=delete;
};

template<class _Tp>
constexpr auto mkelm_str_iota(const _Tp& x,const _Tp& y)
{
	return mk_elements_string_iota_pair_type<_Tp>(x,y);
}

template<char _delimiter=' ',class _Tp>
constexpr std::string make_elements_string(mk_elements_string_iota_pair_type<_Tp>&& m)
{
	std::ostringstream result;
	for(; m.first<m.last; ++m.first)result<<m.first<<_delimiter;
	std::string s=std::move(result.str());
	s.pop_back();
	return s;
}
} // inline namespace mkelm_str_iota_nm

} // inline namespace v1

} // namespace srook
#endif

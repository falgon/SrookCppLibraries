#ifndef SROOK_INCLUDED_RANGE_ITERATOR
#define SROOK_INCLUDED_RANGE_ITERATOR
#include<iterator>
namespace srook{

struct OnlyHeadAndTail_Iterator_Tag{};
template<class Iterator>
using derived_type=std::iterator<OnlyHeadAndTail_Iterator_Tag,typename std::iterator_traits<Iterator>::value_type>;
template<class Iterator>
struct range_iterator:public derived_type<Iterator>{
	typedef Iterator iterator;
	typedef iterator const_iterator;
	
	explicit range_iterator(Iterator first,Iterator last):first_(first),last_(last){}
	iterator begin()const{return first_;}
	iterator end()const{return last_;}
	const_iterator cbegin()const{return first_;}
	const_iterator cend()const{return last_;}
private:
	iterator first_,last_;
};
template<class Iterator>
range_iterator<Iterator> make_range_iterator(Iterator first,Iterator last){return range_iterator<Iterator>(first,last);}

}
#endif

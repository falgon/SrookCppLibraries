#ifndef SROOK_INCLUDED_RANGE_ADAPTOR_COPIED
#define SROOK_INCLUDED_RANGE_ADAPTOR_COPIED
#include<srook/range/adaptor/adaptor_operator.hpp>
#include<srook/iterator/range_iterator.hpp>
namespace srook{

template<class Iterator>
struct copied_t_impl{
	explicit copied_t_impl(Iterator first,Iterator last):first_(first),last_(last){}
	template<class Range>
	operator Range()const{return Range(first_,last_);}
private:
	Iterator first_,last_;
};
template<class Iterator>
copied_t_impl<Iterator> make_copied_t_impl(Iterator first,Iterator last){return copied_t_impl<Iterator>(first,last);}
const struct copied_t{
	template<class Range>
	auto operator()(const Range& r)const{return make_copied_t_impl(r.begin(),r.end());}
}copied={};

}
#endif

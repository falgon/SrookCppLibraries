#ifndef INCLUDED_SROOK_REMOVE_COPIED_RANGE_ITERATOR_HPP
#define INCLUDED_SROOK_REMOVE_COPIED_RANGE_ITERATOR_HPP
#include<srook/type_traits/has_iterator.hpp>
#include<srook/iterator/range_iterator.hpp>
#include<srook/config/require.hpp>
#include<iterator>
#include<srook/iterator/skipping_iterator_value_core.hpp>

namespace srook{
inline namespace v1{

template<class Iterator,class T>
struct remove_copied_range_iterator final:skipping_iterator_value_core<Iterator,T>{
	using skipping_iterator_value_core<Iterator,T>::skipping_iterator_value_core;
private:
	void skip()override
	{
		while(this->value_==*(this->first_))
			++(this->first_);
	}
};

template<class Iterator,class T>
constexpr remove_copied_range_iterator<std::decay_t<Iterator>,std::decay_t<T>>
make_remove_copied_range_iterator(Iterator&& first,Iterator&& last,T&& t)
{
	return remove_copied_range_iterator<std::decay_t<Iterator>,std::decay_t<T>>(std::forward<Iterator>(first),std::forward<Iterator>(last),std::forward<T>(t));
}

} // inline namespace v1
} // namespace srook

#endif

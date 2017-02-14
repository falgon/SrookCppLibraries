#ifndef INCLUDED_FILTERD_ITERATOR_HPP
#define INCLUDED_FILTERD_ITERATOR_HPP
#include<iterator>
#include<srook/utility/lambda_wrapper.hpp>

namespace srook{
inline namespace v1{

template<class Predicate,class Iterator>
struct filterd_iterator final{
    using iterator_category=std::forward_iterator_tag;
    using iterator=Iterator;
    using const_iterator=Iterator;
    using value_type=typename std::iterator_traits<Iterator>::value_type;
    using difference_type=typename std::iterator_traits<Iterator>::difference_type;
    using reference=typename std::iterator_traits<Iterator>::reference;
    using pointer=typename std::iterator_traits<Iterator>::pointer;

    explicit filterd_iterator(Predicate& predicate,Iterator first,Iterator last)noexcept
        :pred(predicate),first_(std::move(first)),last_(std::move(last))
        {
            skip();
        }
    explicit filterd_iterator(Predicate&& predicate,Iterator first,Iterator last)noexcept
        :pred(std::move(predicate)),first_(std::move(first)),last_(std::move(last))
        {
            skip();
        }
    
    filterd_iterator& operator++()
    {
        ++first_;
        skip();
        return *this;
    }
    filterd_iterator operator++(int)
    {
        filterd_iterator tmp=*this;
        ++first_;
        skip();
        return tmp;
    }
	filterd_iterator& operator=(const filterd_iterator& rhs)
	{
		pred=rhs.pred;
		first_=rhs.first_;
		last_=rhs.last_;
		return *this;
	}

    reference operator*(){return *first_;}
	const reference operator*()const{return *first_;}
	constexpr bool operator==(const filterd_iterator& rhs)const{return first_==rhs.first_;}
    constexpr bool operator!=(const filterd_iterator& rhs)const{return !operator==(rhs);}
private:
    void skip(){while(first_!=last_ && !pred(*first_))++first_;}
    lambda_wrapper<Predicate> pred;
	iterator first_,last_;
};
template<class Predicate,class Iterator>
constexpr filterd_iterator<std::remove_reference_t<Predicate>,Iterator>
make_filterd_iterator(Predicate&& pred,Iterator first,Iterator last)
{
    return filterd_iterator<Predicate,Iterator>(
        std::forward<Predicate>(pred),std::move(first),std::move(last)
    );
}

} // inline namespace v1
} // namespace srook
#endif


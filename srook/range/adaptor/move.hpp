#ifndef INCLUDED_SROOK_RANGE_ADAPTOR_MOVE
#define INCLUDED_SROOK_RANGE_ADAPTOR_MOVE
#include<srook/range/adaptor/adaptor_operator.hpp>
#include<utility>

namespace srook{
namespace adaptors{
namespace detail{
inline namespace v1{

template<class Data>
struct move_t_impl{
	explicit constexpr move_t_impl(Data&& d):data_(std::move(d)){}
	template<class T>
	operator T()
	{
		return T(std::move(data_));
	}
private:
   Data data_;
};

const struct move_t{
	template<class T>
	move_t_impl<std::decay_t<T>> operator()(T& value)const{return move_t_impl<std::decay_t<T>>(std::move(value));}
	template<class T>
	move_t_impl<std::decay_t<T>> operator()(T&& value)const{return move_t_impl<std::decay_t<T>>(std::move(value));}
}move={};

} // inline namespace v1
} // namespace detail

using detail::move;

} // namespace adaptors
} // namespace srook
#endif

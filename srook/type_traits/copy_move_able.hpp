// Copyright (C) 2017 roki
#ifndef INCLUDED_TYPE_TRAITS_COPY_MOVE_ABLE
#define INCLUDED_TYPE_TRAITS_COPY_MOVE_ABLE
#include<type_traits>
namespace srook{

template<class _Tp,_Tp&(_Tp::*)(const _Tp&)>
struct copy_signature{
	using type=_Tp;
};
template<class _Tp,class=_Tp>
struct copy_f_deleted:std::false_type{};
template<class _Tp>
struct copy_f_deleted<_Tp,std::enable_if_t<std::is_pod<std::remove_reference_t<_Tp>>{},_Tp>>:std::true_type{};
template<class _Tp>
struct copy_f_deleted<_Tp,typename copy_signature<_Tp,&_Tp::operator=>::type>:std::true_type{};
template<class _Tp>
constexpr bool is_copyable_v=copy_f_deleted<_Tp>::value;

template<class _Tp,_Tp&(_Tp::*)(_Tp&&)>
struct move_signature{
	using type=_Tp;
};
template<class _Tp,class=_Tp>
struct move_f_deleted:std::false_type{};
template<class _Tp>
struct move_f_deleted<_Tp,std::enable_if_t<std::is_pod<std::remove_reference_t<_Tp>>{},_Tp>>:std::true_type{};
template<class _Tp>
struct move_f_deleted<_Tp,typename move_signature<_Tp,&_Tp::operator=>::type>:std::true_type{};
template<class _Tp>
constexpr bool is_moveable_v=move_f_deleted<_Tp>::value;

}
#endif

// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_MPL_HUFFMAN_CODING_HPP
#define INCLUDED_SROOK_MPL_HUFFMAN_CODING_HPP
#include<type_traits>
#if __has_include(<optional>)
#	include<optional>
#	define nullopt_t std::nullopt_t
#elif __has_include(<boost/optional.hpp>)
#	include<boost/optional.hpp>
#	define nullopt_t boost::none_t
#endif

namespace srook{
namespace huffman_coding{

namespace{

template<class... Tp>
struct type_pack{
    static constexpr std::size_t size(){return sizeof...(Tp);}
};

template<class L,class... R>
struct concat_type{
    using type=type_pack<L,R...>;
};
template<class... L,class... R>
struct concat_type<type_pack<L...>,R...>:concat_type<L...,R...>{};
template<class L,class... R>
struct concat_type<L,type_pack<R...>>:concat_type<L,R...>{};
template<class... L,class... R>
struct concat_type<type_pack<L...>,type_pack<R...>>:concat_type<L...,R...>{};
template<class L,class... R>
using concat_type_t=typename concat_type<L,R...>::type;

template<class Head,class... Tail>
struct pop_front_type{
    using type=type_pack<Tail...>;
};
template<class... Ts>
struct pop_front_type<type_pack<Ts...>>:pop_front_type<Ts...>{};
template<class... Pack>
using pop_front_type_t=typename pop_front_type<Pack...>::type;

template<class Head,class...>
struct first_type{
    using type=Head;
};
template<class Head,class... Tail>
struct first_type<type_pack<Head,Tail...>>:first_type<Head,Tail...>{};
template<class... Pack>
using first_type_t=typename first_type<Pack...>::type;

template<auto...>
struct pack{};

template<auto,class> struct count;
template<auto target,auto head,auto... tail>
struct count<target,pack<head,tail...>>{
	static constexpr std::size_t value=(target==head?1:0)+count<target,pack<tail...>>::value;
};
template<auto target>
struct count<target,pack<>>{
	static constexpr std::size_t value=0;
};
template<auto target,class pack>
static constexpr std::size_t count_v=count<target,pack>::value;

template<class,class> struct concat;
template<auto... l,auto... r>
struct concat<pack<l...>,pack<r...>>{
    using type=pack<l...,r...>;
};
template<class L,class R>
using concat_t=typename concat<L,R>::type;


template<auto,class> struct erase;
template<auto target,auto head,auto... tail>
struct erase<target,pack<head,tail...>>{
    using type=concat_t<std::conditional_t<target==head,pack<>,pack<head>>,typename erase<target,pack<tail...>>::type>;
};
template<auto target>
struct erase<target,pack<>>{
    using type=pack<>;
};
template<auto target,class Pack>
using erase_t=typename erase<target,Pack>::type;

template<class> struct no_duplicate;
template<auto head,auto... tail>
struct no_duplicate<pack<head,tail...>>{
    using type=concat_t<pack<head>,typename no_duplicate<erase_t<head,pack<tail...>>>::type>;
};
template<>
struct no_duplicate<pack<>>{
    using type=pack<>;
};
template<class Pack>
using no_duplicate_t=typename no_duplicate<Pack>::type;

template<auto v,std::size_t r>
struct priority_pair{
    static constexpr decltype(v) value=v;
    static constexpr std::size_t rank=r;
};

template<class,class> struct make_elements_pack_impl;
template<auto... elements,auto list_head,auto... list_tail>
struct make_elements_pack_impl<pack<elements...>,pack<list_head,list_tail...>>{
    using type=
        concat_type_t<
            priority_pair<list_head,count_v<list_head,pack<elements...>>>,
            typename make_elements_pack_impl<pack<elements...>,pack<list_tail...>>::type
        >;
};
template<auto... elements>
struct make_elements_pack_impl<pack<elements...>,pack<>>{
    using type=type_pack<>;
};
template<class Pack>
using make_elements_pack=typename make_elements_pack_impl<Pack,no_duplicate_t<Pack>>::type;

template<class,class> struct take_max_elements_impl;
template<class Comparison,auto v,std::size_t r,class... Tail>
struct take_max_elements_impl<Comparison,type_pack<priority_pair<v,r>,Tail...>>{
    using type=
        typename take_max_elements_impl<
            std::conditional_t<(Comparison::rank < r),priority_pair<v,r>,Comparison>,
            type_pack<Tail...>
        >::type;
};
template<class Comparison>
struct take_max_elements_impl<Comparison,type_pack<>>{
    using type=Comparison;
};
template<class priority_pair_pack>
using take_max_elements=typename take_max_elements_impl<first_type_t<priority_pair_pack>,pop_front_type_t<priority_pair_pack>>::type;

template<class,class> struct erase_priority_pair;
template<auto vtarget,std::size_t rtarget,auto v,std::size_t r,class... Tail>
struct erase_priority_pair<priority_pair<vtarget,rtarget>,type_pack<priority_pair<v,r>,Tail...>>{
    using type=
        concat_type_t<
            priority_pair<v,r>,
            typename erase_priority_pair<priority_pair<vtarget,rtarget>,type_pack<Tail...> >::type
        >;
};
template<auto vtarget,std::size_t rtarget,class... Tail>
struct erase_priority_pair<priority_pair<vtarget,rtarget>,type_pack<priority_pair<vtarget,rtarget>,Tail...>>{
    using type=type_pack<Tail...>;
};
template<auto vtarget,std::size_t rtarget>
struct erase_priority_pair<priority_pair<vtarget,rtarget>,type_pack<>>{
    using type=pack<>;
};
template<class Target,class Priority_pack>
using erase_priority_pair_t=typename erase_priority_pair<Target,Priority_pack>::type;

template<class,bool,class> struct node;
template<auto v,bool b,bool branch,class Tail>
struct node<pack<v,b>,branch,Tail>{
    static constexpr decltype(v) value=v;
    static constexpr bool sign=b;
};

template<class> struct priority_pack_sort_impl;
template<class... Elements>
struct priority_pack_sort_impl<type_pack<Elements...>>{
private:
    using elements=type_pack<Elements...>;
    using inner=take_max_elements<elements>;
public:
    using type=concat_type_t<type_pack<inner>,typename priority_pack_sort_impl<erase_priority_pair_t<inner,elements>>::type>;
};
template<>
struct priority_pack_sort_impl<type_pack<>>{
    using type=type_pack<>;
};
template<class Pack>
using priority_pack_sort=typename priority_pack_sort_impl<make_elements_pack<Pack>>::type;

template<bool,class> struct make_huffman_tree_impl;
template<bool b,auto v,std::size_t r,class... Tail>
struct make_huffman_tree_impl<b,type_pack<priority_pair<v,r>,Tail...>>{
    using type=node<pack<v,b>,1,typename make_huffman_tree_impl<0,type_pack<Tail...>>::type>;
};
template<bool b>
struct make_huffman_tree_impl<b,type_pack<>>{
    using type=nullopt_t;
};
template<class Priority_pack>
using make_huffman_tree=typename make_huffman_tree_impl<0,Priority_pack>::type;

template<auto,class,std::nullptr_t=nullptr> struct value_to_huffman_impl;
template<auto target,auto v,bool b,bool branch,auto next_char,bool next_b,bool next_branch,class Tail,std::enable_if_t<target!=v,std::nullptr_t> nullptrer>
struct value_to_huffman_impl<target,node<pack<v,b>,branch,node<pack<next_char,next_b>,next_branch,Tail>>,nullptrer>{
    using type=
        concat_t<
            pack<branch>,
            typename value_to_huffman_impl<target,node<pack<next_char,next_b>,next_branch,Tail>>::type
        >;
};
template<auto target,bool bv,bool branch,class Tail,
    std::nullptr_t nullptrer>
struct value_to_huffman_impl<target,node<pack<target,bv>,branch,Tail>,nullptrer>{
    using type=pack<bv>;
};
template<auto target_value,class huffman_tree>
using value_to_huffman=typename value_to_huffman_impl<target_value,huffman_tree,nullptr>::type;

template<class,class> struct huffman_encode_impl;
template<class All,auto head,auto... tail>
struct huffman_encode_impl<All,pack<head,tail...>>{
public:
    using type=
        concat_t<
            value_to_huffman<
                head,
                make_huffman_tree<priority_pack_sort<All>>
            >,
        typename huffman_encode_impl<All,pack<tail...>>::type>;
};
template<class All>
struct huffman_encode_impl<All,pack<>>{
    using type=pack<>;
};

} // namespace anonymouse

template<class Pack>
using huffman_encode=typename huffman_encode_impl<Pack,Pack>::type;

} // namespace huffman_coding
} // namespace srook

#undef nullopt_t
#endif

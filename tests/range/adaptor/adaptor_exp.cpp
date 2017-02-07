#include<srook/range/adaptor/adjacent_find.hpp>
#include<srook/range/adaptor/all_of.hpp>
#include<srook/range/adaptor/binary_search.hpp>
#include<srook/range/adaptor/copied.hpp>
#include<srook/range/adaptor/copied_backward.hpp>
#include<srook/range/adaptor/copied_if.hpp>
#include<srook/range/adaptor/copied_n.hpp>
#include<srook/range/adaptor/copy.hpp>
#include<srook/range/adaptor/copy_backward.hpp>
#include<srook/range/adaptor/copy_if.hpp>
#include<srook/range/adaptor/copy_n.hpp>
#include<srook/range/adaptor/count.hpp>
#include<srook/range/adaptor/count_if.hpp>
#include<srook/range/adaptor/equal.hpp>
#include<srook/range/adaptor/equal_range.hpp>
#include<srook/range/adaptor/fill.hpp>
#include<srook/range/adaptor/fill_n.hpp>
#include<srook/range/adaptor/filterd.hpp>
#include<srook/range/adaptor/find.hpp>
#include<srook/range/adaptor/find_end.hpp>
#include<srook/range/adaptor/find_first_of.hpp>
#include<srook/range/adaptor/find_if_not.hpp>
#include<srook/range/adaptor/for_each.hpp>
#include<srook/range/adaptor/generate.hpp>
#include<srook/range/adaptor/generate_n.hpp>
#include<srook/range/adaptor/includes.hpp>
#include<srook/range/adaptor/inplace_merge.hpp>
#include<srook/range/adaptor/is_heap.hpp>
#include<srook/range/adaptor/is_heap_until.hpp>
#include<srook/range/adaptor/is_partitioned.hpp>
#include<srook/range/adaptor/is_permutation.hpp>
#include<srook/range/adaptor/is_sorted.hpp>
#include<srook/range/adaptor/is_sorted_until.hpp>
#include<srook/range/adaptor/lexicographical_compare.hpp>
#include<srook/range/adaptor/lower_bound.hpp>
#include<srook/range/adaptor/make_heap.hpp>
#include<srook/range/adaptor/max.hpp>
#include<srook/range/adaptor/min.hpp>
#include<srook/range/adaptor/max_element.hpp>
#include<srook/range/adaptor/min_element.hpp>
#include<srook/range/adaptor/merge.hpp>
#include<srook/range/adaptor/minmax.hpp>
#include<srook/range/adaptor/minmax_element.hpp>
#include<srook/range/adaptor/mismatch.hpp>
#include<srook/range/adaptor/move.hpp>
#include<srook/range/adaptor/moved.hpp>
#include<srook/range/adaptor/move_backward.hpp>
#include<srook/range/adaptor/next_permutation.hpp>
#include<srook/range/adaptor/none_of.hpp>
#include<srook/range/adaptor/nth_element.hpp>
#include<srook/range/adaptor/partial_sort.hpp>
#include<srook/range/adaptor/partial_sort_copy.hpp>
#include<srook/range/adaptor/partition.hpp>
#include<srook/range/adaptor/partition_copy.hpp>
#include<srook/range/adaptor/partition_point.hpp>
#include<srook/range/adaptor/pop_heap.hpp>

#include<srook/range/adaptor/sort.hpp>
#include<srook/range/adaptor/print.hpp>


#include<srook/mpl/variadic_player.hpp>
#include<srook/config/attribute.hpp>
#include<srook/config/require.hpp>
#include<srook/type_traits/remove_all_reference.hpp>
#include<random>
#include<tuple>
#include<utility>
#include<boost/range/algorithm_ext/iota.hpp>
#include<boost/range/algorithm/for_each.hpp>
#include<boost/version.hpp>

// Test Ranges
#include<vector>
#include<deque>
#include<string>
#include<list>
#include<initializer_list>


namespace{
	constexpr std::size_t range_size=10;
}

template<class TestExpression>
struct tester{
	explicit constexpr tester(const TestExpression& t):exp_(t){};
	explicit constexpr tester(TestExpression&& t):exp_(std::move(t)){}
	
	template<class TestRange>
	void play(TestRange&& tr)const
	{
		exp_(std::forward<TestRange>(tr));
	}
private:
	const TestExpression& exp_;
};
template<class TestExpression>
tester<std::decay_t<TestExpression>> make_tester(TestExpression&& test)
{
	return tester<std::decay_t<TestExpression>>(std::forward<TestExpression>(test));
}


template<class Tuple,class Range_tuple>
struct applyer{
	explicit constexpr applyer(const Tuple& t,const Range_tuple& ranges)
		:t_(t),ranges_(ranges){}

	void play_invoker()
	{
		play_invoker(t_,std::make_index_sequence<std::tuple_size<std::remove_reference_t<Tuple>>::value>());
	}
private:				
	void invoke_play(){}
	template<class Head,class... Tail>
	void invoke_play(Head&& head,Tail&&... tail)
	{
		forwarding_tuple(std::forward<Head>(head),std::integral_constant<std::size_t,std::tuple_size<Range_tuple>::value-1>());
		invoke_play(std::forward<Tail>(tail)...);
	}
	template<class T,std::size_t... I>
	void play_invoker(T&& t,const std::index_sequence<I...>&&){invoke_play(std::get<I>(t)...);}

	template<class T,std::size_t tuple_size>
	void forwarding_tuple(T&& t,const std::integral_constant<std::size_t,tuple_size>&)
	{
		t.play(std::get<tuple_size>(ranges_));
		forwarding_tuple(std::forward<T>(t),std::integral_constant<std::size_t,tuple_size-1>());
	}
	template<class T>
	void forwarding_tuple(T&& t,const std::integral_constant<std::size_t,0>&)
	{
		t.play(std::get<0>(ranges_));
	}

	Tuple t_;
	Range_tuple ranges_;
};

template<class Tuple,class... Ranges>
applyer<
	std::decay_t<Tuple>,
	srook::mpl::Transfer_t<std::tuple,srook::remove_all_reference_t<Ranges...>>
> 
make_applyer_impl(Tuple&& t,Ranges&&... ranges)
{
	return applyer<
				std::decay_t<Tuple>,
				srook::mpl::Transfer_t<std::tuple,srook::remove_all_reference_t<Ranges...>>
			>(
				std::forward<Tuple>(t),
				srook::mpl::Transfer_t<std::tuple,srook::remove_all_reference_t<Ranges...>>{std::forward<Ranges>(ranges)...}
			);
}

struct mk{
	template<class Tuple,class Tuple_range,std::size_t I,class... Args>
	static auto make_applyer(Tuple&& t,Tuple_range&& t_range,const std::integral_constant<std::size_t,I>& intconstant,Args&&... args)
	{
		return std::conditional<
					sizeof...(args)==std::tuple_size<std::remove_reference_t<Tuple_range>>::value,
					invoke,
					unpack
				>::type::apply(
						std::forward<Tuple>(t),
						std::forward<Tuple_range>(t_range),
						intconstant,
						std::forward<Args>(args)...
				);
	}
	struct invoke{
		template<class Tuple,class Tuple_range,std::size_t n,class... Args>
		static auto apply(Tuple&& t,Tuple_range&&,const std::integral_constant<std::size_t,n>&,Args&&... args)
		{
			return make_applyer_impl(std::forward<Tuple>(t),std::forward<Args>(args)...);
		}
	};
	struct unpack{
		template<class Tuple,class Tuple_range,std::size_t I,class... Args>
		static auto apply(Tuple&& t,Tuple_range&& t_range,const std::integral_constant<std::size_t,I>&,Args&&... args)
		{
			return mk::make_applyer(
					std::forward<Tuple>(t),
					std::forward<Tuple_range>(t_range),
					std::integral_constant<std::size_t,I-1>(),
					std::forward<Args>(args)...,
					std::get<I>(t_range)
			);
		}
	};				
};

template<class Tuple,class Tuple_range>
auto make_applyer(Tuple&& t,Tuple_range&& t_range)
{
	return mk::make_applyer(
			std::forward<Tuple>(t),
			std::forward<Tuple_range>(t_range),
			std::integral_constant<std::size_t,std::tuple_size<std::remove_reference_t<Tuple_range>>::value-1>()
	);
}


/* 
 *
 *
 * Creating ranges
 *
 *
 */


auto make_test_ranges()
{
	std::vector<int> v(range_size);
#if (BOOST_VERSION != 105800)
//	std::deque<int> deq(range_size);
#endif
	{
		std::uniform_int_distribution<> dist(0,42);
		std::random_device rng;
		std::default_random_engine engine(rng());
		auto apply_dist=[&dist,&engine](auto& x){x=dist(engine);};

		boost::range::for_each(v,apply_dist);
#if (BOOST_VERSION != 105800)
		//boost::range::for_each(deq,apply_dist);
#endif
	}
//	std::string str="Imagination is more important than knowledge. Knowledge is limited. Imagination encircles the world.";
	
	return std::make_tuple(std::move(v)/*,std::move(str)*/
#if (BOOST_VERSION != 105800)
//			,std::move(deq)
#endif
			);
}


/*
 *
 *
 * The below is intended to change debugging contents by classification of iterator which range contains.
 *
 *
 */


template<template<class...>class Range>
struct exclude_range{
	template<class... Ts>
	constexpr void operator()(const Range<Ts...>&)const{}
};

const struct find_check_t{
	template<class Range,REQUIRES(!std::is_same<std::decay_t<Range>,std::string>{})>
	void operator()(Range&& r)const
	{
		r | srook::adaptors::find(static_cast<typename std::decay_t<Range>::value_type>(42));
	}
	void operator()(const std::string& str)const
	{
		using namespace std::string_literals;
		auto search_string="important"s;
		
		std::size_t pos=str | srook::adaptors::find(search_string);

		SROOK_attribute_UNUSED std::size_t pos1=str | srook::adaptors::find(search_string,pos);
		SROOK_attribute_UNUSED std::size_t pos2=str | srook::adaptors::find(search_string,pos,search_string.size());
	}
}find_check={};

const struct fill_check_t:exclude_range<std::basic_string>{
	template<class Range>
	void operator()(Range r)const
	{
		r | srook::adaptors::fill(42);
	}
}fill_check={};

const struct fill_n_check_t:exclude_range<std::basic_string>{
	template<class Range>
	void operator()(Range r)const
	{
		r.begin() | srook::adaptors::fill_n(r.size(),42);
	}
}fill_n_check={};

const struct find_first_of_check_t{
	template<class Range,REQUIRES(!std::is_same<std::decay_t<Range>,std::string>{})>
	void operator()(const Range& r)const
	{
		auto hs=r;
		const auto f=[](typename std::decay_t<Range>::value_type x,typename std::decay_t<Range>::value_type y){return x<y;};

		SROOK_attribute_UNUSED typename std::decay_t<Range>::const_iterator it1 = r | srook::adaptors::find_first_of(hs);
		SROOK_attribute_UNUSED typename std::decay_t<Range>::const_iterator it2 = r | srook::adaptors::find_first_of(hs.cbegin(),hs.cend());
		SROOK_attribute_UNUSED typename std::decay_t<Range>::const_iterator it3 = r | srook::adaptors::find_first_of(hs,f);
		SROOK_attribute_UNUSED typename std::decay_t<Range>::const_iterator it4 = r | srook::adaptors::find_first_of(hs.cbegin(),hs.cend(),f);
	}
	void operator()(const std::string& str)const
	{
		using namespace std::string_literals;
		auto search_string="important"s;

		SROOK_attribute_UNUSED std::string::size_type result1 = str | srook::adaptors::find_first_of(search_string);
		SROOK_attribute_UNUSED std::string::size_type result2 = str | srook::adaptors::find_first_of(search_string.c_str(),search_string.size());
		SROOK_attribute_UNUSED std::string::size_type result3 = 
			str | srook::adaptors::find_first_of(search_string.c_str(),search_string.size(),search_string.size());
	}
}find_first_of_check={};

const struct binary_search_check_t:exclude_range<std::list>{
	template<class Range>
	void operator()(Range r)const
	{

		SROOK_attribute_UNUSED bool b1 = r | srook::adaptors::sort() | srook::adaptors::binary_search(4);
		SROOK_attribute_UNUSED bool b2 = r | srook::adaptors::binary_search(4,std::greater<>());
	}
}binary_search_check={};

const struct find_if_not_check_t:exclude_range<std::list>{
	template<class Range>
	void operator()(Range&& r)const
	{

		SROOK_attribute_UNUSED typename std::decay_t<decltype(r)>::const_iterator result_it = 
			r | srook::adaptors::find_if_not([](typename std::decay_t<decltype(r)>::value_type x){return x%2==0;});
	}
}find_if_not_check={};

const struct generate_n_check_t:exclude_range<std::list>{
	template<class Range>
	void operator()(Range r)const
	{

		SROOK_attribute_UNUSED typename std::decay_t<Range>::iterator it = r | srook::adaptors::generate_n(r.size(),[]{return 42;});
	}
}generate_n_check={};

#define st_ctype(x) static_cast<core_type>(x)
const struct includes_check_t:exclude_range<std::list>{
	template<class Range>
	void operator()(Range r)const
	{
		using core_type=typename std::decay_t<Range>::value_type;

		SROOK_attribute_UNUSED const bool result1 = 
			r | srook::adaptors::sort() | srook::adaptors::includes(std::decay_t<Range>{st_ctype(0),st_ctype(1),st_ctype(2)});
		SROOK_attribute_UNUSED const bool result2 =
			r | srook::adaptors::includes(std::decay_t<Range>{st_ctype(0),st_ctype(1),st_ctype(2)},std::greater<>());

		auto test_range=r;

		SROOK_attribute_UNUSED const bool result3 = 
			r | srook::adaptors::includes(test_range.cbegin(),test_range.cend());
		SROOK_attribute_UNUSED const bool result4 =
			r | srook::adaptors::includes(test_range.cbegin(),test_range.cend(),std::greater<>());
	}		
}includes_check={};
#undef st_ctype

const struct inplace_merge_check_t:exclude_range<std::list>{
	template<class Range>
	void operator()(Range r)const
	{
		SROOK_attribute_UNUSED auto range_it2 = r | srook::adaptors::inplace_merge(std::next(r.begin(),r.size()-1),r.end());
		SROOK_attribute_UNUSED auto range_it4 = r | srook::adaptors::inplace_merge(std::next(r.begin(),r.size()-1),r.end(),std::greater<>());
	}
}inplace_merge_check={};

const struct is_partitioned_check_t:exclude_range<std::list>{
	template<class Range>
	void operator()(const Range& r)const
	{
		SROOK_attribute_UNUSED bool b = r | srook::adaptors::is_partitioned([](typename std::decay_t<decltype(r)>::value_type x){return x%2==0;});
	}
}is_partitioned_check={};

const struct lexicographical_compare_check_t:exclude_range<std::list>{
	template<class Range>
	void operator()(const Range& r)const
	{
		auto tmp=r;

		SROOK_attribute_UNUSED bool b1 = r | srook::adaptors::lexicographical_compare(tmp);
		SROOK_attribute_UNUSED bool b2 = r | srook::adaptors::lexicographical_compare(tmp.cbegin(),tmp.cend());
		SROOK_attribute_UNUSED bool b3 = r | srook::adaptors::lexicographical_compare(tmp,std::greater<>());
		SROOK_attribute_UNUSED bool b4 = r | srook::adaptors::lexicographical_compare(tmp.cbegin(),tmp.cend(),std::greater<>());
	}
}lexicographical_compare_check={};

#define st(x) static_cast<typename std::decay_t<Range>::value_type>(x)
const struct lower_bound_check_t{
	template<class Range>
	void operator()(const Range& r)const
	{
		SROOK_attribute_UNUSED typename std::decay_t<Range>::const_iterator it1 = r | srook::adaptors::lower_bound(st(42));
		SROOK_attribute_UNUSED typename std::decay_t<Range>::const_iterator it2 = r | srook::adaptors::lower_bound(st(42),std::greater<>());
	}
}lower_bound_check={};
#undef st

const struct merge_check_t:exclude_range<std::list>{
	template<class Range>
	void operator()(const Range& r)const
	{
		auto a=r;
		std::decay_t<Range> result;
		
		r | srook::adaptors::merge(a,std::back_inserter(result));
		r | srook::adaptors::merge(a.cbegin(),a.cend(),std::back_inserter(result));
		r | srook::adaptors::merge(a,std::back_inserter(result),std::greater<>());
		r | srook::adaptors::merge(a.cbegin(),a.cend(),std::back_inserter(result),std::greater<>());
	}
}merge_check={};

const struct mismatch_check_t:exclude_range<std::list>{
	template<class Range>
	void operator()(const Range& r)const
	{
		auto a=r;
		const auto pred=[](typename std::decay_t<Range>::value_type x,typename decltype(a)::value_type y){return x==y;};
		typedef std::pair<typename std::decay_t<Range>::const_iterator,typename decltype(a)::const_iterator> result_type;

		SROOK_attribute_UNUSED result_type p1 = r | srook::adaptors::mismatch(a);
		SROOK_attribute_UNUSED result_type p2 = r | srook::adaptors::mismatch(a.cbegin());
		SROOK_attribute_UNUSED result_type p3 = r | srook::adaptors::mismatch(a,pred);
		SROOK_attribute_UNUSED result_type p4 = r | srook::adaptors::mismatch(a.cbegin(),a.cend());
		SROOK_attribute_UNUSED result_type p5 = r | srook::adaptors::mismatch(a.cbegin(),a.cend(),pred);
	}
}mismatch_check={};


const struct next_permutation_check_t:exclude_range<std::list>{
	template<class R>
	void operator()(R r)const
	{
		SROOK_attribute_UNUSED bool b1 = r | srook::adaptors::next_permutation();
		SROOK_attribute_UNUSED bool b2 = r | srook::adaptors::next_permutation(std::greater<>());
	}
}next_permutation_check={};

const struct none_of_check_t:exclude_range<std::list>{
	template<class Range>
	void operator()(const Range& r)const
	{
		SROOK_attribute_UNUSED bool b1 = r | srook::adaptors::none_of([](const typename std::decay_t<Range>::value_type x){return x%2==0;});
	}
}none_of_check={};


const struct nth_element_check_t:exclude_range<std::list>{
	template<class Range>
	void operator()(Range r)const
	{
		SROOK_attribute_UNUSED const auto iter1= r | srook::adaptors::nth_element(std::next(r.begin(),r.size()/2));
		SROOK_attribute_UNUSED const auto iter2= r | srook::adaptors::nth_element(std::next(r.begin(),r.size()/2),std::greater<>());
	}
}nth_element_check={};

const struct partial_sort_check_t:exclude_range<std::list>{
	template<class Range>
	void operator()(Range r)const
	{
		SROOK_attribute_UNUSED const auto iter1 = r | srook::adaptors::partial_sort(std::next(r.begin(),r.size()/2));
		SROOK_attribute_UNUSED const auto iter2 = r | srook::adaptors::partial_sort(std::next(r.begin(),r.size()/2),std::greater<>());
	}
}partial_sort_check={};

const struct partial_sort_copy_check_t:exclude_range<std::list>{
	template<class Range>
	void operator()(Range r)const
	{
		Range result(r);

		SROOK_attribute_UNUSED typename Range::iterator iter1 = r | srook::adaptors::partial_sort_copy(result);
		SROOK_attribute_UNUSED typename Range::iterator iter2 = r | srook::adaptors::partial_sort_copy(result,std::greater<>());
		SROOK_attribute_UNUSED typename Range::iterator iter3 = r | srook::adaptors::partial_sort_copy(result.begin(),result.end());
		SROOK_attribute_UNUSED typename Range::iterator iter4 = r | srook::adaptors::partial_sort_copy(result.begin(),result.end(),std::greater<>());
	}
}partial_sort_copy_check={};

const struct partition_copy_check_t:exclude_range<std::list>,exclude_range<std::basic_string>{
	template<class Range>
	void operator()(const Range& r)const
	{
		Range result1(r.size()),result2(r.size());
		const auto pred=[](const typename std::decay_t<Range>::value_type x){return x%2==0;};

		SROOK_attribute_UNUSED const auto p1 = r | srook::adaptors::partition_copy(std::back_inserter(result1),std::back_inserter(result2),pred);
		SROOK_attribute_UNUSED const auto p2 = r | srook::adaptors::partition_copy(result1.begin(),result2,pred);
		SROOK_attribute_UNUSED const auto p3 = r | srook::adaptors::partition_copy(result1,result2.begin(),pred);
		SROOK_attribute_UNUSED const auto p4 = r | srook::adaptors::partition_copy(result1,result2,pred);
	}
}partition_copy_check={};

const struct pop_heap_check_t:exclude_range<std::list>{
	template<class Range>
	void operator()(Range r)const
	{
		SROOK_attribute_UNUSED const auto iter1 = r | srook::adaptors::make_heap() | srook::adaptors::pop_heap();
		SROOK_attribute_UNUSED const auto iter2 = r | srook::adaptors::pop_heap(std::greater<>());
	}
}pop_heap_check={};

const struct print_check_t{
	template<class T>
	void operator()(const T&)const{}

	void operator()(std::string str)const
	{
		SROOK_attribute_UNUSED const auto range_iter = str | srook::adaptors::print(std::cout,"");
		std::cout<<std::endl;
	}
}print_check={};


int main()
{
	const auto tests=std::make_tuple(
			make_tester(
				[](const auto& x)
				{
					SROOK_attribute_UNUSED typename std::decay_t<decltype(x)>::const_iterator it = x | srook::adaptors::adjacent_find();
					SROOK_attribute_UNUSED decltype(it) it1 = x | srook::adaptors::adjacent_find(std::greater<>());
				}
			),
			make_tester(
				[](const auto& x)
				{
					SROOK_attribute_UNUSED bool b = x | srook::adaptors::all_of([](const auto& x){return x%2==0;});
				}
			),
			make_tester(binary_search_check),
			make_tester(
				[](const auto& x)
				{
					SROOK_attribute_UNUSED auto test = x | srook::adaptors::copied;
				}
			),
			make_tester(
				[](const auto& x)
				{
					SROOK_attribute_UNUSED auto test = x | srook::adaptors::copied_backward;
				}
			),
			make_tester(
				[](const auto& x)
				{
					SROOK_attribute_UNUSED auto test = x | srook::adaptors::copied_if([](const auto& x){return x%2==0;});
				}
			),
			make_tester(
				[](const auto& x)
				{
					SROOK_attribute_UNUSED auto test = x | srook::adaptors::copied_n(42);
				}
			),
			make_tester(
				[](const auto& x)
				{
					std::decay_t<decltype(x)> test=x;
					x | srook::adaptors::copy(test.begin());
				}
			),
			make_tester(
				[](const auto& x)
				{
					std::vector<typename std::decay_t<decltype(x)>::value_type> test(x.size());
					x | srook::adaptors::copy_backward(test.end());
				}
			),
			make_tester(
				[](const auto& x)
				{
					std::decay_t<decltype(x)> test=x;
					x | srook::adaptors::copy_if(test.begin(),[](auto&& x){return x%2==0;});
				}
			),
			make_tester(
				[](const auto& x)
				{
					std::decay_t<decltype(x)> test=x;
					x | srook::adaptors::copy_n(4,test.begin());
				}
			),
			make_tester(
				[](const auto& x)
				{

					SROOK_attribute_UNUSED typename std::iterator_traits<typename std::decay_t<decltype(x)>::iterator>::difference_type value = 
						x | srook::adaptors::count(10);
				}
			),
			make_tester(
				[](const auto& x)
				{

					SROOK_attribute_UNUSED typename std::iterator_traits<typename std::decay_t<decltype(x)>::iterator>::difference_type value = 
						x | srook::adaptors::count_if([](typename std::decay_t<decltype(x)>::value_type v){return v%2==0;});
				}
			),
			make_tester(
				[](const auto& x)
				{
					auto range=x;
					boost::iota(range,0);

					auto pred=
						[](typename decltype(range)::value_type x,typename decltype(range)::value_type y){return x-1<=y && y<=x+1;};

					SROOK_attribute_UNUSED bool b0 = x | srook::adaptors::equal(range);
					SROOK_attribute_UNUSED bool b1 = x | srook::adaptors::equal(range.begin());
					SROOK_attribute_UNUSED bool b2 = x | srook::adaptors::equal(range,pred);
					SROOK_attribute_UNUSED bool b3 = x | srook::adaptors::equal(range.begin(),range.end(),pred);
				}
			),
			make_tester(
				[](auto x)
				{
					SROOK_attribute_UNUSED auto test = x | srook::adaptors::equal_range(5);
					SROOK_attribute_UNUSED auto test1 = x | srook::adaptors::equal_range(5,std::greater<>());
				}
			),
			make_tester(fill_check),
			make_tester(fill_n_check),
			make_tester(find_check),
			make_tester(
					[](const auto& x)
					{
						auto hs=x;
						const auto f=
							[](typename decltype(hs)::value_type x,
							   typename decltype(hs)::value_type y)
							{
								return x < y;
							};

						SROOK_attribute_UNUSED typename std::decay_t<decltype(x)>::const_iterator it1 = x | srook::adaptors::find_end(hs);
						SROOK_attribute_UNUSED typename std::decay_t<decltype(x)>::const_iterator it2 = x | srook::adaptors::find_end(hs.cbegin(),hs.cend());
						SROOK_attribute_UNUSED typename std::decay_t<decltype(x)>::const_iterator it3 = x | srook::adaptors::find_end(hs,f);
						SROOK_attribute_UNUSED typename std::decay_t<decltype(x)>::const_iterator it4 = x | srook::adaptors::find_end(hs.cbegin(),hs.cend(),f);
					}
			),
			make_tester(find_first_of_check),
			make_tester(
				[](auto r)
				{
					r | srook::adaptors::sort();
					r | srook::adaptors::sort(std::greater<>());
				}		
			),
			make_tester(find_if_not_check),
			make_tester(
				[](const auto& r)
				{
					r | srook::adaptors::for_each([](typename std::decay_t<decltype(r)>::value_type){});
				}
			),
			make_tester(
				[](auto r)
				{
					SROOK_attribute_UNUSED auto range_iterator = r | srook::adaptors::generate([]{return 42;});
				}
			),
			make_tester(generate_n_check),
			make_tester(includes_check),
			make_tester(inplace_merge_check),
			make_tester(
				[](auto r)
				{

					SROOK_attribute_UNUSED const bool b1 = r | srook::adaptors::is_heap();
					SROOK_attribute_UNUSED const bool b2 = r | srook::adaptors::make_heap() | srook::adaptors::is_heap(std::greater<>());
				}
			),
			make_tester(
				[](auto r)
				{
					SROOK_attribute_UNUSED typename decltype(r)::const_iterator it1 = r | srook::adaptors::is_heap_until();
					SROOK_attribute_UNUSED typename decltype(r)::const_iterator it2 = 
						r | srook::adaptors::make_heap() | srook::adaptors::is_heap_until(std::greater<>());
				}
			),
			make_tester(is_partitioned_check),
			make_tester(
				[](const auto& r)
				{
					auto a=r;

					SROOK_attribute_UNUSED bool b1 = r | srook::adaptors::is_permutation(a);
					SROOK_attribute_UNUSED bool b2 = r | srook::adaptors::is_permutation(a.cbegin());
					SROOK_attribute_UNUSED bool b3 = r | srook::adaptors::is_permutation(a.cbegin(),a.cend());
					
					const auto test_f=[](typename decltype(a)::value_type x,typename decltype(a)::value_type y){return x==y;};
					SROOK_attribute_UNUSED bool b4 = r | srook::adaptors::is_permutation(a,test_f);
					SROOK_attribute_UNUSED bool b5 = r | srook::adaptors::is_permutation(a.cbegin(),test_f);
					SROOK_attribute_UNUSED bool b6 = r | srook::adaptors::is_permutation(a.cbegin(),a.cend(),test_f);
				}
			),
			make_tester(
				[](const auto& r)
				{
					SROOK_attribute_UNUSED bool b1 = r | srook::adaptors::is_sorted();
					SROOK_attribute_UNUSED bool b2 = r | srook::adaptors::is_sorted(std::greater<>());
				}
			),
			make_tester(
				[](const auto& r)
				{
					SROOK_attribute_UNUSED typename std::decay_t<decltype(r)>::const_iterator it1 = r | srook::adaptors::is_sorted_until();
					SROOK_attribute_UNUSED typename std::decay_t<decltype(r)>::const_iterator it2 = r | srook::adaptors::is_sorted_until(std::greater<>());
				}
			),
			make_tester(lexicographical_compare_check),
			make_tester(lower_bound_check),
			make_tester(
				[](const auto& r)
				{
					const auto get_initpack = []()->std::initializer_list<int>{return {1,2,3,4,5};};

					SROOK_attribute_UNUSED typename std::decay_t<decltype(r)>::value_type a = r | srook::adaptors::max();
					SROOK_attribute_UNUSED typename std::decay_t<decltype(r)>::value_type b = r | srook::adaptors::max(std::greater<>());
					SROOK_attribute_UNUSED auto c = 42 | srook::adaptors::max(32);
					SROOK_attribute_UNUSED auto d = 42 | srook::adaptors::max(32,std::greater<>());
					SROOK_attribute_UNUSED typename std::decay_t<decltype(get_initpack())>::value_type e = get_initpack() | srook::adaptors::max();
					SROOK_attribute_UNUSED typename std::decay_t<decltype(get_initpack())>::value_type f = 
						get_initpack() | srook::adaptors::max(std::greater<>());
					SROOK_attribute_UNUSED typename std::decay_t<decltype(r)>::value_type g = r | srook::adaptors::min();
					SROOK_attribute_UNUSED typename std::decay_t<decltype(r)>::value_type h = r | srook::adaptors::min(std::greater<>());
					SROOK_attribute_UNUSED auto i = 42 | srook::adaptors::min(32);
					SROOK_attribute_UNUSED auto j = 42 | srook::adaptors::min(32,std::greater<>());
				}
			),
			make_tester(
				[](const auto& r){

					SROOK_attribute_UNUSED typename std::decay_t<decltype(r)>::const_iterator it1 = r | srook::adaptors::max_element();
					SROOK_attribute_UNUSED typename std::decay_t<decltype(r)>::const_iterator it2 = r | srook::adaptors::max_element(std::greater<>());
					SROOK_attribute_UNUSED typename std::decay_t<decltype(r)>::const_iterator it3 = r | srook::adaptors::min_element();
					SROOK_attribute_UNUSED typename std::decay_t<decltype(r)>::const_iterator it4 = r | srook::adaptors::min_element(std::greater<>());
				}
			),
			make_tester(merge_check),
			make_tester(
				[](const auto& r)
				{

					SROOK_attribute_UNUSED auto p1 = r | srook::adaptors::minmax();
					SROOK_attribute_UNUSED auto p2 = r | srook::adaptors::minmax(std::greater<>());
					SROOK_attribute_UNUSED auto p3 = 42 | srook::adaptors::minmax(32);
					SROOK_attribute_UNUSED auto p4 = 42 | srook::adaptors::minmax(42,std::greater<>());
				}
			),
			make_tester(
				[](const auto& r)
				{
					SROOK_attribute_UNUSED auto p1 = r | srook::adaptors::minmax_element();
					SROOK_attribute_UNUSED auto p2 = r | srook::adaptors::minmax_element(std::greater<>());
				}
			),
			make_tester(mismatch_check),
			make_tester(
				[](auto r)
				{
					SROOK_attribute_UNUSED decltype(r) a = r | srook::adaptors::move;
				}
			),
			make_tester(
				[](auto r)
				{
					SROOK_attribute_UNUSED decltype(r) a = 
						r | srook::adaptors::filterd([](const typename decltype(r)::value_type x){return x%2==0;}) | srook::adaptors::moved;
				}
			),
			make_tester(
				[](auto r)
				{
					SROOK_attribute_UNUSED const auto b = r | srook::adaptors::move_backward(r.end());
				}
			),
			make_tester(next_permutation_check),
			make_tester(none_of_check),
			make_tester(nth_element_check),
			make_tester(partial_sort_check),
			make_tester(partial_sort_copy_check),
			make_tester(
				[](auto r)
				{
					SROOK_attribute_UNUSED const auto pos = 
						r | srook::adaptors::partition([](typename std::decay_t<decltype(r)>::value_type x){return x%2==0;});
				}
			),
			make_tester(partition_copy_check),
			make_tester(
				[](const auto& r)
				{
					SROOK_attribute_UNUSED const auto iter = 
						r | srook::adaptors::partition_point([](typename std::decay_t<decltype(r)>::value_type x){return x%2==0;});
				}
			),
			make_tester(pop_heap_check),
			make_tester(print_check)
	);
	
	auto ap=make_applyer(std::move(tests),make_test_ranges());
	ap.play_invoker();
}

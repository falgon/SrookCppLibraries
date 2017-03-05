#define BOOST_TEST_MODULE srook_constant_sequence_unit_test
#include<boost/test/included/unit_test.hpp>

#include<vector>
#include<algorithm>
#include<srook/mpl/constant_sequence/algorithm.hpp>
#include<srook/mpl/constant_sequence/interval_sequence.hpp>
#include<srook/mpl/constant_sequence/samevalue_sequence.hpp>
#define INDEX_SEQUENCE(...) std::index_sequence<__VA_ARGS__>
template<class L,class R>
constexpr void static_type_test()
{
	static_assert(std::is_same_v<L,R>);
}

template<std::size_t v>
using pred=std::integral_constant<bool,(v%2==0)>;

template<std::size_t v>
using function=std::integral_constant<std::size_t,(v*2)>;

BOOST_AUTO_TEST_CASE(test_op_reportings)
{
	using geometric_progression=srook::make_interval_sequence<srook::interval_sequence::plus,10,10,5>;
	static_type_test<geometric_progression,INDEX_SEQUENCE(10,20,30,40,50)>();

	using no_geometric_progression=srook::constant_sequence::insert_t<std::index_sequence<40,40,40>,geometric_progression::size()/2,geometric_progression>;
	static_type_test<no_geometric_progression,INDEX_SEQUENCE(10,20,40,40,40,30,40,50)>();

	using samevalue_sequence=srook::constant_sequence::make_samevalue_sequence<4,42>;
	static_type_test<samevalue_sequence,INDEX_SEQUENCE(42,42,42,42)>();

	constexpr std::size_t at_result=srook::constant_sequence::at_v<2,geometric_progression>;
	BOOST_TEST( (at_result==30) );
	
	constexpr bool binary_search_result1=srook::constant_sequence::binary_search_v<30,geometric_progression>;
	constexpr bool binary_search_result2=srook::constant_sequence::binary_search_v<42,geometric_progression>;
	BOOST_TEST( (binary_search_result1 and !binary_search_result2) );

	using concat_result=srook::constant_sequence::concat_t<geometric_progression,std::index_sequence<42,42>>;
	static_type_test<concat_result,INDEX_SEQUENCE(10,20,30,40,50,42,42)>();

	constexpr std::size_t count_result=srook::constant_sequence::count_v<40,no_geometric_progression>;
	BOOST_TEST( (4==count_result) );

	constexpr std::size_t count_if_result=srook::constant_sequence::count_if_v<pred,std::make_index_sequence<10>>;
	BOOST_TEST( (5==count_if_result) );

	using no_geometric_progression2=no_geometric_progression;
	constexpr bool equal_result1=srook::constant_sequence::equal_v<no_geometric_progression,no_geometric_progression2>;
	constexpr bool equal_result2=srook::constant_sequence::equal_v<no_geometric_progression,std::index_sequence<1>>;
	BOOST_TEST( (equal_result1 and !equal_result2) );

	constexpr auto equal_range_result=std::move(srook::constant_sequence::equal_range_v<40,no_geometric_progression>);
	BOOST_TEST( (equal_range_result.first==2 and equal_range_result.second==7) );

	using erase_result=srook::constant_sequence::erase_t<40,no_geometric_progression>;
	static_type_test<erase_result,INDEX_SEQUENCE(10,20,40,40,30,40,50)>();

	using erase_all_result=srook::constant_sequence::erase_all_t<40,no_geometric_progression>;
	static_type_test<erase_all_result,INDEX_SEQUENCE(10,20,30,50)>();

	using erase_duplicate_result=srook::constant_sequence::erase_duplicate_t<no_geometric_progression>;
	static_type_test<erase_duplicate_result,INDEX_SEQUENCE(10,20,40,30,50)>();

	using erase_if_result=srook::constant_sequence::erase_if_t<pred,std::make_index_sequence<10>>;
	static_type_test<erase_if_result,INDEX_SEQUENCE(0,2,4,6,8)>();

	using erase_n_result=srook::constant_sequence::erase_n_t<3,geometric_progression>;
	static_type_test<erase_n_result,INDEX_SEQUENCE(10,20,30,50)>();

	using filter_result=srook::constant_sequence::filter_t<pred,std::make_index_sequence<10>>;
	static_type_test<filter_result,INDEX_SEQUENCE(0,2,4,6,8)>();

	constexpr int find_result=srook::constant_sequence::find_v<30,geometric_progression>;
	BOOST_TEST( (find_result==2) );

	constexpr int find_if_result1=srook::constant_sequence::find_if_v<pred,INDEX_SEQUENCE(1,1,1,1,1,2,1)>;
	constexpr int find_if_result2=srook::constant_sequence::find_if_v<pred,srook::constant_sequence::make_samevalue_sequence<4,1>>;
	BOOST_TEST( (find_if_result1==5 and find_if_result2==-1) );

	constexpr int find_if_not_result1=srook::constant_sequence::find_if_not_v<pred,INDEX_SEQUENCE(2,2,2,2,1)>;
	constexpr int find_if_not_result2=srook::constant_sequence::find_if_not_v<pred,geometric_progression>;
	BOOST_TEST( (find_if_not_result1==4 and find_if_not_result2==-1) );

	constexpr std::size_t first_result=srook::constant_sequence::first_v<geometric_progression>;
	BOOST_TEST( (first_result==10) );

	using for_each_result=srook::constant_sequence::for_each_t<function,geometric_progression>;
	static_type_test<for_each_result,INDEX_SEQUENCE(20,40,60,80,100)>();

	constexpr bool includes_result1=srook::constant_sequence::includes_v<geometric_progression,INDEX_SEQUENCE(20,30,40)>;
	constexpr bool includes_result2=srook::constant_sequence::includes_v<geometric_progression,std::make_index_sequence<3>>;
	BOOST_TEST( (includes_result1 and !includes_result2) );

	using inplace_merge_result=srook::constant_sequence::inplace_merge_t<geometric_progression,INDEX_SEQUENCE(1,2,3,10,20)>;
	static_type_test<inplace_merge_result,INDEX_SEQUENCE(1,2,3,10,10,20,20,30,40,50)>();

	constexpr bool is_all_less_result=srook::constant_sequence::is_all_less_v<INDEX_SEQUENCE(1,2),INDEX_SEQUENCE(10,20)>;
	constexpr bool is_all_greater_result=srook::constant_sequence::is_all_greater_v<INDEX_SEQUENCE(10,20),INDEX_SEQUENCE(1,2)>;
	BOOST_TEST( (is_all_less_result and is_all_greater_result) );

	constexpr bool is_heap_result1=srook::constant_sequence::is_heap_v<INDEX_SEQUENCE(100,19,36,17,3,25,1,2,7)>;
	constexpr bool is_heap_result2=srook::constant_sequence::is_heap_v<INDEX_SEQUENCE(1,2,3,17,19,36,7,25,100),srook::constant_sequence::less>;
	BOOST_TEST( (is_heap_result1 and is_heap_result2) );

	constexpr bool is_partitioned_result1=srook::constant_sequence::is_partitioned_v<pred,INDEX_SEQUENCE(1,3,5,7,9,2,4,6)>;
	constexpr bool is_partitioned_result2=srook::constant_sequence::is_partitioned_v<pred,INDEX_SEQUENCE(1,2,3)>;
	BOOST_TEST( (is_partitioned_result1 and !is_partitioned_result2) );

	constexpr std::size_t last_result=srook::constant_sequence::last_v<geometric_progression>;
	BOOST_TEST( (last_result==50) );

	constexpr std::size_t length_result=srook::constant_sequence::length_v<geometric_progression>;
	BOOST_TEST( (length_result==5) );

	constexpr int lower_bound_result1=srook::constant_sequence::lower_bound_v<40,no_geometric_progression>;
	constexpr int lower_bound_result2=srook::constant_sequence::lower_bound_v<100,no_geometric_progression>;
	BOOST_TEST( ((lower_bound_result1==2) and (lower_bound_result2==-1)) );

	constexpr std::size_t min_result=srook::constant_sequence::min_v<geometric_progression>;
	BOOST_TEST( (min_result==10) );

	constexpr std::size_t max_result=srook::constant_sequence::max_v<geometric_progression>;
	BOOST_TEST( (max_result==50) );

	using partial_head_result=srook::constant_sequence::partial_head_t<geometric_progression::size()/2,geometric_progression>;
	static_type_test<partial_head_result,INDEX_SEQUENCE(10,20)>();

	using partial_tail_result=srook::constant_sequence::partial_tail_t<geometric_progression::size()/2,geometric_progression>;
	static_type_test<partial_tail_result,INDEX_SEQUENCE(30,40,50)>();

	using pop_back_result=srook::constant_sequence::pop_back_t<geometric_progression>;
	static_type_test<pop_back_result,INDEX_SEQUENCE(10,20,30,40)>();

	using pop_front_result=srook::constant_sequence::pop_front_t<geometric_progression>;
	static_type_test<pop_front_result,INDEX_SEQUENCE(20,30,40,50)>();

	using replace_result=srook::constant_sequence::replace_t<40,42,no_geometric_progression>;
	static_type_test<replace_result,INDEX_SEQUENCE(10,20,42,40,40,30,40,50)>();

	using replace_all_result=srook::constant_sequence::replace_all_t<40,42,no_geometric_progression>;
	static_type_test<replace_all_result,INDEX_SEQUENCE(10,20,42,42,42,30,42,50)>();

	using reverse_result=srook::constant_sequence::reverse_t<geometric_progression>;
	static_type_test<reverse_result,INDEX_SEQUENCE(50,40,30,20,10)>();

	constexpr std::size_t size_result=srook::constant_sequence::size<geometric_progression>;
	BOOST_TEST( (size_result==srook::constant_sequence::length_v<geometric_progression>) );

	using random_sequence=INDEX_SEQUENCE(30,20,42,19,22,2,8,45,10);
	using sort_less_result=srook::constant_sequence::sort_t<random_sequence>;
	static_type_test<sort_less_result,INDEX_SEQUENCE(2,8,10,19,20,22,30,42,45)>();

	constexpr std::size_t summation_result=srook::constant_sequence::summation_v<geometric_progression>;
	BOOST_TEST( (summation_result==110) );

	using swap_L_result=srook::constant_sequence::swap_L<3,geometric_progression,random_sequence>;
	using swap_R_result=srook::constant_sequence::swap_R<3,geometric_progression,random_sequence>;
	static_type_test<swap_L_result,INDEX_SEQUENCE(10,20,30,19,50)>();
	static_type_test<swap_R_result,INDEX_SEQUENCE(30,20,42,40,22,2,8,45,10)>();

	using swap_at_L_result=srook::constant_sequence::swap_at_L<2,geometric_progression,4,random_sequence>;
	using swap_at_R_result=srook::constant_sequence::swap_at_R<2,geometric_progression,4,random_sequence>;
	static_type_test<swap_at_L_result,INDEX_SEQUENCE(10,20,22,40,50)>();
	static_type_test<swap_at_R_result,INDEX_SEQUENCE(30,20,42,19,30,2,8,45,10)>();

	const auto test_range=std::move(srook::constant_sequence::transfer<std::vector,geometric_progression>::value);
	decltype(test_range) comparison{10,20,30,40,50};
	BOOST_TEST(std::equal(test_range.begin(),test_range.end(),comparison.begin()));

	const auto test_array=std::move(srook::constant_sequence::transfer_array<geometric_progression>::value);
	decltype(test_array) comparison_ar{{10,20,30,40,50}};
	BOOST_TEST(std::equal(test_array.begin(),test_array.end(),comparison_ar.begin()));

	constexpr int upper_bound_result1=srook::constant_sequence::upper_bound_v<40,no_geometric_progression>;
	constexpr int upper_bound_result2=srook::constant_sequence::upper_bound_v<100,no_geometric_progression>;
	BOOST_TEST( ((upper_bound_result1==7) and (upper_bound_result2==-1)) );
}

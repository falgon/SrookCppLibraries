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
#include<srook/range/adaptor/sort.hpp>
#include<srook/range/adaptor/print.hpp>

#include<srook/mpl/variadic_player.hpp>
#include<srook/config/require.hpp>
#include<srook/type_traits/remove_all_reference.hpp>
#include<random>
#include<tuple>
#include<utility>
#include<boost/range/algorithm_ext/iota.hpp>
#include<boost/range/algorithm/for_each.hpp>

// Test Ranges
#include<vector>
#include<deque>
#include<string>
#include<list>

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


auto make_test_ranges()
{
	std::vector<int> v(range_size);
	std::deque<int> deq(range_size);
	{
		std::uniform_int_distribution<> dist(0,42);
		std::random_device rng;
		std::default_random_engine engine(rng());
		auto apply_dist=[&dist,&engine](auto& x){x=dist(engine);};

		boost::range::for_each(v,apply_dist);
		boost::range::for_each(deq,apply_dist);
	}
	std::string str="Imagination is more important than knowledge. Knowledge is limited. Imagination encircles the world.";
	
	return std::make_tuple(std::move(v),std::move(deq),std::move(str));
}

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
#ifdef __GNUC__
		[[gnu::unused]]
#else
		[[maybe_unused]]
#endif
		std::size_t pos1=str | srook::adaptors::find(search_string,pos);
#ifdef __GNUC__
		[[gnu::unused]]
#else
		[[maybe_unused]]
#endif
		std::size_t pos2=str | srook::adaptors::find(search_string,pos,search_string.size());
	}
}find_check={};

const struct fill_check_t{
	template<class Range,REQUIRES(!std::is_same<std::decay_t<Range>,std::string>{})>
	void operator()(Range r)const
	{
		r | srook::adaptors::fill(42);
	}
	constexpr void operator()(const std::string&)const noexcept{}
}fill_check={};

const struct fill_n_check_t{
	template<class Range,REQUIRES(!std::is_same<std::decay_t<Range>,std::string>{})>
	void operator()(Range r)const
	{
		r.begin() | srook::adaptors::fill_n(r.size(),42);
	}
	constexpr void operator()(const std::string&)const noexcept{}
}fill_n_check={};

const struct find_first_of_check_t{
	template<class Range,REQUIRES(!std::is_same<std::decay_t<Range>,std::string>{})>
	void operator()(const Range& r)const
	{
		auto hs=r;
		const auto f=[](typename std::decay_t<Range>::value_type x,typename std::decay_t<Range>::value_type y){return x<y;};
#ifdef __GNUC__
		[[gnu::unused]]
#else
		[[maybe_unused]]
#endif
		typename std::decay_t<Range>::const_iterator it1 = r | srook::adaptors::find_first_of(hs);
#ifdef __GNUC__
		[[gnu::unused]]
#else
		[[maybe_unused]]
#endif
		typename std::decay_t<Range>::const_iterator it2 = r | srook::adaptors::find_first_of(hs.cbegin(),hs.cend());
#ifdef __GNUC__
		[[gnu::unused]]
#else
		[[maybe_unused]]
#endif
		typename std::decay_t<Range>::const_iterator it3 = r | srook::adaptors::find_first_of(hs,f);
#ifdef __GNUC__
		[[gnu::unused]]
#else
		[[maybe_unused]]
#endif
		typename std::decay_t<Range>::const_iterator it4 = r | srook::adaptors::find_first_of(hs.cbegin(),hs.cend(),f);
	}
	void operator()(const std::string& str)const
	{
		using namespace std::string_literals;
		auto search_string="important"s;
#ifdef __GNUC__
		[[gnu::unused]]
#else
		[[maybe_unused]]
#endif	
		std::string::size_type result1 = str | srook::adaptors::find_first_of(search_string);
/*#ifdef __GNUC__
		[[gnu::unused]]
#else
		[[maybe_unused]]
#endif
		std::string::size_type result2 = str | srook::adaptors::find_first_of(search_string.c_str(),search_string.size());
#ifdef __GNUC__
		[[gnu::unused]]
#else
		[[maybe_unused]]
#endif
		std::string::size_type result3 = str | srook::adaptors::find_first_of(search_string.c_str(),search_string.size(),search_string.size());*/
	}
}find_first_of_check={};

const struct binary_search_check_t{
	template<class Range>
	void operator()(Range r)const
	{
#ifdef __GNUC__
		[[gnu::unused]]
#else
		[[maybe_unused]]
#endif
		bool b1 = r | srook::adaptors::sort() | srook::adaptors::binary_search(4);
#ifdef __GNUC__
		[[gnu::unused]]
#else
		[[maybe_unused]]
#endif
		bool b2 = r | srook::adaptors::binary_search(4,std::greater<>());
	}
	template<class T>
	void operator()(const std::list<T>&)const{}
}binary_search_check={};


int main()
{
	const auto tests=std::make_tuple(
			make_tester(
				[](const auto& x)
				{
#ifdef __GNUC__
					[[gnu::unused]]
#else
					[[maybe_unused]]
#endif
					typename std::decay_t<decltype(x)>::const_iterator it = x | srook::adaptors::adjacent_find();
#ifdef __GNUC__
					[[gnu::unused]]
#else
					[[maybe_unused]]
#endif
					decltype(it) it1 = x | srook::adaptors::adjacent_find(std::greater<>());
				}
			),
			make_tester(
				[](const auto& x)
				{
#ifdef __GNUC__
					[[gnu::unused]]
#else
					[[maybe_unused]]
#endif
					bool b = x | srook::adaptors::all_of([](const auto& x){return x%2==0;});
				}
			),
			make_tester(binary_search_check),
			make_tester(
				[](const auto& x)
				{
#ifdef __GNUC__
					[[gnu::unused]]
#else
					[[maybe_unused]]
#endif
					auto test = x | srook::adaptors::copied;
				}
			),
			make_tester(
				[](const auto& x)
				{
#ifdef __GNUC__
					[[gnu::unused]]
#else
					[[maybe_unused]]
#endif
					auto test = x | srook::adaptors::copied_backward;
				}
			),
			make_tester(
				[](const auto& x)
				{
#ifdef __GNUC__
					[[gnu::unused]]
#else
					[[maybe_unused]]
#endif
					auto test = x | srook::adaptors::copied_if([](const auto& x){return x%2==0;});
				}
			),
			make_tester(
				[](const auto& x)
				{
#ifdef __GNUC__
					[[gnu::unused]]
#else
					[[maybe_unused]]
#endif
					auto test = x | srook::adaptors::copied_n(42);
				}
			),
			make_tester(
				[](const auto& x)
				{
					x | srook::adaptors::copy(std::ostream_iterator<typename std::decay_t<decltype(x)>::value_type>(std::cout," "));
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
					x | srook::adaptors::copy_if(std::ostream_iterator<typename std::decay_t<decltype(x)>::value_type>(std::cout," "),[](auto&& x){return x%2==0;});
				}
			),
			make_tester(
				[](const auto& x)
				{
					x | srook::adaptors::copy_n(4,std::ostream_iterator<typename std::decay_t<decltype(x)>::value_type>(std::cout," "));
				}
			),
			make_tester(
				[](const auto& x)
				{
#ifdef __GNUC__
					[[gnu::unused]]
#else
					[[maybe_unused]]
#endif
					typename std::iterator_traits<typename std::decay_t<decltype(x)>::iterator>::difference_type value= x | srook::adaptors::count(10);
				}
			),
			make_tester(
				[](const auto& x)
				{
#ifdef __GNUC__
					[[gnu::unused]]
#else
					[[maybe_unused]]
#endif
					typename std::iterator_traits<typename std::decay_t<decltype(x)>::iterator>::difference_type value = 
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
#ifdef __GNUC__
					[[gnu::unused]]
#else
					[[maybe_unused]]
#endif
					bool b0 = x | srook::adaptors::equal(range);
#ifdef __GNUC__
					[[gnu::unused]]
#else
					[[maybe_unused]]
#endif
					bool b1 = x | srook::adaptors::equal(range.begin());
#ifdef __GNUC__
					[[gnu::unused]]
#else
					[[maybe_unused]]
#endif
					bool b2 = x | srook::adaptors::equal(range,pred);
#ifdef __GNUC__
					[[gnu::unused]]
#else
					[[maybe_unused]]
#endif
					bool b3 = x | srook::adaptors::equal(range.begin(),range.end(),pred);
				}
			),
			make_tester(
				[](auto x)
				{
#ifdef __GNUC__
					[[gnu::unused]]
#else
					[[maybe_unused]]
#endif
					auto test = x | srook::adaptors::equal_range(5);
#ifdef __GNUC__
					[[gnu::unused]]
#else
					[[maybe_unused]]
#endif
					auto test1 = x | srook::adaptors::equal_range(5,std::greater<>());
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
#ifdef __GNUC__
						[[gnu::unused]]
#else
						[[maybe_unused]]
#endif
						typename std::decay_t<decltype(x)>::const_iterator it1 = x | srook::adaptors::find_end(hs);
#ifdef __GNUC__
						[[gnu::unused]]
#else
						[[maybe_unused]]
#endif
						typename std::decay_t<decltype(x)>::const_iterator it2 = x | srook::adaptors::find_end(hs.cbegin(),hs.cend());
#ifdef __GNUC__
						[[gnu::unused]]
#else
						[[maybe_unused]]
#endif
						typename std::decay_t<decltype(x)>::const_iterator it3 = x | srook::adaptors::find_end(hs,f);
#ifdef __GNUC__
						[[gnu::unused]]
#else
						[[maybe_unused]]
#endif
						typename std::decay_t<decltype(x)>::const_iterator it4 = x | srook::adaptors::find_end(hs.cbegin(),hs.cend(),f);
					}
			),
			make_tester(find_first_of_check)/*,
			make_tester(
				[](auto r)
				{
					r | srook::adaptors::sort();
					r | srook::adaptors::sort(std::greater<>());
				}		
			)*/
	);
	
	auto ap=make_applyer(std::move(tests),make_test_ranges());
	ap.play_invoker();
}

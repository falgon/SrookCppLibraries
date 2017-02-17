#ifndef INCLUDED_ADAPTOR_FIND
#define INCLUDED_ADAPTOR_FIND
#include<srook/range/adaptor/adaptor_operator.hpp>

#if __has_include(<boost/optional.hpp>)
#define POSSIBLE_TO_INCLUDE_BOOST_OPTIONAL
#include<boost/optional.hpp>
#elif __has_include(<optional>)
#define POSSIBLE_TO_STD_OPTIONAL
#include<optional>
#else
#include<srook/optional.hpp>
#endif


#if __has_include(<boost/range/algorithm/find.hpp>)
#define POSSIBLE_TO_INCLUDE_BOOST_RANGE_FIND
#include<boost/range/algorithm/find.hpp>
#elif
#include<algorithm>
#endif

namespace srook{
namespace pipealgo{
namespace detail{
inline namespace v1{

namespace mpl{

template<class T,class=std::void_t<>>
constexpr bool has_size_type=std::false_type::value;
template<class T>
constexpr bool has_size_type<T,std::void_t<typename T::size_type>> =std::true_type::value;

template<bool b,class T>
struct size_type_select{
	using type=typename T::size_type;
};
template<class T>
struct size_type_select<false,T>{
	using type=std::size_t;
};

}

template<
	class Target,
	class Pos=typename mpl::size_type_select<mpl::has_size_type<Target>,Target>::type
>
class find_t{
	Target target_;
	Pos pos_;
#ifdef POSSIBLE_TO_INCLUDE_BOOST_OPTIONAL
	boost::optional<Pos> n_;
#elif defined(POSSIBLE_TO_STD_OPTIONAL)
	std::optional<Pos> n_;
#else
	srook::optional<Pos> n_;
#endif

	// If you wanna use member function of find,the type must have function find of below form.
	template<
		class T,
		typename T::size_type (T::*)(typename T::value_type,typename T::size_type)const noexcept 
	>
	struct mfunction_findable final{
		using type=T;
	};
	template<class T,class=T>
	struct mfunction_f:std::false_type{};
	template<class T>
	struct mfunction_f<T,typename mfunction_findable<T,&T::find>::type>:std::true_type{};
	template<class T>
	static constexpr bool has_mfind_v=mfunction_f<T>::value;
public:
	explicit constexpr find_t(
			Target t,
			Pos pos,
			Pos n=0
	)noexcept
		:target_(std::move(t)),
		pos_(std::move(pos)),
		n_(std::move(n))
	{}
	
	explicit constexpr find_t(
			Target t
	)noexcept
		:target_(std::move(t)),
		pos_(0),
		n_(
#ifdef POSSIBLE_TO_INCLUDE_BOOST_OPTIONAL
				boost::none
#elif defined(POSSIBLE_TO_STD_OPTIONAL)
				std::nullopt
#else
				srook::nullopt
#endif
		)
	{}
	
	template<class Range,std::enable_if_t<has_mfind_v<std::remove_reference_t<Range>>,std::nullptr_t> =nullptr>
	auto operator()(Range&& r)
	{
		return !n_?r.find(std::move(target_.c_str()),std::move(pos_),std::move(n_.value())):r.find(std::move(target_),std::move(pos_));
	}

	template<class Range,std::enable_if_t<!has_mfind_v<std::remove_reference_t<Range>>,std::nullptr_t> =nullptr>
	auto operator()(Range&& r)
	{
#ifdef POSSIBLE_TO_INCLUDE_BOOST_RANGE_FIND
		return boost::find(std::forward<Range>(r),std::move(target_));
#elif
		return std::find(r.cbegin(),r.cend(),std::move(target_));
#endif
	}
};

template<
	class Target,
	std::enable_if_t<
		mpl::has_size_type<std::remove_reference_t<Target>>,
		std::nullptr_t
	> =nullptr
>
find_t<std::remove_reference_t<Target>,typename std::remove_reference_t<Target>::size_type>
find(Target&& t,typename std::remove_reference_t<Target>::size_type pos,typename std::remove_reference_t<Target>::size_type n)
{
	return find_t<
		std::remove_reference_t<Target>,
		typename std::remove_reference_t<Target>::size_type
	>(std::forward<Target>(t),std::move(pos),std::move(n));
}

template<
	class Target,
	std::enable_if_t<
		mpl::has_size_type<std::remove_reference_t<Target>>,
		std::nullptr_t
	> =nullptr
>
find_t<std::remove_reference_t<Target>,typename std::remove_reference_t<Target>::size_type>
find(Target&& t,typename std::remove_reference_t<Target>::size_type pos=0)
{
	return find_t<
		std::remove_reference_t<Target>,
		typename std::remove_reference_t<Target>::size_type
	>(std::forward<Target>(t),std::move(pos));
}

template<
	class Target,
	std::enable_if_t<
		!mpl::has_size_type<std::remove_reference_t<Target>>,
		std::nullptr_t
	> =nullptr
>
find_t<std::remove_reference_t<Target>>
find(Target&& t)
{
	return find_t<std::remove_reference_t<Target>>(std::forward<Target>(t));
}

} // inline namespace v1
} // namespace detail

using detail::find;

} // namespace pipealgo
} // namespace srook

#ifdef INCLUDED_BOOST_RANGE_FIND
#undef INCLUDED_BOOST_RANGE_FIND
#endif
#ifdef POSSIBLE_TO_INCLUDE_BOOST_OPTIONAL
#undef POSSIBLE_TO_INCLUDE_BOOST_OPTIONAL
#endif
#ifdef POSSIBLE_TO_STD_OPTIONAL
#undef POSSIBLE_TO_STD_OPTIONAL
#endif
#endif

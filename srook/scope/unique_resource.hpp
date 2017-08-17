// This header inspired P0052R5
// Copyright (C) 2017 roki

#ifndef INCLUDED_SROOK_SCOPE_UNIQUE_RESOURCE_HPP
#define INCLUDED_SROOK_SCOPE_UNIQUE_RESOURCE_HPP
#include<srook/config/noexcept_detection.hpp>
#include<srook/config/require.hpp>
#include<type_traits>
#include<utility>

namespace srook{

namespace detail{

template<class T>
struct is_nothrow_movable : std::integral_constant<bool,std::is_nothrow_move_constructible<T>::value and std::is_nothrow_move_assignable<T>::value>{};

} // namespace detail

template<class R,class D>
class unique_resource {
	static_assert(std::is_nothrow_move_constructible<R>::value or std::is_copy_constructible<R>::value,"resource must be nothrow_move_constructible or copy_consturcitble");
	static_assert(std::is_nothrow_move_constructible<D>::value or std::is_copy_constructible<D>::value,"deleter must be nothrow_move_constructible or copy_consturcitble");

	static constexpr auto is_nothrow_delete_v = noexcept(std::declval<D&>()(std::declval<R&>()));
	static constexpr auto is_nothrow_swappable_v = is_nothrow_delete_v and detail::is_nothrow_movable<R>::value and detail::is_nothrow_movable<D>::value;

	unique_resource& operator=(const unique_resource&) = delete;
	unique_resource(const unique_resource&) = delete;
public:
	template<class RR,class DD,REQUIRES(std::is_constructible<R,RR>::value and std::is_constructible<D,DD>::value)>
	explicit unique_resource(RR&& r,DD&& d) : resource(std::forward<RR>(r)),deleter(std::forward<DD>(d))
	{}

	unique_resource(unique_resource&& rhs)
		: resource(std::move(rhs.resource)),deleter(std::move(rhs.deleter)),execute_on_destruction{std::exchange(rhs.execute_on_destruction,false)}
	{}

	unique_resource& operator=(unique_resource&& rhs)
	SROOK_NOEXCEPT(std::is_nothrow_delete_v and std::is_nothrow_move_assignable<R>::value and std::is_nothrow_move_assignable<D>::value)
	{
		static_assert(std::is_nothrow_move_assignable<R>::value or std::is_copy_assignable<R>::value,"The resource must be nothrow-move assignable, or copy assignable");
		static_assert(std::is_nothrow_move_assignable<D>::value or std::is_copy_assignable<R>::value,"The resource must be nothrow-move assignable, or copy assignable");

		if(&rhs == this)return *this;

		reset();
		deleter = std::move(rhs.deleter);
		resource = std::move(rhs.resource);
		execute_on_destruction = std::exchange(rhs.execute_on_destruction,false);
		return *this;
	}

	~unique_resource()
	{
		reset();
	}

	void swap(unique_resource& other)
	SROOK_NOEXCEPT(std::is_nothrow_move_constructible<T>::value and std::is_nothrow_move_assignable)
	{
#if __cplusplus >= 201703L
		if constexpr(is_nothrow_swappable_v){
#else
		if(is_nothrow_swappable_v){
#endif
			using std::swap;
			swap(execute_on_destruction,other.execute_on_destruction);
			swap(resource,other.resource);
			swap(deleter,other.deleter);
		}else{
			auto tmp = std::move(*this);
			*this = std::move(other);
			other = std::move(tmp);
		}
	}

	void reset() SROOK_NOEXCEPT(is_nothrow_delete_v)
	{
		if(execute_on_destruction){
			execute_on_destruction = false;
			deleter(resource);
		}
	}

	template<class RR>
	void reset(RR& r) SROOK_NOEXCEPT(is_nothrow_delete_v)
	{
		reset();
		resource = std::move(r);
		execute_on_destruction = true;
		release();
	}

	R release() SROOK_NOEXCEPT()
	{
		execute_on_destruction = false;
		return get();
	}

	const R& get() const noexcept
	{
		return resource;
	}

	R operator->() const noexcept
	{
		return resource;
	}

	typename std::add_lvalue_reference<typename std::remove_pointer<R>::type>::type operator*() const
	{
		return resource;
	}
private:
	R resource;
	D deleter;
	bool execute_on_destruction{true};
};

template<class R,class D>
unique_resource<typename std::decay<R>::type,typename std::decay<D>::type> make_unique_resource(R&& r,D&& d)
//noexcept(noexcept(unique_resource<typename std::decay<R>::type,typename std::decay<D>::type>{std::forward<R>(r),std::forward<D>(d)}))
{
	return unique_resource<typename std::decay<R>::type,typename std::decay<D>::type>(std::forward<R>(r),std::forward<D>(d));
}

template<class R,class D>
unique_resource<R,typename std::remove_reference<D>::type> make_unique_resource(std::reference_wrapper<R> r,D&& d)
noexcept(noexcept(unique_resource<R&,typename std::decay<D>::type>{r.get(),std::forward<D>(d)}))
{
	return unique_resource<R,typename std::remove_reference<D>::type>(r.get(),std::forward<D>(d));
}

#if __cplusplus >= 201703L
template<class R,class D>
unique_resource(R&& r,D&& d) -> unique_resource<typename std::decay<R>::type,typename std::decay<D>::type>;

template<class R,class D>
unique_resource(std::reference_wrapper<R> r,D&& d) -> unique_resource<R&,typename std::decay<D>::type>;
#endif

} // namespace
#endif

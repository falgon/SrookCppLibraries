// This header inspired P0052R5
// Copyright (C) 2011-2019 Roki. Distributed under the MIT License

#ifndef INCLUDED_SROOK_SCOPE_UNIQUE_RESOURCE_HPP
#define INCLUDED_SROOK_SCOPE_UNIQUE_RESOURCE_HPP
#include <srook/config/attribute/visibility.hpp>
#include <srook/config/cpp_predefined.hpp>
#include <srook/config/feature.hpp>
#include <srook/config/require.hpp>
#include <srook/type_traits/is_constructible.hpp>
#include <srook/type_traits/is_copy_assignable.hpp>
#include <srook/type_traits/remove_pointer.hpp>
#include <srook/type_traits/is_copy_constructible.hpp>
#include <srook/type_traits/decay.hpp>
#include <srook/utility/move.hpp>
#include <srook/utility/noncopyable.hpp>
#include <srook/utility/exchange.hpp>
#include <type_traits>

#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
#    define CJUNCT srook::type_traits::detail::Land
#    define DJUNCT srook::type_traits::detail::Lor
#else
#    define CJUNCT srook::type_traits::detail::Land_2
#    define DJUNCT srook::type_traits::detail::Lor_2
#endif

namespace srook {
namespace scope {
namespace detail {

template <class T>
struct is_nothrow_movable
    : bool_constant<CJUNCT<std::is_nothrow_move_constructible<T>, std::is_nothrow_move_assignable<T> >::value> {
};

} // namespace detail

template <class R, class D>
class SROOK_ATTRIBUTE_TEMPLATE_VIS_DEFAULT unique_resource : noncopyable<unique_resource<R, D> > {
    SROOK_STATIC_ASSERT((DJUNCT<std::is_nothrow_move_constructible<R>, srook::is_copy_constructible<R> >::value),
                        "resource must be nothrow_move_constructible or copy_consturcitble");
    SROOK_STATIC_ASSERT((DJUNCT<std::is_nothrow_move_constructible<D>, srook::is_copy_constructible<D> >::value),
                        "deleter must be nothrow_move_constructible or copy_consturcitble");
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
    static SROOK_CONSTEXPR bool
        is_nothrow_delete_v = noexcept(declval<D&>()(declval<R&>())),
        is_nothrow_swappable_v = is_nothrow_delete_v and CJUNCT<detail::is_nothrow_movable<R>, detail::is_nothrow_movable<D> >::value;
#endif
    unique_resource& operator=(const unique_resource&) SROOK_EQ_DELETE
    unique_resource(const unique_resource&) SROOK_EQ_DELETE

public:
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
    template <class RR, class DD, REQUIRES(CJUNCT<is_constructible<R, RR>, is_constructible<D, DD> >::value)>
    SROOK_ATTRIBUTE_INLINE_VISIBILITY explicit 
	unique_resource(RR&& r, DD&& d)
        : resource(srook::forward<RR>(r)), deleter(srook::forward<DD>(d))
    {}
#else
	template <class RR, class DD>
	SROOK_ATTRIBUTE_INLINE_VISIBILITY explicit
	unique_resource(utility::cxx03::move_tag<RR> r, utility::cxx03::move_tag<DD> d, 
			REQUIRES(CJUNCT<is_constructible<R, RR>, is_constructible<D, DD> >::value) = SROOK_NULLPTR_T())
		: resource(r.get()), deleter(d.get()), execute_on_destruction(true)
	{}

	template <class RR, class DD>
	SROOK_ATTRIBUTE_INLINE_VISIBILITY explicit
	unique_resource(const RR& r, const DD& d,
			REQUIRES(CJUNCT<is_constructible<R, RR>, is_constructible<D, DD> >::value) = SROOK_NULLPTR_T())
		: resource(r), deleter(d), execute_on_destruction(true)
	{}
#endif

    SROOK_ATTRIBUTE_INLINE_VISIBILITY
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
    unique_resource(unique_resource&& rhs)
        : resource(srook::move(rhs.resource)),
          deleter(srook::move(rhs.deleter)),
          execute_on_destruction(exchange(rhs.execute_on_destruction, false))
#else
    unique_resource(utility::cxx03::move_tag<unique_resource> rhs)
		: resource(rhs.get().resource),
          deleter(rhs.get().deleter),
		  execute_on_destruction(exchange(rhs.get().execute_on_destruction, false))
#endif
    {}


    SROOK_ATTRIBUTE_INLINE_VISIBILITY
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
    unique_resource& operator=(unique_resource&& rhs)
#else
	unique_resource& operator=(utility::cxx03::move_tag<unique_resource> rhs)
#endif
    SROOK_NOEXCEPT((is_nothrow_delete_v and CJUNCT<std::is_nothrow_move_assignable<R>, std::is_nothrow_move_assignable<D> >::value))
    {
        SROOK_STATIC_ASSERT((DJUNCT<std::is_nothrow_move_assignable<R>, is_copy_assignable<R> >::value),
                            "The resource must be nothrow-move assignable, or copy assignable");
        SROOK_STATIC_ASSERT((DJUNCT<std::is_nothrow_move_assignable<D>, is_copy_assignable<R> >::value),
                            "The resource must be nothrow-move assignable, or copy assignable");

        if (&rhs == this) return *this;

        reset();
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
        deleter = srook::move(rhs.deleter);
        resource = srook::move(rhs.resource);
        execute_on_destruction = exchange(rhs.execute_on_destruction, false);
#else
		deleter = rhs.get().deleter;
		resource = rhs.get().resource;
		execute_on_destruction = exchange(rhs.get().execute_on_destruction, false);
#endif
        return *this;
    }

    SROOK_ATTRIBUTE_INLINE_VISIBILITY
    ~unique_resource()
    {
        reset();
    }

    void swap(unique_resource& other)
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
    SROOK_NOEXCEPT(is_nothrow_swappable_v)
#endif
    {
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT 
        SROOK_IF_CONSTEXPR(is_nothrow_swappable_v) {
            using std::swap;
            swap(execute_on_destruction, other.execute_on_destruction);
            swap(resource, other.resource);
            swap(deleter, other.deleter);
		} else {
#endif
            unique_resource tmp = srook::move(*this);
            *this = srook::move(other);
            other = srook::move(tmp);
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
        }
#endif
    }

    void reset()
    SROOK_NOEXCEPT(is_nothrow_delete_v)
    {
        if (execute_on_destruction) {
            execute_on_destruction = false;
            deleter(resource);
        }
    }

    template <class RR>
    void reset(RR& r)
    SROOK_NOEXCEPT(is_nothrow_delete_v)
    {
        reset();
        resource = srook::move(r);
        execute_on_destruction = true;
        release();
    }

    SROOK_FORCE_INLINE
    R release() SROOK_NOEXCEPT_TRUE
    {
        execute_on_destruction = false;
        return get();
    }

    SROOK_FORCE_INLINE
    const R& get() const SROOK_NOEXCEPT_TRUE
    {
        return resource;
    }

    SROOK_FORCE_INLINE
    R operator->() const SROOK_NOEXCEPT_TRUE
    {
        return resource;
    }

    SROOK_FORCE_INLINE
    typename std::add_lvalue_reference<typename srook::remove_pointer<R>::type>::type
    operator*() const SROOK_NOEXCEPT_TRUE
    {
        return resource;
    }

private:
    R resource;
    D deleter;
    bool execute_on_destruction
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
        = true
#endif
        ;
};

template <class R, class D>
unique_resource<typename decay<R>::type, typename decay<D>::type>
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
make_unique_resource(R&& r, D&& d)
#else
make_unique_resource(utility::cxx03::move_tag<R> r, utility::cxx03::move_tag<D> d)
#endif
SROOK_NOEXCEPT((is_nothrow_constructible<unique_resource<typename decay<R>::type, typename decay<D>::type>, R, D>::value))
{
    return unique_resource<typename decay<R>::type, typename decay<D>::type>(srook::forward<R>(r), srook::forward<D>(d));
}

template <class R, class D>
unique_resource<R, typename remove_reference<D>::type>
make_unique_resource(std::reference_wrapper<R> r, 
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
		D&& d
#else
		utility::cxx03::move_tag<D> d
#endif
		)
SROOK_NOEXCEPT((is_nothrow_constructible<unique_resource<R, typename remove_reference<D>::type>, decltype(r.get()), declval<D>()>::value))
{
    return unique_resource<R, typename srook::remove_reference<D>::type>(r.get(), srook::forward<D>(d));
}

#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS17_CONSTANT
template <class R, class D>
unique_resource(R&& r, D&& d)
-> unique_resource<typename decay<R>::type, typename decay<D>::type>;

template <class R, class D>
unique_resource(std::reference_wrapper<R> r, D&& d)
-> unique_resource<R&, typename decay<D>::type>;
#endif

} // namespace scope

using scope::make_unique_resource;
using scope::unique_resource;

} // namespace srook

#    undef CJUNCT
#    undef DJUNCT
#endif

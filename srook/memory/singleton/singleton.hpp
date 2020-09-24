// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_MEMORY_SINGLETON_SINGLETON_HPP
#define INCLUDED_SROOK_MEMORY_SINGLETON_SINGLETON_HPP
#ifdef _MSC_VER
#   pragma once
#endif

#include <srook/config.hpp>
#include <srook/utility.hpp>
#include <srook/memory/unique_ptr.hpp>
#include <srook/memory/launder.hpp>
#include <srook/memory_resource/polymorphic_allocator.hpp>
#include <srook/mpl/variadic_types.hpp>

namespace srook {
namespace memory {
SROOK_INLINE_NAMESPACE(v1)

namespace singleton_policy {

struct use_default_ctors;
struct use_allocator_ctors;

} // namespace singleton_policy

namespace detail {

template <class, class, class> class singleton_core;

template <class T, class Allocator>
class singleton_core<T, Allocator, singleton_policy::use_default_ctors> : private enable_copy_move<true, false, false, false> {
protected:
    typedef 
#ifdef POSSIBLE_TO_INCLUDE_STD_MEMORY
        std::unique_ptr<Allocator>
#elif defined(POSSIBLE_TO_INCLUDE_BOOST_UNIQUE_PTR)
        boost::unique_ptr<Allocator>
#else
        unique_ptr<Allocator>
#endif
    allocator_pointer_type;

    typedef Allocator allocator_type;
    typedef std::allocator_traits<allocator_type> traits_type;
    typedef SROOK_DEDUCED_TYPENAME traits_type::value_type value_type;
    typedef SROOK_DEDUCED_TYPENAME traits_type::pointer pointer;
    typedef SROOK_DEDUCED_TYPENAME traits_type::const_pointer const_pointer;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    
    template <class... Ts>
    SROOK_FORCE_INLINE static reference
    instance(Ts&&... ts) 
    {
        return !ptr_ ? alloc_construct(srook::forward<Ts>(ts)...) : *ptr_;
    }

    SROOK_FORCE_INLINE static void destroy() SROOK_NOEXCEPT(is_nothrow_destructible<value_type>::value)
    {
        if (ptr_ && alloc_ptr_) {
            ptr_->~value_type();
            traits_type::deallocate(*alloc_ptr_, ptr_, 1);
            ptr_ = SROOK_NULLPTR;
            alloc_ptr_.reset();
        }
    }
    
    template <class... Ts>
    struct special_constructible
        : public is_invocable<SROOK_DECLTYPE(static_cast<void (*)(allocator_type&, pointer, Ts...)>(traits_type::construct)), allocator_type&, pointer, Ts...> {};
private:
    template <class... Ts>
    SROOK_FORCE_INLINE static reference
    alloc_construct(Ts&&... ts)
    {
        alloc();
        return construct(srook::forward<Ts>(ts)...);
    }

    SROOK_FORCE_INLINE static void alloc()
    {
        SROOK_TRY {
            ptr_ = traits_type::allocate(*alloc_ptr_, 1);
        } SROOK_CATCH (const std::bad_alloc& e) {
            SROOK_THROW e;
        } SROOK_CATCH (...) {
            destroy();
            SROOK_THROW;
        }
    }

    template <class... Ts>
    SROOK_FORCE_INLINE static SROOK_DEDUCED_TYPENAME 
    enable_if<special_constructible<Ts&&...>::value, reference>::type
    construct(Ts&&... ts) 
    {
        return *(ptr_ = new(ptr_) value_type(srook::forward<Ts>(ts)...));
    }
protected:   
    singleton_core() SROOK_DEFAULT

    static SROOK_INLINE_VARIABLE allocator_pointer_type alloc_ptr_ = SROOK_NULLPTR;
    static SROOK_INLINE_VARIABLE pointer ptr_ = SROOK_NULLPTR;
};

template <class T, class Allocator>
class singleton_core<T, Allocator, singleton_policy::use_allocator_ctors> : private enable_copy_move<true, false, false, false> {
protected:
    typedef 
#ifdef POSSIBLE_TO_INCLUDE_STD_MEMORY
        std::unique_ptr<Allocator>
#elif defined(POSSIBLE_TO_INCLUDE_BOOST_UNIQUE_PTR
        boost::unique_ptr<Allocator>
#else
        unique_ptr<Allocator>
#endif
    allocator_pointer_type;

    typedef Allocator allocator_type;
    typedef std::allocator_traits<allocator_type> traits_type;
    typedef SROOK_DEDUCED_TYPENAME traits_type::value_type value_type;
    typedef SROOK_DEDUCED_TYPENAME traits_type::pointer pointer;
    typedef SROOK_DEDUCED_TYPENAME traits_type::const_pointer const_pointer;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    
    template <class... Ts>
    SROOK_FORCE_INLINE static reference
    instance(Ts&&... ts) 
    {
        return !ptr_ ? alloc_construct(srook::forward<Ts>(ts)...) : *ptr_;
    }

    SROOK_FORCE_INLINE static void destroy() SROOK_NOEXCEPT(is_nothrow_destructible<value_type>::value)
    {
        if (ptr_ && alloc_ptr_) {
            traits_type::destroy(*alloc_ptr_, ptr_);
            traits_type::deallocate(*alloc_ptr_, ptr_, 1);
            ptr_ = SROOK_NULLPTR;
            alloc_ptr_.reset();
        }
    }
    
    template <class... Ts>
    struct special_constructible
        : public is_invocable<SROOK_DECLTYPE(static_cast<void (*)(allocator_type&, pointer, Ts...)>(traits_type::construct)), allocator_type&, pointer, Ts...> {};
private:
    template <class... Ts>
    SROOK_FORCE_INLINE static reference
    alloc_construct(Ts&&... ts)
    {
        alloc();
        return construct(srook::forward<Ts>(ts)...);
    }

    SROOK_FORCE_INLINE static void alloc()
    {
        SROOK_TRY {
            ptr_ = traits_type::allocate(*alloc_ptr_, 1);
        } SROOK_CATCH (const std::bad_alloc& e) {
            SROOK_THROW e;
        } SROOK_CATCH (...) {
            destroy();
            SROOK_THROW;
        }
    }

    template <class... Ts>
    SROOK_FORCE_INLINE static SROOK_DEDUCED_TYPENAME 
    enable_if<type_traits::detail::Land<special_constructible<Ts&&...>, type_traits::detail::Lnot<is_pointer<pointer>>>::value, reference>::type
    construct(Ts&&... ts) SROOK_NOEXCEPT((traits_type::construct(*alloc_ptr_, ptr_, srook::forward<Ts>(ts)...)))
    {
        // NOTE: 
        //  It is impossible to laund ptr_ by [basic.life] and allocator requirement, 
        //  so if value_type has non-static const data member or non-static reference type member, it cause undefined behavior.
        //  See more detail: http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2017/p0532r0.pdf
        traits_type::construct(*alloc_ptr_, ptr_, srook::forward<Ts>(ts)...);
        return *ptr_;
    }

    template <class... Ts>
    SROOK_FORCE_INLINE static SROOK_DEDUCED_TYPENAME 
    enable_if<type_traits::detail::Land<special_constructible<Ts&&...>, is_pointer<pointer>>::value, reference>::type
    construct(Ts&&... ts) SROOK_NOEXCEPT((traits_type::construct(*alloc_ptr_, ptr_, srook::forward<Ts>(ts)...)))
    {
        traits_type::construct(*alloc_ptr_, ptr_, srook::forward<Ts>(ts)...);
        return *(ptr_ = srook::launder(ptr_));
    }
protected:   
    singleton_core() SROOK_DEFAULT

    static SROOK_INLINE_VARIABLE allocator_pointer_type alloc_ptr_ = SROOK_NULLPTR;
    static SROOK_INLINE_VARIABLE pointer ptr_ = SROOK_NULLPTR;
};


template <class T, class Allocator, class Policy>
class singleton_base : protected singleton_core<T, Allocator, Policy> {
protected:
    typedef singleton_core<T, Allocator, Policy> base_type;
    typedef SROOK_DEDUCED_TYPENAME base_type::allocator_type allocator_type;
    typedef SROOK_DEDUCED_TYPENAME base_type::traits_type traits_type;
    typedef SROOK_DEDUCED_TYPENAME base_type::value_type value_type;
    typedef SROOK_DEDUCED_TYPENAME base_type::pointer pointer;
    typedef SROOK_DEDUCED_TYPENAME base_type::const_pointer const_pointer;
    typedef SROOK_DEDUCED_TYPENAME base_type::reference reference;
    typedef SROOK_DEDUCED_TYPENAME base_type::const_reference const_reference;
    
    template <class... Us>
    struct construct_requires
        : public type_traits::detail::Land<
            type_traits::detail::Lnot<is_same<SROOK_DEDUCED_TYPENAME First<SROOK_DEDUCED_TYPENAME decay<Us>::type...>::type, allocator_type>>, // the first argument type should not allocator_type
            SROOK_DEDUCED_TYPENAME base_type::template special_constructible<Us...> // value_type should be constructible with Us...
          > {};
protected:
    template <class... Ts>
    SROOK_FORCE_INLINE static 
    SROOK_DEDUCED_TYPENAME enable_if<construct_requires<Ts&&...>::value, reference>::type
    instance(Ts&&... ts) 
    {
        if (!base_type::alloc_ptr_) {
            SROOK_TRY {
                base_type::alloc_ptr_.reset(new allocator_type());
            } SROOK_CATCH (const std::bad_alloc& e) {
                SROOK_THROW e;
            } SROOK_CATCH (...) {
                SROOK_THROW;
            }
        }
        return base_type::instance(srook::forward<Ts>(ts)...);
    }

    template <class... Ts>
    SROOK_FORCE_INLINE static SROOK_DEDUCED_TYPENAME 
    enable_if<base_type::template special_constructible<Ts&&...>::value, reference>::type
    instance(const allocator_type& alloc = allocator_type(), Ts&&... ts) 
    {
        if (!base_type::alloc_ptr_) {
            SROOK_TRY {
                base_type::alloc_ptr_.reset(new allocator_type(alloc));
            } SROOK_CATCH (const std::bad_alloc& e) {
                SROOK_THROW e;
            } SROOK_CATCH (...) {
                SROOK_THROW;
            }
        }
        return base_type::instance(srook::forward<Ts>(ts)...);
    }
    
    singleton_base() SROOK_DEFAULT
};

} // namespace detail

template <class T, class Allocator = std::allocator<T>, class Policy = singleton_policy::use_default_ctors>
class singleton : protected detail::singleton_base<T, Allocator, Policy> {
    typedef detail::singleton_base<T, Allocator, Policy> base_type;
public:
    typedef SROOK_DEDUCED_TYPENAME base_type::base_type friend_type; 
    typedef SROOK_DEDUCED_TYPENAME base_type::allocator_type friend_allocator_type;
    typedef SROOK_DEDUCED_TYPENAME base_type::allocator_type allocator_type;
    typedef SROOK_DEDUCED_TYPENAME base_type::traits_type traits_type;
    typedef SROOK_DEDUCED_TYPENAME base_type::value_type value_type;
    typedef SROOK_DEDUCED_TYPENAME base_type::pointer pointer;
    typedef SROOK_DEDUCED_TYPENAME base_type::const_pointer const_pointer;
    typedef SROOK_DEDUCED_TYPENAME base_type::reference reference;
    typedef SROOK_DEDUCED_TYPENAME base_type::const_reference const_reference;

    template <class... Ts>
    SROOK_ATTRIBUTE_NODISCARD SROOK_FORCE_INLINE static reference
    instance(Ts&&... ts) SROOK_NOEXCEPT((base_type::instance(declval<Ts>()...)))
    {
        return base_type::instance(srook::forward<Ts>(ts)...);
    }

    using base_type::destroy;
protected:
    singleton() SROOK_DEFAULT
};

SROOK_INLINE_NAMESPACE_END
} // namespace memory

using memory::singleton;

namespace pmr {
SROOK_INLINE_NAMESPACE(v1)

#if SROOK_CPP_ALIAS_TEMPLATES
template <class T>
using singleton = srook::memory::singleton<T, srook::pmr::polymorphic_allocator<T>>;
#endif

SROOK_INLINE_NAMESPACE_END
} // namespace pmr


} // namespace srook

#endif

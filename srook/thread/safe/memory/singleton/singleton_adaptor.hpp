// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_THREAD_SAFE_MEMORY_SINGLETON_THREAD_SAFE_SINGLETON_ADAPTOR_HPP
#define INCLUDED_SROOK_THREAD_SAFE_MEMORY_SINGLETON_THREAD_SAFE_SINGLETON_ADAPTOR_HPP
#include <srook/thread/safe/memory/singleton/singleton_adaptor.h>

#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
#include <srook/memory/singleton.hpp>
#include <srook/mutex.hpp>
#include <atomic>

namespace srook {
namespace threading {
namespace safe {
SROOK_INLINE_NAMESPACE(v1)
namespace detail {

template <class, template <class...> class> 
class pop_front_apply;

template <class H, class... Ts, template <class...> class base>
class pop_front_apply<pack<H, Ts...>, base> : base<Ts...> {};

template <class>
class singleton_adaptor_core;

// The thread safe singleton_adaptor.
// In this implementation, DCLP with acquire-release semantic is used without std::call_once 
// based on the result of the benchmark.
// reference: http://www.modernescpp.com/images/blog/Threads/Singleton/comparisonSingletonEng.png

template <class T, class Allocator>
class singleton_adaptor_core<srook::memory::singleton<T, Allocator, srook::memory::singleton_policy::use_default_ctors>> : private enable_copy_move<true, false, false, false> {
protected:
    typedef Allocator* allocator_pointer_type; // cannot use std::atomic<std::unique_ptr<Allocator>>

    typedef Allocator allocator_type;
    typedef std::allocator_traits<allocator_type> traits_type;
    typedef SROOK_DEDUCED_TYPENAME traits_type::value_type value_type;
    typedef SROOK_DEDUCED_TYPENAME traits_type::pointer pointer;
    typedef SROOK_DEDUCED_TYPENAME traits_type::const_pointer const_pointer;
    typedef value_type& reference;
    typedef const value_type& const_reference;

    template <class... Us>
    struct is_allocator_construct_invocable
        : public is_invocable<SROOK_DECLTYPE(static_cast<void (*)(allocator_type&, pointer, Us...)>(traits_type::construct)), allocator_type&, pointer, Us...> {};

    template <class... Us>
    struct construct_requires
        : public type_traits::detail::Land<
            type_traits::detail::Lnot<is_same<SROOK_DEDUCED_TYPENAME First<SROOK_DEDUCED_TYPENAME decay<Us>::type...>::type, allocator_type>>,
            pop_front_apply<pack<Us...>, is_allocator_construct_invocable>
          > {};

#if SROOK_CPLUSPLUS == SROOK_CPLUSPLUS17_CONSTANT // P0371R1: Temporarily discourage memory_order_consume
    template <class... Ts>
    SROOK_FORCE_INLINE static 
    SROOK_DEDUCED_TYPENAME enable_if<construct_requires<Ts&&...>::value, reference>::type
    instance(Ts&&... ts)
    {
        // Allocation of the allocator and allocation of the instance are executed collectively in a single thread.
        // At the time of being allocated of the allocator, another thread will not attempt to allocate of instance's memory resource.
        
        allocator_pointer_type ap = alloc_ptr_.load(std::memory_order_acquire);
        pointer p = ptr_.load(std::memory_order_acquire);
        
        if (!ap && !p) {
            lock_guard<mutex> lk(m_);
            ap = alloc_ptr_.load(std::memory_order_relaxed);
            p = ptr_.load(std::memory_order_relaxed);

            if (!ap && !p) {
                SROOK_TRY {
                    ap = new allocator_type();
                    p = traits_type::allocate(*ap, 1);
                } SROOK_CATCH (const std::bad_alloc& e) {
                    SROOK_THROW e;
                } SROOK_CATCH (...) {
                    SROOK_THROW;
                }
                
                p = new(p) value_type(srook::forward<Ts>(ts)...);
                alloc_ptr_.store(ap, std::memory_order_release);
                ptr_.store(p, std::memory_order_release);
            }
        }

        return *p;
    }

    template <class... Ts>
    SROOK_FORCE_INLINE static 
    SROOK_DEDUCED_TYPENAME enable_if<is_allocator_construct_invocable<Ts&&...>::value, reference>::type
    instance(const allocator_type& alloc, Ts&&... ts)
    {
        allocator_pointer_type ap = alloc_ptr_.load(std::memory_order_acquire);
        pointer p = ptr_.load(std::memory_order_acquire);

        if (!ap && !p) {
            lock_guard<mutex> lk(m_);
            ap = alloc_ptr_.load(std::memory_order_relaxed);
            p = ptr_.load(std::memory_order_relaxed);

            if (!ap && !p) {
                SROOK_TRY {
                    ap = new allocator_type(alloc);
                    p = traits_type::allocate(*ap, 1);
                } SROOK_CATCH (const std::bad_alloc& e) {
                    SROOK_THROW e;
                } SROOK_CATCH (...) {
                    SROOK_THROW;
                }

                p = new(p) value_type(srook::forward<Ts>(ts)...);
                alloc_ptr_.store(ap, std::memory_order_release);
                ptr_.store(p, std::memory_order_release);
            }
        }

        return *p;
    }
                

    SROOK_FORCE_INLINE static void destroy() 
    SROOK_NOEXCEPT(is_nothrow_destructible<value_type>::value)
    {
        // Deallocation of the instance and deallocation of the allocator are executed collectively in a single thread.
        // At the time of being deallocated of the instance, another thread will not attempt to deallocate of allocator's memory resources.

        pointer p = ptr_.load(std::memory_order_acquire);
        allocator_pointer_type ap = alloc_ptr_.load(std::memory_order_acquire);

        if (p && ap) { 
            lock_guard<mutex> lk(m_);
            p = ptr_.load(std::memory_order_relaxed);
            ap = alloc_ptr_.load(std::memory_order_relaxed);

            if (p && ap) {
                p->~value_type();
                traits_type::deallocate(*ap, p, 1);
                delete ap;
                
                ptr_.store(SROOK_NULLPTR, std::memory_order_release);
                alloc_ptr_.store(SROOK_NULLPTR, std::memory_order_release);
            }
        }
    }
#else // Data-Dependency Ordering version
    template <class... Ts>
    [[carries_dependency]] SROOK_FORCE_INLINE static 
    SROOK_DEDUCED_TYPENAME enable_if<construct_requires<Ts&&...>::value, reference>::type
    instance(Ts&&... ts)
    {
        allocator_pointer_type ap = alloc_ptr_.load(std::memory_order_consume);
        pointer p = ptr_.load(std::memory_order_consume);
        
        if (!ap && !p) {
            lock_guard<mutex> lk(m_);
            ap = alloc_ptr_.load(std::memory_order_relaxed);
            p = ptr_.load(std::memory_order_relaxed);

            if (!ap && !p) {
                SROOK_TRY {
                    ap = new allocator_type();
                    p = traits_type::allocate(*ap, 1);
                } SROOK_CATCH (const std::bad_alloc& e) {
                    SROOK_THROW e;
                } SROOK_CATCH (...) {
                    SROOK_THROW;
                }
                
                p = new(p) value_type(srook::forward<Ts>(ts)...);
                alloc_ptr_.store(ap, std::memory_order_release);
                ptr_.store(p, std::memory_order_release);
            }
        }

        return *p;
    }

    template <class... Ts>
    [[carries_dependency]] SROOK_FORCE_INLINE static 
    SROOK_DEDUCED_TYPENAME enable_if<is_allocator_construct_invocable<Ts&&...>::value, reference>::type
    instance(const allocator_type& alloc = allocator_type(), Ts&&... ts)
    {
        allocator_pointer_type ap = alloc_ptr_.load(std::memory_order_consume);
        pointer p = ptr_.load(std::memory_order_consume);

        if (!ap && !p) {
            lock_guard<mutex> lk(m_);
            ap = alloc_ptr_.load(std::memory_order_relaxed);
            p = ptr_.load(std::memory_order_relaxed);

            if (!ap && !p) {
                SROOK_TRY {
                    ap = new allocator_type(alloc);
                    p = traits_type::allocate(*ap, 1);
                } SROOK_CATCH (const std::bad_alloc& e) {
                    SROOK_THROW e;
                } SROOK_CATCH (...) {
                    SROOK_THROW;
                }

                p = new(p) value_type(srook::forward<Ts>(ts)...);
                alloc_ptr_.store(ap, std::memory_order_release);
                ptr_.store(p, std::memory_order_release);
            }
        }

        return *p;
    }
                

    [[carries_dependency]] SROOK_FORCE_INLINE static void destroy() 
    SROOK_NOEXCEPT((is_nothrow_destructible<value_type>::value))
    {
        pointer p = ptr_.load(std::memory_order_consume);
        allocator_pointer_type ap = ptr_.load(std::memory_order_consume);

        if (p && ap) {
            lock_guard<mutex> lk(m_);
            p = ptr_.load(std::memory_order_relaxed);
            ap = alloc_ptr_.load(std::memory_order_relaxed);

            if (p && ap) {
                p->~value_type();
                traits_type::deallocate(*ap, p, 1);
                delete ap;
                
                ptr_.store(SROOK_NULLPTR, std::memory_order_release);
                alloc_ptr_.store(SROOK_NULLPTR, std::memory_order_release);
            }
        }
    }
#endif
protected:
    singleton_adaptor_core() SROOK_DEFAULT

#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS17_CONSTANT && SROOK_CPP_INLINE_VARIABLES
    static SROOK_INLINE_VARIABLE std::atomic<pointer> ptr_ = SROOK_NULLPTR;
    static SROOK_INLINE_VARIABLE std::atomic<allocator_pointer_type> alloc_ptr_ = SROOK_NULLPTR;
    static SROOK_INLINE_VARIABLE mutex m_;
#else
    static std::atomic<pointer> ptr_;
    static std::atomic<allocator_pointer_type> alloc_ptr_;
    static mutex m_;
#endif
};

#if SROOK_CPLUSPLUS < SROOK_CPLUSPLUS17_CONSTANT || !SROOK_CPP_INLINE_VARIABLES
template <class T, class Allocator>
std::atomic<SROOK_DEDUCED_TYPENAME singleton_adaptor_core<srook::memory::singleton<T, Allocator, srook::memory::singleton_policy::use_default_ctors>>::pointer> 
singleton_adaptor_core<srook::memory::singleton<T, Allocator, srook::memory::singleton_policy::use_default_ctors>>::ptr_ = SROOK_NULLPTR;
template <class T, class Allocator>
std::atomic<SROOK_DEDUCED_TYPENAME singleton_adaptor_core<srook::memory::singleton<T, Allocator, srook::memory::singleton_policy::use_default_ctors>>::allocator_pointer_type> 
singleton_adaptor_core<srook::memory::singleton<T, Allocator, srook::memory::singleton_policy::use_default_ctors>>::alloc_ptr_ = SROOK_NULLPTR;
template <class T, class Allocator>
mutex singleton_adaptor_core<srook::memory::singleton<T, Allocator, srook::memory::singleton_policy::use_default_ctors>>::m_;
#endif

template <class T, class Allocator>
class singleton_adaptor_core<srook::memory::singleton<T, Allocator, srook::memory::singleton_policy::use_allocator_ctors>> : private enable_copy_move<true, false, false, false> {
protected:
    typedef Allocator* allocator_pointer_type; // cannot use std::atomic<std::unique_ptr<Allocator>>

    typedef Allocator allocator_type;
    typedef std::allocator_traits<allocator_type> traits_type;
    typedef SROOK_DEDUCED_TYPENAME traits_type::value_type value_type;
    typedef SROOK_DEDUCED_TYPENAME traits_type::pointer pointer;
    typedef SROOK_DEDUCED_TYPENAME traits_type::const_pointer const_pointer;
    typedef value_type& reference;
    typedef const value_type& const_reference;

    template <class... Us>
    struct is_allocator_construct_invocable
        : public is_invocable<SROOK_DECLTYPE(static_cast<void (*)(allocator_type&, pointer, Us...)>(traits_type::construct)), allocator_type&, pointer, Us...> {};

    template <class... Us>
    struct construct_requires
        : public type_traits::detail::Land<
            type_traits::detail::Lnot<is_same<SROOK_DEDUCED_TYPENAME First<SROOK_DEDUCED_TYPENAME decay<Us>::type...>::type, allocator_type>>,
            is_allocator_construct_invocable<Us...>
          > {};

#if SROOK_CPLUSPLUS == SROOK_CPLUSPLUS17_CONSTANT // P0371R1: Temporarily discourage memory_order_consume
    template <class... Ts>
    SROOK_FORCE_INLINE static 
    SROOK_DEDUCED_TYPENAME enable_if<construct_requires<Ts&&...>::value, reference>::type
    instance(Ts&&... ts)
    {
        // Allocation of the allocator and allocation of the instance are executed collectively in a single thread.
        // At the time of being allocated of the allocator, another thread will not attempt to allocate of instance's memory resource.
        
        allocator_pointer_type ap = alloc_ptr_.load(std::memory_order_acquire);
        pointer p = ptr_.load(std::memory_order_acquire);
        
        if (!ap && !p) {
            lock_guard<mutex> lk(m_);
            ap = alloc_ptr_.load(std::memory_order_relaxed);
            p = ptr_.load(std::memory_order_relaxed);

            if (!ap && !p) {
                SROOK_TRY {
                    ap = new allocator_type();
                    p = traits_type::allocate(*ap, 1);
                } SROOK_CATCH (const std::bad_alloc& e) {
                    SROOK_THROW e;
                } SROOK_CATCH (...) {
                    SROOK_THROW;
                }
                
                p = construct(ap, p, srook::forward<Ts>(ts)...);
                alloc_ptr_.store(ap, std::memory_order_release);
                ptr_.store(p, std::memory_order_release);
            }
        }

        return *p;
    }

    template <class... Ts>
    SROOK_FORCE_INLINE static 
    SROOK_DEDUCED_TYPENAME enable_if<is_allocator_construct_invocable<Ts&&...>::value, reference>::type
    instance(const allocator_type& alloc = allocator_type(), Ts&&... ts)
    {
        allocator_pointer_type ap = alloc_ptr_.load(std::memory_order_acquire);
        pointer p = ptr_.load(std::memory_order_acquire);

        if (!ap && !p) {
            lock_guard<mutex> lk(m_);
            ap = alloc_ptr_.load(std::memory_order_relaxed);
            p = ptr_.load(std::memory_order_relaxed);

            if (!ap && !p) {
                SROOK_TRY {
                    ap = new allocator_type(alloc);
                    p = traits_type::allocate(*ap, 1);
                } SROOK_CATCH (const std::bad_alloc& e) {
                    SROOK_THROW e;
                } SROOK_CATCH (...) {
                    SROOK_THROW;
                }

                p = construct(ap, p, srook::forward<Ts>(ts)...);
                alloc_ptr_.store(ap, std::memory_order_release);
                ptr_.store(p, std::memory_order_release);
            }
        }

        return *p;
    }
                

    SROOK_FORCE_INLINE static void destroy() 
    SROOK_NOEXCEPT(is_nothrow_destructible<value_type>::value)
    {
        // Deallocation of the instance and deallocation of the allocator are executed collectively in a single thread.
        // At the time of being deallocated of the instance, another thread will not attempt to deallocate of allocator's memory resources.

        pointer p = ptr_.load(std::memory_order_acquire);
        allocator_pointer_type ap = alloc_ptr_.load(std::memory_order_acquire);

        if (p && ap) { 
            lock_guard<mutex> lk(m_);
            p = ptr_.load(std::memory_order_relaxed);
            ap = alloc_ptr_.load(std::memory_order_relaxed);

            if (p && ap) {
                traits_type::destroy(*ap, p);
                traits_type::deallocate(*ap, p, 1);
                delete ap;
                
                ptr_.store(SROOK_NULLPTR, std::memory_order_release);
                alloc_ptr_.store(SROOK_NULLPTR, std::memory_order_release);
            }
        }
    }
#else // Data-Dependency Ordering version
    template <class... Ts>
    [[carries_dependency]] SROOK_FORCE_INLINE static 
    SROOK_DEDUCED_TYPENAME enable_if<construct_requires<Ts&&...>::value, reference>::type
    instance(Ts&&... ts)
    {
        allocator_pointer_type ap = alloc_ptr_.load(std::memory_order_consume);
        pointer p = ptr_.load(std::memory_order_consume);
        
        if (!ap && !p) {
            lock_guard<mutex> lk(m_);
            ap = alloc_ptr_.load(std::memory_order_relaxed);
            p = ptr_.load(std::memory_order_relaxed);

            if (!ap && !p) {
                SROOK_TRY {
                    ap = new allocator_type();
                    p = traits_type::allocate(*ap, 1);
                } SROOK_CATCH (const std::bad_alloc& e) {
                    SROOK_THROW e;
                } SROOK_CATCH (...) {
                    SROOK_THROW;
                }
                
                p = construct(ap, p, srook::forward<Ts>(ts)...);
                alloc_ptr_.store(ap, std::memory_order_release);
                ptr_.store(p, std::memory_order_release);
            }
        }

        return *p;
    }

    template <class... Ts>
    [[carries_dependency]] SROOK_FORCE_INLINE static 
    SROOK_DEDUCED_TYPENAME enable_if<is_allocator_construct_invocable<Ts&&...>::value, reference>::type
    instance(const allocator_type& alloc = allocator_type(), Ts&&... ts)
    {
        allocator_pointer_type ap = alloc_ptr_.load(std::memory_order_consume);
        pointer p = ptr_.load(std::memory_order_consume);

        if (!ap && !p) {
            lock_guard<mutex> lk(m_);
            ap = alloc_ptr_.load(std::memory_order_relaxed);
            p = ptr_.load(std::memory_order_relaxed);

            if (!ap && !p) {
                SROOK_TRY {
                    ap = new allocator_type(alloc);
                    p = traits_type::allocate(*ap, 1);
                } SROOK_CATCH (const std::bad_alloc& e) {
                    SROOK_THROW e;
                } SROOK_CATCH (...) {
                    SROOK_THROW;
                }

                p = construct(ap, p, srook::forward<Ts>(ts)...);
                alloc_ptr_.store(ap, std::memory_order_release);
                ptr_.store(p, std::memory_order_release);
            }
        }

        return *p;
    }
                

    [[carries_dependency]] SROOK_FORCE_INLINE static void destroy() 
    SROOK_NOEXCEPT((is_nothrow_destructible<value_type>::value))
    {
        pointer p = ptr_.load(std::memory_order_consume);
        allocator_pointer_type ap = ptr_.load(std::memory_order_consume);

        if (p && ap) {
            lock_guard<mutex> lk(m_);
            p = ptr_.load(std::memory_order_relaxed);
            ap = alloc_ptr_.load(std::memory_order_relaxed);

            if (p && ap) {
                traits_type::destroy(*ap, p);
                traits_type::deallocate(*ap, p, 1);
                delete ap;
                
                ptr_.store(SROOK_NULLPTR, std::memory_order_release);
                alloc_ptr_.store(SROOK_NULLPTR, std::memory_order_release);
            }
        }
    }
#endif
protected:
    singleton_adaptor_core() SROOK_DEFAULT

#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS17_CONSTANT && SROOK_CPP_INLINE_VARIABLES
    static SROOK_INLINE_VARIABLE std::atomic<pointer> ptr_ = SROOK_NULLPTR;
    static SROOK_INLINE_VARIABLE std::atomic<allocator_pointer_type> alloc_ptr_ = SROOK_NULLPTR;
    static SROOK_INLINE_VARIABLE mutex m_;
#else
    static std::atomic<pointer> ptr_;
    static std::atomic<allocator_pointer_type> alloc_ptr_;
    static mutex m_;
#endif
private:
    template <class... Ts>
    SROOK_FORCE_INLINE static SROOK_DEDUCED_TYPENAME
    enable_if<type_traits::detail::Land<is_allocator_construct_invocable<Ts&&...>, type_traits::detail::Lnot<is_pointer<pointer>>>::value, reference>::type
    construct(allocator_pointer_type ap, pointer p, Ts&&... ts) SROOK_NOEXCEPT((traits_type::construct(declval<allocator_pointer_type>(), declval<pointer>(), declval<Ts>()...)))
    {
        // NOTE:
        //  It is impossible to laund ptr_ by [basic.life] and allocator requirement.
        //  so if value_type has non-static const data member or non-static reference type member, it cause undefined behavior.
        //  See more detail: http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2017/p0532r0.pdf
        traits_type::construct(*ap, p, srook::forward<Ts>(ts)...);
        return p;
    }

    template <class... Ts>
    SROOK_FORCE_INLINE static SROOK_DEDUCED_TYPENAME
    enable_if<type_traits::detail::Land<is_allocator_construct_invocable<Ts&&...>, is_pointer<pointer>>::value, reference>::type
    construct(allocator_pointer_type ap, pointer p, Ts&&... ts) SROOK_NOEXCEPT((traits_type::construct(declval<allocator_pointer_type>(), declval<pointer>(), declval<Ts>()...)))
    {
        traits_type::construct(*ap, p, srook::forward<Ts>(ts)...);
        return srook::launder(p);
    }
};

#if SROOK_CPLUSPLUS < SROOK_CPLUSPLUS17_CONSTANT || !SROOK_CPP_INLINE_VARIABLES
template <class T, class Allocator>
std::atomic<SROOK_DEDUCED_TYPENAME singleton_adaptor_core<srook::memory::singleton<T, Allocator, srook::memory::singleton_policy::use_allocator_ctors>>::pointer> 
singleton_adaptor_core<srook::memory::singleton<T, Allocator, srook::memory::singleton_policy::use_allocator_ctors>>::ptr_ = SROOK_NULLPTR;
template <class T, class Allocator>
std::atomic<SROOK_DEDUCED_TYPENAME singleton_adaptor_core<srook::memory::singleton<T, Allocator, srook::memory::singleton_policy::use_allocator_ctors>>::allocator_pointer_type> 
singleton_adaptor_core<srook::memory::singleton<T, Allocator, srook::memory::singleton_policy::use_allocator_ctors>>::alloc_ptr_ = SROOK_NULLPTR;
template <class T, class Allocator>
mutex singleton_adaptor_core<srook::memory::singleton<T, Allocator, srook::memory::singleton_policy::use_allocator_ctors>>::m_;
#endif

} // namespace detail
SROOK_INLINE_NAMESPACE_END

template <class T, class Allocator, class Policy>
class singleton_adaptor<srook::memory::singleton<T, Allocator, Policy>> 
    : protected srook::threading::safe::detail::singleton_adaptor_core<srook::memory::singleton<T, Allocator, Policy>> {
    typedef detail::singleton_adaptor_core<srook::memory::singleton<T, Allocator, Policy>> base_type;
public:
    typedef base_type friend_type;
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
};

template <class T>
class singleton_adaptor<srook::memory::mayers_singleton<T>> : protected srook::memory::mayers_singleton<T> {
    typedef srook::memory::mayers_singleton<T> base_type;
public:
    typedef SROOK_DEDUCED_TYPENAME base_type::friend_type friend_type;
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
};

} // namespace safe
} // namespace thread
} // namespace srook

#endif
#endif

// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_THREAD_SAFE_CONTAINER_STACK_HPP
#define INCLUDED_SROOK_THREAD_SAFE_CONTAINER_STACK_HPP

#include <srook/config/cpp_predefined.hpp>
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
#    include <cassert>
#    include <deque>
#    include <functional>
#    include <srook/config.hpp>
#    include <srook/memory/uses_allocator.hpp>
#    include <srook/mutex.hpp>
#    include <srook/scope/unique_resource.hpp>
#    include <srook/thread/safe/container/config.hpp>
#    include <srook/type_traits.hpp>
#    include <srook/utility/enable_copy_move.hpp>

namespace srook {
namespace threading {
namespace safe {
SROOK_INLINE_NAMESPACE(v1)

template <class T, class Container = std::deque<T>, behavior = behavior::wait_pushed>
class stack;

namespace detail {

template <class T, class Container>
struct stack_impl {
    typedef SROOK_DEDUCED_TYPENAME Container::value_type value_type;
    typedef SROOK_DEDUCED_TYPENAME Container::reference reference;
    typedef SROOK_DEDUCED_TYPENAME Container::const_reference const_reference;
    typedef SROOK_DEDUCED_TYPENAME Container::size_type size_type;
    typedef Container container_type;

#    if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
#        define USES_ALLOC(X) SROOK_REQUIRES(uses_allocator<container_type, X>::value)
    template <class C = Container, SROOK_REQUIRES(is_default_constructible<C>::value)>
    stack_impl() : c() {}

    explicit stack_impl(const container_type& con) : c(con) {}
    explicit stack_impl(container_type&& con) : c(srook::move(con)) {}

    template <class Alloc, USES_ALLOC(Alloc)>
    explicit stack_impl(const Alloc& a) : c(a) {}

    template <class Alloc, USES_ALLOC(Alloc)>
    explicit stack_impl(const container_type& con, const Alloc& a) : c(con, a) {}

    template <class Alloc, USES_ALLOC(Alloc)>
    explicit stack_impl(container_type&& con, const Alloc& a) : c(srook::move(con), a) {}
#    else
    explicit stack_impl(const container_type& con = container_type()), c(con) {}
#    endif
protected:
    container_type c;
    mutex m_;

public:
    SROOK_FORCE_INLINE SROOK_CONSTEXPR bool empty()
    SROOK_MEMFN_NOEXCEPT(declval<container_type>().empty())
    {
        lock_guard<mutex> lk(m_);
        return c.empty();
    }

    SROOK_FORCE_INLINE SROOK_CONSTEXPR size_type size()
    SROOK_MEMFN_NOEXCEPT(declval<container_type>().size())
    {
        lock_guard<mutex> lk(m_);
        return c.size();
    }

    void push(const value_type& x)
    {
        lock_guard<mutex> lk(m_);
        c.push_back(x);
    }

#    if SROOK_CPP_RVALUE_REFERENCES
    void push(value_type&& x)
    {
        lock_guard<mutex> lk(m_);
        c.push_back(srook::move(x));
    }

    template <class... Args>
    auto emplace(Args&&... args)
    -> decltype(declval<container_type>().emplace_back(declval<Args>()...))
    {
        lock_guard<mutex> lk(m_);
        return c.emplace_back(srook::forward<Args>(args)...);
    }
#    endif

    void swap(stack_impl& other)
    {
        if (this == srook::addressof(other)) return;
        using std::swap;

        lock(m_, other.m_);
        scoped_lock<mutex, mutex> lk(adopt_lock, m_, other.m_);
        swap(c, other.c);
    }
};

} // namespace detail

template <class T, class Container, behavior>
class stack : public detail::stack_impl<T, Container> {
    typedef detail::stack_impl<T, Container> base_type;
    struct check_notifier_ : public enable_copy_move<true, true, true, true, check_notifier_> {
        check_notifier_(stack& st) : st_(st) {}
        SROOK_FORCE_INLINE void operator()(condition_variable& cv) const
        {
            if (!st_.c.empty()) cv.notify_all();
        }

    private:
        stack& st_;
    };
    struct notifier_ {
        SROOK_FORCE_INLINE void operator()(condition_variable& cv) const { cv.notify_all(); }
    };
    typedef unique_resource<condition_variable&, check_notifier_> scoped_check_notifier;
    typedef unique_resource<condition_variable&, notifier_> scoped_notifier;

public:
    typedef SROOK_DEDUCED_TYPENAME base_type::value_type value_type;
    typedef SROOK_DEDUCED_TYPENAME base_type::reference reference;
    typedef SROOK_DEDUCED_TYPENAME base_type::const_reference const_reference;
    typedef SROOK_DEDUCED_TYPENAME base_type::size_type size_type;
    typedef SROOK_DEDUCED_TYPENAME base_type::container_type container_type;

protected:
    srook::condition_variable cv_empty_check;
    bool is_aborted_
#    if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
        = false
#    endif
        ;
public:
#    if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT && SROOK_CPP_RVALUE_REFERENCES
    template <class C = container_type, SROOK_REQUIRES(is_default_constructible<C>::value)>
    stack()
        : base_type() {}
    explicit stack(const container_type& con)
        : base_type(con) {}
    explicit stack(container_type&& con)
        : base_type(srook::move(con)) {}
    template <class Alloc, USES_ALLOC(Alloc)>
    explicit stack(const Alloc& a)
        : base_type(a) {}
    template <class Alloc, USES_ALLOC(Alloc)>
    explicit stack(const container_type& con, const Alloc& a)
        : base_type(con, a) {}
    template <class Alloc, USES_ALLOC(Alloc)>
    explicit stack(container_type&& con, const Alloc& a)
        : base_type(srook::move(con), a) {}
    template <class Alloc, USES_ALLOC(Alloc)>
    explicit stack(const stack& s, const Alloc& a)
        : base_type(s.c, a) {}
    template <class Alloc, USES_ALLOC(Alloc)>
    explicit stack(stack&& s, const Alloc& a)
        : base_type(srook::move(s.c), a) {}
#    else
    explicit stack(const container_type& con = container_type())
        : base_type(con), is_aborted_(false) {}
#    endif

    void push(const value_type& x)
    {
        scoped_check_notifier n_(cv_empty_check, check_notifier_(*this));
        base_type::push(x);
    }

#    if SROOK_CPP_RVALUE_REFERENCES
    void push(value_type&& x)
    {
        scoped_check_notifier n_(cv_empty_check, check_notifier_(*this));
        base_type::push(srook::move(x));
    }

    template <class... Args>
    auto emplace(Args&&... args)
    -> decltype(declval<container_type>().emplace_back(declval<Args>()...))
    {
        scoped_check_notifier n_(cv_empty_check, check_notifier_(*this));
        return base_type::emplace(srook::forward<Args>(args)...);
    }
#    endif

    void abort()
    {
        scoped_notifier n_(cv_empty_check, notifier_());
        lock_guard<mutex> lk(this->m_);
        is_aborted_ = true;
    }

    reference top()
    {
        unique_lock<mutex> lk(this->m_);
        cv_empty_check.wait(lk, [this] { return !this->c.empty() || is_aborted_; });
        if (is_aborted_) throw aborted();
        return this->c.back();
    }

    const_reference top() const
    {
        unique_lock<mutex> lk(this->m_);
        cv_empty_check.wait(lk, [this] { return !this->c.empty() || is_aborted_; });
        if (is_aborted_) throw aborted();
        return this->c.back();
    }

    srook::libraries::optional<value_type> pop()
    {
        unique_lock<mutex> lk(this->m_);
        cv_empty_check.wait(lk, [this] { return !this->c.empty() || is_aborted_; });
        if (is_aborted_) throw aborted();

        const value_type result(this->c.back());
        this->c.pop_back();
        return srook::libraries::make_optional(result);
    }

    void swap(stack& other)
    SROOK_MEMFN_NOEXCEPT(is_nothrow_swappable<container_type>::value)
    {
        if (this == srook::addressof(other)) return;
        using std::swap;

		lock(this->m_, other.m_);
        scoped_lock<mutex, mutex> lk(adopt_lock, this->m_, other.m_);
        swap(this->c, other.c);
        swap(is_aborted_, other.is_aborted_);
    }
    template <class U, class C>
    friend SROOK_FORCE_INLINE bool operator==(const stack<U, C>&, const stack<U, C>&);
    template <class U, class C>
    friend SROOK_FORCE_INLINE bool operator<(const stack<U, C>&, const stack<U, C>&);
    template <class U, class C>
    friend SROOK_FORCE_INLINE bool operator!=(const stack<U, C>&, const stack<U, C>&);
    template <class U, class C>
    friend SROOK_FORCE_INLINE bool operator>(const stack<U, C>&, const stack<U, C>&);
    template <class U, class C>
    friend SROOK_FORCE_INLINE bool operator<=(const stack<U, C>&, const stack<U, C>&);
    template <class U, class C>
    friend SROOK_FORCE_INLINE bool operator>=(const stack<U, C>&, const stack<U, C>&);
};

template <class T, class Container>
struct stack<T, Container, behavior::no_wait_pushed> : public detail::stack_impl<T, Container> {
    typedef detail::stack_impl<T, Container> base_type;

public:
    typedef SROOK_DEDUCED_TYPENAME base_type::value_type value_type;
    typedef SROOK_DEDUCED_TYPENAME base_type::reference reference;
    typedef SROOK_DEDUCED_TYPENAME base_type::const_reference const_reference;
    typedef SROOK_DEDUCED_TYPENAME base_type::size_type size_type;
    typedef SROOK_DEDUCED_TYPENAME base_type::container_type container_type;

public:
#    if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT && SROOK_CPP_RVALUE_REFERENCES
    template <class C = container_type, SROOK_REQUIRES(is_default_constructible<C>::value)>
    stack()
        : base_type() {}
    explicit stack(const container_type& con)
        : base_type(con) {}
    explicit stack(container_type&& con)
        : base_type(srook::move(con)) {}
    template <class Alloc, USES_ALLOC(Alloc)>
    explicit stack(const Alloc& a)
        : base_type(a) {}
    template <class Alloc, USES_ALLOC(Alloc)>
    explicit stack(const container_type& con, const Alloc& a)
        : base_type(con, a) {}
    template <class Alloc, USES_ALLOC(Alloc)>
    explicit stack(container_type&& con, const Alloc& a)
        : base_type(srook::move(con), a) {}
    template <class Alloc, USES_ALLOC(Alloc)>
    explicit stack(const stack& s, const Alloc& a)
        : base_type(s.c, a) {}
    template <class Alloc, USES_ALLOC(Alloc)>
    explicit stack(stack&& s, const Alloc& a)
        : base_type(srook::move(s.c), a) {}
#        undef USES_ALLOC
#    else
    explicit stack(const container_type& con = container_type())
        : base_type(con) {}
#    endif

#    ifdef __glibcxx_check_nonempty
#        define CHECK_NONEMPTY() __glibcxx_check_nonempty()
#    else
#        define CHECK_NONEMPTY() assert(this->c.size())
#    endif
    SROOK_CONSTEXPR reference top()
    {
        lock_guard<mutex> lk(this->m_);
        CHECK_NONEMPTY();
        return this->c.back();
    }

    SROOK_CONSTEXPR const_reference top() const
    {
        lock_guard<mutex> lk(this->m_);
        CHECK_NONEMPTY();
        return this->c.back();
    }
    srook::libraries::optional<value_type> pop()
    {
        if (this->c.empty()) return srook::libraries::nullopt;

        lock_guard<mutex> lk(this->m_);
        CHECK_NONEMPTY();
        const value_type result(this->c.back());
        this->c.pop_back();
        return srook::libraries::make_optional(result);
    }
#    undef CHECK_NONEMPTY

    template <class U, class C>
    friend SROOK_FORCE_INLINE bool operator==(const stack<U, C>&, const stack<U, C>&);
    template <class U, class C>
    friend SROOK_FORCE_INLINE bool operator<(const stack<U, C>&, const stack<U, C>&);
    template <class U, class C>
    friend SROOK_FORCE_INLINE bool operator!=(const stack<U, C>&, const stack<U, C>&);
    template <class U, class C>
    friend SROOK_FORCE_INLINE bool operator>(const stack<U, C>&, const stack<U, C>&);
    template <class U, class C>
    friend SROOK_FORCE_INLINE bool operator<=(const stack<U, C>&, const stack<U, C>&);
    template <class U, class C>
    friend SROOK_FORCE_INLINE bool operator>=(const stack<U, C>&, const stack<U, C>&);
};

template <class U, class C>
SROOK_FORCE_INLINE bool operator==(const stack<U, C>& lhs, const stack<U, C>& rhs)
{
    lock(lhs.m_, rhs.m_);
    scoped_lock<mutex, mutex> lk(adopt_lock, lhs.m_, rhs.m_);
    return lhs.c == rhs.c;
}

template <class U, class C>
SROOK_FORCE_INLINE bool operator<(const stack<U, C>& lhs, const stack<U, C>& rhs)
{
    lock(lhs.m_, rhs.m_);
    scoped_lock<mutex, mutex> lk(adopt_lock, lhs.m_, rhs.m_);
    return lhs.c < rhs.c;
}

template <class U, class C>
SROOK_FORCE_INLINE bool operator!=(const stack<U, C>& lhs, const stack<U, C>& rhs)
{
    lock(lhs.m_, rhs.m_);
    scoped_lock<mutex, mutex> lk(adopt_lock, lhs.m_, rhs.m_);
    return !(lhs == rhs);
}

template <class U, class C>
SROOK_FORCE_INLINE bool operator>(const stack<U, C>& lhs, const stack<U, C>& rhs)
{
    lock(lhs.m_, rhs.m_);
    scoped_lock<mutex, mutex> lk(adopt_lock, lhs.m_, rhs.m_);
    return rhs < lhs;
}

template <class U, class C>
SROOK_FORCE_INLINE bool operator<=(const stack<U, C>& lhs, const stack<U, C>& rhs)
{
    lock(lhs.m_, rhs.m_);
    scoped_lock<mutex, mutex> lk(adopt_lock, lhs.m_, rhs.m_);
    return !(rhs < lhs);
}

template <class U, class C>
SROOK_FORCE_INLINE bool operator>=(const stack<U, C>& lhs, const stack<U, C>& rhs)
{
    lock(lhs.m_, rhs.m_);
    scoped_lock<mutex, mutex> lk(adopt_lock, lhs.m_, rhs.m_);
    return !(lhs < rhs);
}

template <class T, class Container>
inline SROOK_DEDUCED_TYPENAME enable_if<is_swappable<Container>::value>::type
swap(stack<T, Container>& lhs, stack<T, Container>& rhs)
SROOK_NOEXCEPT(lhs.swap(rhs))
{
    lhs.swap(rhs);
}

#    if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS17_CONSTANT
template <class Container>
stack(Container)->stack<SROOK_DEDUCED_TYPENAME Container::value_type, Container>;

template <class Container, class Alloc>
stack(Container, Alloc)->stack<SROOK_DEDUCED_TYPENAME Container::value_type, Container>;
#    endif

SROOK_INLINE_NAMESPACE_END
} // namespace safe
} // namespace threading

namespace thread_safe {
namespace container {

using threading::safe::stack;
using threading::safe::swap;

} // namespace container
} // namespace thread_safe

template <class T, class Container, class Alloc>
struct uses_allocator<thread_safe::container::stack<T, Container>, Alloc>
    : public uses_allocator<Container, Alloc>::type {};

} // namespace srook

#    if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
#        include <type_traits>

namespace std {

template <class T, class Container, class Alloc>
struct uses_allocator<srook::thread_safe::container::stack<T, Container>, Alloc>
    : public uses_allocator<Container, Alloc>::type {};

} // namespace std

#        endif
#    endif
#endif

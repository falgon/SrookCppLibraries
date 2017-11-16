// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_THREAD_SAFE_CONTAINER_STACK_HPP
#define INCLUDED_SROOK_THREAD_SAFE_CONTAINER_STACK_HPP

#include <deque>
#include <exception>
#include <cassert>
#include <srook/config/cpp_predefined.hpp>
#include <srook/config/feature.hpp>
#include <srook/config/libraries/optional.hpp>
#include <srook/config/require.hpp>
#include <srook/memory/uses_allocator.hpp>
#include <srook/mutex.hpp>
#include <srook/type_traits.hpp>

namespace srook {
namespace threading {
namespace safe {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <class T, class Container>
struct stack_impl {
    typedef SROOK_DEDUCED_TYPENAME Container::value_type value_type;
    typedef SROOK_DEDUCED_TYPENAME Container::reference reference;
    typedef SROOK_DEDUCED_TYPENAME Container::const_reference const_reference;
    typedef SROOK_DEDUCED_TYPENAME Container::size_type size_type;
    typedef Container container_type;

#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
#    define USES_ALLOC(X) SROOK_REQUIRES(uses_allocator<container_type, X>::value)
	template <class C = Container, SROOK_REQUIRES(is_default_constructible<C>::value)>
	stack_impl() : c_() {}

	explicit stack_impl(const container_type& c) : c_(c) {}
	explicit stack_impl(container_type&& c) : c_(srook::move(c)) {}
	
	template <class Alloc, USES_ALLOC(Alloc)>
	explicit stack_impl(const Alloc& a) : c_(a) {}

	template <class Alloc, USES_ALLOC(Alloc)>
	explicit stack_impl(const container_type& c, const Alloc& a) : c_(c, a) {}

	template <class Alloc, USES_ALLOC(Alloc)>
	explicit stack_impl(container_type&& c, const Alloc& a) : c_(srook::move(c), a) {}
#else
	explicit stack_impl(const container_type& c = container_type()), c_(c) {}
#endif
protected:
	container_type c_;
	srook::mutex m_;
public:
    SROOK_FORCE_INLINE SROOK_CONSTEXPR bool empty()
    const SROOK_MEMFN_NOEXCEPT(declval<container_type>().empty())
    {
        return c_.empty();
    }

    SROOK_FORCE_INLINE SROOK_CONSTEXPR size_type size()
    const SROOK_MEMFN_NOEXCEPT(declval<container_type>().size())
    {
        return c_.size();
    }

    void push(const value_type& x)
    {
        unique_lock<mutex> lk(m_);
        c_.push_back(x);
    }

#if SROOK_CPP_RVALUE_REFERENCES
    void push(value_type&& x)
    {
        unique_lock<mutex> lk(m_);
        c_.push_back(srook::move(x));
    }

    template <class... Args>
    auto emplace(Args&&... args)
    -> decltype(declval<container_type>().emplace_back(declval<Args>()...))
    {
        unique_lock<mutex> lk(m_);
        return c_.emplace_back(srook::forward<Args>(args)...);
    }
#endif
	
    void swap(stack_impl& other)
    {
        if (this == srook::addressof(other)) return;
        using std::swap;

        lock(m_, other.m_);
        lock_guard<mutex> l1(m_, adopt_lock);
        lock_guard<mutex> l2(other.m_, adopt_lock);
        swap(c_, other.c_);
    }
};

} // namespace detail

struct aborted : public std::exception {
    aborted() SROOK_DEFAULT
    virtual const char* what() const SROOK_NOEXCEPT_TRUE SROOK_OVERRIDE
    {
        return "srook::thread_safe::stack: Aborted";
    }
    virtual ~aborted() SROOK_NOEXCEPT_TRUE SROOK_DEFAULT
};

SROOK_STRONG_ENUM_BEGIN(behavior) {
    wait_pushed,
    no_wait_pushed
};
SROOK_STRONG_ENUM_EPILOG(perform)

template <class T, class Container = std::deque<T>, behavior = behavior::wait_pushed>
class stack : public detail::stack_impl<T, Container> {
	typedef detail::stack_impl<T, Container> base_type;
public:
    typedef SROOK_DEDUCED_TYPENAME base_type::value_type value_type;
    typedef SROOK_DEDUCED_TYPENAME base_type::reference reference;
    typedef SROOK_DEDUCED_TYPENAME base_type::const_reference const_reference;
    typedef SROOK_DEDUCED_TYPENAME base_type::size_type size_type;
    typedef SROOK_DEDUCED_TYPENAME base_type::container_type container_type;

protected:
    srook::condition_variable cv_empty_check;
    bool is_aborted_
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
        = false
#endif
        ;
public:
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT && SROOK_CPP_RVALUE_REFERENCES
    template <class C = container_type, SROOK_REQUIRES(is_default_constructible<C>::value)>
    stack()
        : base_type() {}
    explicit stack(const container_type& c)
        : base_type(c) {}
    explicit stack(container_type&& c)
		: base_type(srook::move(c)) {}
    template <class Alloc, USES_ALLOC(Alloc)>
    explicit stack(const Alloc& a)
		: base_type(a) {}
    template <class Alloc, USES_ALLOC(Alloc)>
    explicit stack(const container_type& c, const Alloc& a)
		: base_type(c, a) {}
    template <class Alloc, USES_ALLOC(Alloc)>
    explicit stack(container_type&& c, const Alloc& a)
        : base_type(srook::move(c), a) {}
    template <class Alloc, USES_ALLOC(Alloc)>
    explicit stack(const stack& s, const Alloc& a)
        : base_type(s.c_, a) {}
    template <class Alloc, USES_ALLOC(Alloc)>
    explicit stack(stack&& s, const Alloc& a)
        : base_type(srook::move(s.c_), a) {}
#else
    explicit stack(const container_type& c = container_type())
        : base_type(c), is_aborted_(false) {}
#endif

    void push(const value_type& x)
    {
        unique_lock<mutex> lk(this->m_);
        this->c_.push_back(x);
		cv_empty_check.notify_all();
    }

#if SROOK_CPP_RVALUE_REFERENCES
    void push(value_type&& x)
    {
        unique_lock<mutex> lk(this->m_);
        this->c_.push_back(srook::move(x));
        cv_empty_check.notify_all();
    }

    template <class... Args>
    auto emplace(Args&&... args)
    -> decltype(declval<container_type>().emplace_back(declval<Args>()...))
    {
        unique_lock<mutex> lk(this->m_);
        this->c_.emplace_back(srook::forward<Args>(args)...);
        cv_empty_check.notify_all();
    }
#endif

    void abort()
    {
        lock_guard<mutex> lk(this->m_);
        is_aborted_ = true;
        cv_empty_check.notify_all();
    }

    reference top()
    {
        unique_lock<mutex> lk(this->m_);
        cv_empty_check.wait(lk, [this] { return !this->empty() || is_aborted_; });
        if (is_aborted_) throw aborted();

        return this->c_.back();
    }

    const_reference top() const
    {
        unique_lock<mutex> lk(this->m_);
        cv_empty_check.wait(lk, [this] { return !this->empty() || is_aborted_; });
        if (is_aborted_) throw aborted();

        return this->c_.back();
    }

    srook::libraries::optional<value_type> pop()
    {
        unique_lock<mutex> lk(this->m_);
        cv_empty_check.wait(lk, [this] { return !this->empty() || is_aborted_; });
        if (is_aborted_) throw aborted();

        const value_type result(this->c_.front());
        this->c_.pop_back();
        return srook::libraries::make_optional(result);
    }
	
    void swap(stack& other)
    SROOK_MEMFN_NOEXCEPT(is_nothrow_swappable<container_type>::value)
    {
        if (this == srook::addressof(other)) return;
        using std::swap;

        lock(this->m_, other.m_);
        lock_guard<mutex> l1(this->m_, adopt_lock);
        lock_guard<mutex> l2(other.m_, adopt_lock);
        swap(this->c_, other.c_);
        swap(is_aborted_, other.is_aborted_);
    }
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
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT && SROOK_CPP_RVALUE_REFERENCES
    template <class C = container_type, SROOK_REQUIRES(is_default_constructible<C>::value)>
    stack()
        : base_type() {}
    explicit stack(const container_type& c)
        : base_type(c) {}
    explicit stack(container_type&& c)
		: base_type(srook::move(c)) {}
    template <class Alloc, USES_ALLOC(Alloc)>
    explicit stack(const Alloc& a)
		: base_type(a) {}
    template <class Alloc, USES_ALLOC(Alloc)>
    explicit stack(const container_type& c, const Alloc& a)
		: base_type(c, a) {}
    template <class Alloc, USES_ALLOC(Alloc)>
    explicit stack(container_type&& c, const Alloc& a)
        : base_type(srook::move(c), a) {}
    template <class Alloc, USES_ALLOC(Alloc)>
    explicit stack(const stack& s, const Alloc& a)
        : base_type(s.c_, a) {}
    template <class Alloc, USES_ALLOC(Alloc)>
    explicit stack(stack&& s, const Alloc& a)
        : base_type(srook::move(s.c_), a) {}
#    undef USES_ALLOC
#else
    explicit stack(const container_type& c = container_type())
        : base_type(c) {}
#endif

#ifdef __glibcxx_check_nonempty
#    define CHECK_NONEMPTY() __glibcxx_check_nonempty()
#else
#    define CHECK_NONEMPTY() assert(this->size())
#endif
    SROOK_CONSTEXPR reference top()
    {
        CHECK_NONEMPTY();
        return this->c_.back();
    }

    SROOK_CONSTEXPR const_reference top() const
    {
        CHECK_NONEMPTY();
        return this->c_.back();
    }
#undef CHECK_NONEMPTY
    srook::libraries::optional<value_type> pop()
    {
        if (this->empty()) return srook::libraries::nullopt;

        unique_lock<mutex> lk(this->m_);
        const value_type result(this->c_.front());
        this->c_.pop_back();
        return srook::libraries::make_optional(result);
    }
};

template <class T, class Container>
SROOK_FORCE_INLINE bool operator==(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
{
    return lhs.c_ == rhs.c_;
}

template <class T, class Container>
SROOK_FORCE_INLINE bool operator<(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
{
    return lhs.c_ < rhs.c_;
}

template <class T, class Container>
SROOK_FORCE_INLINE bool operator!=(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
{
    return !(lhs == rhs);
}

template <class T, class Container>
SROOK_FORCE_INLINE bool operator>(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
{
    return rhs < lhs;
}

template <class T, class Container>
SROOK_FORCE_INLINE bool operator<=(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
{
    return !(rhs < lhs);
}

template <class T, class Container>
SROOK_FORCE_INLINE bool operator>=(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
{
    return !(lhs < rhs);
}

template <class T, class Container>
inline SROOK_DEDUCED_TYPENAME enable_if<is_swappable<Container>::value>::type
swap(stack<T, Container>& lhs, stack<T, Container>& rhs)
SROOK_NOEXCEPT(lhs.swap(rhs))
{
    lhs.swap(rhs);
}

#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS17_CONSTANT
template <class Container>
stack(Container) -> stack<SROOK_DEDUCED_TYPENAME Container::value_type, Container>;

template <class Container, class Alloc>
stack(Container, Alloc) -> stack<SROOK_DEDUCED_TYPENAME Container::value_type, Container>;
#endif

SROOK_INLINE_NAMESPACE_END
} // namespace safe
} // namespace threading

namespace thread_safe {
namespace container {

using threading::safe::aborted;
using threading::safe::behavior;
using threading::safe::stack;
using threading::safe::swap;

} // namespace container
} // namespace thread_safe

template <class T, class Container, class Alloc>
struct uses_allocator<thread_safe::container::stack<T, Container>, Alloc>
    : public uses_allocator<Container, Alloc>::type {};

} // namespace srook

#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
#include <type_traits>

namespace std {

template <class T, class Container, class Alloc>
struct uses_allocator<srook::thread_safe::container::stack<T, Container>, Alloc>
    : public uses_allocator<Container, Alloc>::type {};

} // namespace std

#endif
#endif

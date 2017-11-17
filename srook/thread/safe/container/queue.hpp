// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_THREAD_SAFE_CONTAINER_QUEUE_HPP
#define INCLUDED_SROOK_THREAD_SAFE_CONTAINER_QUEUE_HPP

#include <srook/config/cpp_predefined.hpp>
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
#include <srook/thread/safe/container/stack.hpp>

namespace srook {
namespace threading {
namespace safe {
SROOK_INLINE_NAMESPACE(v1)

template <class T, class Container = std::deque<T>, behavior = behavior::wait_pushed>
class queue;

namespace detail {

template <class T, class Container>
struct queue_impl {
    typedef SROOK_DEDUCED_TYPENAME Container::value_type value_type;
    typedef SROOK_DEDUCED_TYPENAME Container::reference reference;
    typedef SROOK_DEDUCED_TYPENAME Container::const_reference const_reference;
    typedef SROOK_DEDUCED_TYPENAME Container::size_type size_type;
    typedef Container container_type;

#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
#    define USES_ALLOC(X) SROOK_REQUIRES(uses_allocator<container_type, X>::value)
	template <class C = Container, SROOK_REQUIRES(is_default_constructible<C>::value)>
	queue_impl() : c() {}

	explicit queue_impl(const container_type& con) : c(con) {}
	explicit queue_impl(container_type&& con) : c(srook::move(con)) {}
	
	template <class Alloc, USES_ALLOC(Alloc)>
	explicit queue_impl(const Alloc& a) : c(a) {}

	template <class Alloc, USES_ALLOC(Alloc)>
	explicit queue_impl(const container_type& con, const Alloc& a) : c(con, a) {}

	template <class Alloc, USES_ALLOC(Alloc)>
	explicit queue_impl(container_type&& con, const Alloc& a) : c(srook::move(con), a) {}
#else
	explicit queue_impl(const container_type& con = container_type()), c(con) {}
#endif
protected:
	container_type c;
	srook::mutex m_;
public:
    SROOK_FORCE_INLINE SROOK_CONSTEXPR bool empty()
    const SROOK_MEMFN_NOEXCEPT(declval<container_type>().empty())
    {
        return c.empty();
    }

    SROOK_FORCE_INLINE SROOK_CONSTEXPR size_type size()
    const SROOK_MEMFN_NOEXCEPT(declval<container_type>().size())
    {
        return c.size();
    }

    void push(const value_type& x)
    {
        unique_lock<mutex> lk(m_);
        c.push_back(x);
    }

#if SROOK_CPP_RVALUE_REFERENCES
    void push(value_type&& x)
    {
        unique_lock<mutex> lk(m_);
        c.push_back(srook::move(x));
    }

    template <class... Args>
    auto emplace(Args&&... args)
    -> decltype(declval<container_type>().emplace_back(declval<Args>()...))
    {
        unique_lock<mutex> lk(m_);
        return c.emplace_back(srook::forward<Args>(args)...);
    }
#endif
	
    void swap(queue_impl& other)
    {
        if (this == srook::addressof(other)) return;
        using std::swap;

        lock(m_, other.m_);
        lock_guard<mutex> l1(m_, adopt_lock), l2(other.m_, adopt_lock);
        swap(c, other.c);
    }
};

} // namespace detail

template <class T, class Container, behavior>
class queue : public detail::queue_impl<T, Container> {
	typedef detail::queue_impl<T, Container> base_type;
    struct check_notifier_ : public enable_copy_move<true, true, true, true, check_notifier_> {
        check_notifier_(queue& st) : st_(st) {}
        SROOK_FORCE_INLINE void operator()(condition_variable& cv) const { if(!st_.empty()) cv.notify_all(); }
    private:
        queue& st_;
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
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
        = false
#endif
        ;
public:
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT && SROOK_CPP_RVALUE_REFERENCES
    template <class C = container_type, SROOK_REQUIRES(is_default_constructible<C>::value)>
    queue()
        : base_type() {}
    explicit queue(const container_type& con)
        : base_type(con) {}
    explicit queue(container_type&& con)
		: base_type(srook::move(con)) {}
    template <class Alloc, USES_ALLOC(Alloc)>
    explicit queue(const Alloc& a)
		: base_type(a) {}
    template <class Alloc, USES_ALLOC(Alloc)>
    explicit queue(const container_type& con, const Alloc& a)
		: base_type(con, a) {}
    template <class Alloc, USES_ALLOC(Alloc)>
    explicit queue(container_type&& con, const Alloc& a)
        : base_type(srook::move(con), a) {}
    template <class Alloc, USES_ALLOC(Alloc)>
    explicit queue(const queue& s, const Alloc& a)
        : base_type(s.c, a) {}
    template <class Alloc, USES_ALLOC(Alloc)>
    explicit queue(queue&& s, const Alloc& a)
        : base_type(srook::move(s.c), a) {}
#else
    explicit queue(const container_type& con = container_type())
        : base_type(con), is_aborted_(false) {}
#endif

    void push(const value_type& x)
    {
        scoped_check_notifier n_(cv_empty_check, check_notifier_(*this));
        base_type::push(x);
    }

#if SROOK_CPP_RVALUE_REFERENCES
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
#endif

    void abort()
    {
        scoped_notifier n_(cv_empty_check, notifier_());
        lock_guard<mutex> lk(this->m_);
        is_aborted_ = true;
    }

    reference front()
    {
        unique_lock<mutex> lk(this->m_);
        cv_empty_check.wait(lk, [this] { return !this->empty() || is_aborted_; });
        if (is_aborted_) throw aborted();
        return this->c.front();
    }

    const_reference front() const
    {
        unique_lock<mutex> lk(this->m_);
        cv_empty_check.wait(lk, [this] { return !this->empty() || is_aborted_; });
        if (is_aborted_) throw aborted();
        return this->c.front();
    }

    reference back()
    {
        unique_lock<mutex> lk(this->m_);
        cv_empty_check.wait(lk, [this] { return !this->empty() || is_aborted_; });
        if (is_aborted_) throw aborted();
        return this->c.back();
    }

    const_reference back() const
    {
        unique_lock<mutex> lk(this->m_);
        cv_empty_check.wait(lk, [this] { return !this->empty() || is_aborted_; });
        if (is_aborted_) throw aborted();
        return this->c.back();
    }

    srook::libraries::optional<value_type> pop()
    {
        unique_lock<mutex> lk(this->m_);
        cv_empty_check.wait(lk, [this] { return !this->empty() || is_aborted_; });
        if (is_aborted_) throw aborted();

        const value_type result(this->c.front());
        this->c.pop_front();
        return srook::libraries::make_optional(result);
    }
	
    void swap(queue& other)
    SROOK_MEMFN_NOEXCEPT(is_nothrow_swappable<container_type>::value)
    {
        if (this == srook::addressof(other)) return;
        using std::swap;

        lock(this->m_, other.m_);
        lock_guard<mutex> l1(this->m_, adopt_lock), l2(other.m_, adopt_lock);
        swap(this->c, other.c);
        swap(is_aborted_, other.is_aborted_);
    }
};

template <class T, class Container>
struct queue<T, Container, behavior::no_wait_pushed> : public detail::queue_impl<T, Container> {
	typedef detail::queue_impl<T, Container> base_type;
public:
    typedef SROOK_DEDUCED_TYPENAME base_type::value_type value_type;
    typedef SROOK_DEDUCED_TYPENAME base_type::reference reference;
    typedef SROOK_DEDUCED_TYPENAME base_type::const_reference const_reference;
    typedef SROOK_DEDUCED_TYPENAME base_type::size_type size_type;
    typedef SROOK_DEDUCED_TYPENAME base_type::container_type container_type;

public:
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT && SROOK_CPP_RVALUE_REFERENCES
    template <class C = container_type, SROOK_REQUIRES(is_default_constructible<C>::value)>
    queue()
        : base_type() {}
    explicit queue(const container_type& c)
        : base_type(c) {}
    explicit queue(container_type&& c)
		: base_type(srook::move(c)) {}
    template <class Alloc, USES_ALLOC(Alloc)>
    explicit queue(const Alloc& a)
		: base_type(a) {}
    template <class Alloc, USES_ALLOC(Alloc)>
    explicit queue(const container_type& c, const Alloc& a)
		: base_type(c, a) {}
    template <class Alloc, USES_ALLOC(Alloc)>
    explicit queue(container_type&& c, const Alloc& a)
        : base_type(srook::move(c), a) {}
    template <class Alloc, USES_ALLOC(Alloc)>
    explicit queue(const queue& s, const Alloc& a)
        : base_type(s.c, a) {}
    template <class Alloc, USES_ALLOC(Alloc)>
    explicit queue(queue&& s, const Alloc& a)
        : base_type(srook::move(s.c), a) {}
#    undef USES_ALLOC
#else
    explicit queue(const container_type& c = container_type())
        : base_type(c) {}
#endif

#ifdef __glibcxx_check_nonempty
#    define CHECK_NONEMPTY() __glibcxx_check_nonempty()
#else
#    define CHECK_NONEMPTY() assert(this->size())
#endif
    SROOK_CONSTEXPR reference front()
    {
        CHECK_NONEMPTY();
        return this->c.front();
    }

    SROOK_CONSTEXPR const_reference front() const
    {
        CHECK_NONEMPTY();
        return this->c.front();
    }

    SROOK_CONSTEXPR reference back()
    {
        CHECK_NONEMPTY();
        return this->c.back();
    }

    SROOK_CONSTEXPR const_reference back() const
    {
        CHECK_NONEMPTY();
        return this->c.back();
    }

#undef CHECK_NONEMPTY
    srook::libraries::optional<value_type> pop()
    {
        if (this->empty()) return srook::libraries::nullopt;

        unique_lock<mutex> lk(this->m_);
        const value_type result(this->c.front());
        this->c.pop_front();
        return srook::libraries::make_optional(result);
    }
};

template <class T, class Container>
SROOK_FORCE_INLINE bool operator==(const queue<T, Container>& lhs, const queue<T, Container>& rhs)
{
    return lhs.c == rhs.c;
}

template <class T, class Container>
SROOK_FORCE_INLINE bool operator<(const queue<T, Container>& lhs, const queue<T, Container>& rhs)
{
    return lhs.c < rhs.c;
}

template <class T, class Container>
SROOK_FORCE_INLINE bool operator!=(const queue<T, Container>& lhs, const queue<T, Container>& rhs)
{
    return !(lhs == rhs);
}

template <class T, class Container>
SROOK_FORCE_INLINE bool operator>(const queue<T, Container>& lhs, const queue<T, Container>& rhs)
{
    return rhs < lhs;
}

template <class T, class Container>
SROOK_FORCE_INLINE bool operator<=(const queue<T, Container>& lhs, const queue<T, Container>& rhs)
{
    return !(rhs < lhs);
}

template <class T, class Container>
SROOK_FORCE_INLINE bool operator>=(const queue<T, Container>& lhs, const queue<T, Container>& rhs)
{
    return !(lhs < rhs);
}

template <class T, class Container>
inline SROOK_DEDUCED_TYPENAME enable_if<is_swappable<Container>::value>::type
swap(queue<T, Container>& lhs, queue<T, Container>& rhs)
SROOK_NOEXCEPT(lhs.swap(rhs))
{
    lhs.swap(rhs);
}

#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS17_CONSTANT
template <class Container>
queue(Container) -> queue<SROOK_DEDUCED_TYPENAME Container::value_type, Container>;

template <class Container, class Alloc>
queue(Container, Alloc) -> queue<SROOK_DEDUCED_TYPENAME Container::value_type, Container>;
#endif

SROOK_INLINE_NAMESPACE_END
} // namespace safe
} // namespace threading

namespace thread_safe {
namespace container {

using threading::safe::queue;
using threading::safe::swap;

} // namespace container
} // namespace thread_safe

template <class T, class Container, class Alloc>
struct uses_allocator<thread_safe::container::queue<T, Container>, Alloc>
    : public uses_allocator<Container, Alloc>::type {};

} // namespace srook

#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
#include <type_traits>

namespace std {

template <class T, class Container, class Alloc>
struct uses_allocator<srook::thread_safe::container::queue<T, Container>, Alloc>
    : public uses_allocator<Container, Alloc>::type {};

} // namespace std

#endif
#endif
#endif

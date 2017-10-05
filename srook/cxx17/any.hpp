// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_CXX17_ANY_HPP
#define INCLUDED_SROOK_CXX17_ANY_HPP
#include <memory>
#include <srook/config/require.hpp>
#include <srook/mpl/variadic_player.hpp>
#include <srook/type_traits/is_same_all.hpp>
#include <type_traits>
#if __has_include(<boost/type_index.hpp>)
#include <boost/type_index.hpp>
#define POSSIBLE_TO_INCLUDE_BOOST_TYPEINDEX
#endif

namespace srook {
namespace detail {
inline namespace v1 {

struct any {
    struct pre {
    };
    struct post {
    };

    explicit constexpr any() = default;

    template <class T, REQUIRES(!std::is_same<any, std::remove_reference_t<std::remove_cv_t<T>>>::value)>
    any(T &&t)
	: ptr_(std::make_unique<Erasure<T>>(std::forward<T>(t)))
    {
    }

    any(const any &other)
	: ptr_(other.ptr_->clone())
    {
    }

    any(any &&other)
	: ptr_(std::move(other.ptr_))
    {
    }

    any &operator=(const any &other)
    {
	ptr_.reset(other.ptr_->clone());
	return *this;
    }

    any &operator=(any &&other)
    {
	ptr_ = std::move(other.ptr_);
	return *this;
    }

    template <class T, REQUIRES(!std::is_same<any, std::remove_reference_t<std::remove_cv_t<T>>>::value)>
    inline bool operator==(const T &t) const
    {
	return get<std::remove_reference_t<T>>() == t;
    }
    template <class T, REQUIRES(!std::is_same<any, std::remove_reference_t<std::remove_cv_t<T>>>::value)>
    bool operator!=(const T &t) const
    {
	return !operator==(t);
    }

    template <class T>
    bool is_same(const any &other) const
    {
	return other.get<T>() == get<T>();
    }

    template <class T>
    bool is_not_same(const any &other) const
    {
	return !is_same<T>(other);
    }

    template <class T, REQUIRES(!std::is_same<any, std::remove_reference_t<std::remove_cv_t<T>>>::value)>
    any &operator=(T &&t)
    {
	ptr_.reset(new Erasure<std::remove_reference_t<T>>(std::forward<T>(t)));
	return *this;
    }

    template <class T, REQUIRES(!std::is_same<any, std::remove_reference_t<std::remove_cv_t<T>>>::value)>
    T &operator+=(T &&t)
    {
	get<std::remove_reference_t<std::remove_cv_t<T>>>() += t;
	return get<std::remove_reference_t<std::remove_cv_t<T>>>();
    }
    template <class T, REQUIRES(!std::is_same<any, std::remove_reference_t<std::remove_cv_t<T>>>::value)>
    T &operator-=(T &&t)
    {
	get<std::remove_reference_t<std::remove_cv_t<T>>>() -= t;
	return get<std::remove_reference_t<std::remove_cv_t<T>>>();
    }
    template <class T, REQUIRES(!std::is_same<any, std::remove_reference_t<std::remove_cv_t<T>>>::value)>
    T &operator*=(T &&t)
    {
	get<std::remove_reference_t<std::remove_cv_t<T>>>() *= t;
	return get<std::remove_reference_t<std::remove_cv_t<T>>>();
    }
    template <class T, REQUIRES(!std::is_same<any, std::remove_reference_t<std::remove_cv_t<T>>>::value)>
    T &operator/=(T &&t)
    {
	get<std::remove_reference_t<std::remove_cv_t<T>>>() /= t;
	return get<std::remove_reference_t<std::remove_cv_t<T>>>();
    }

    template <class T, class place = pre>
    T increment()
    {
	return increment_core<T, place>::apply(*this);
    }

    template <class T, class place = pre>
    T decrement()
    {
	return decrement_core<T, place>::apply(*this);
    }

    template <class T, REQUIRES(!std::is_same<any, std::remove_reference_t<std::remove_cv_t<T>>>::value)>
    T operator+(const T &t) const
    {
	return get<const std::remove_reference_t<T>>() + t;
    }

    template <class T, REQUIRES(!std::is_same<any, std::remove_reference_t<std::remove_cv_t<T>>>::value)>
    T operator-(const T &t) const
    {
	return get<const std::remove_reference_t<T>>() + t;
    }

    template <class T, REQUIRES(!std::is_same<any, std::remove_reference_t<std::remove_cv_t<T>>>::value)>
    T operator*(const T &t) const
    {
	return get<const std::remove_reference_t<T>>() * t;
    }

    template <class T, REQUIRES(!std::is_same<any, std::remove_reference_t<std::remove_cv_t<T>>>::value)>
    T operator/(const T &t) const
    {
	return get<const std::remove_reference_t<T>>() / t;
    }

    template <class T, REQUIRES(!std::is_same<any, std::remove_reference_t<std::remove_cv_t<T>>>::value)>
    bool operator<(const T &t) const
    {
	return get<const std::remove_reference_t<T>>() < t;
    }

    template <class T, REQUIRES(!std::is_same<any, std::remove_reference_t<std::remove_cv_t<T>>>::value)>
    bool operator>(const T &t) const
    {
	return !operator<(t);
    }

    template <class T, REQUIRES(!std::is_same<any, std::remove_reference_t<std::remove_cv_t<T>>>::value)>
    bool operator<=(const T &t) const
    {
	return get<const std::remove_reference_t<T>>() <= t;
    }

    template <class T, REQUIRES(!std::is_same<any, std::remove_reference_t<std::remove_cv_t<T>>>::value)>
    bool operator>=(const T &t) const
    {
	return !operator<=(t);
    }

    template <class... Ts, REQUIRES(!is_same_all<any, Ts...>::value)>
    std::remove_reference_t<srook::First_t<Ts...>> plus(Ts &&... args) const
    {
	return plus_core(
	    static_cast<
		const std::remove_reference_t<First_t<Ts...>>>(**static_cast<Erasure<std::remove_reference_t<First_t<Ts...>>> *>(ptr_.get())),
	    std::forward<Ts>(args)...);
    }

    template <class T>
    T plus(const any &other) const
    {
	return get<
		   std::remove_reference_t<std::remove_cv_t<T>>>() +
	       other.get<
		   std::remove_reference_t<std::remove_cv_t<T>>>();
    }

    template <class T>
    T minus(const any &other) const
    {
	return get<
		   std::remove_reference_t<std::remove_cv_t<T>>>() -
	       other.get<
		   std::remove_reference_t<std::remove_cv_t<T>>>();
    }

    template <class T>
    T multiply(const any &other) const
    {
	return get<
		   std::remove_reference_t<std::remove_cv_t<T>>>() *
	       other.get<
		   std::remove_reference_t<std::remove_cv_t<T>>>();
    }

    template <class T>
    T division(const any &other) const
    {
	return get<
		   std::remove_reference_t<std::remove_cv_t<T>>>() /
	       other.get<
		   std::remove_reference_t<std::remove_cv_t<T>>>();
    }

    template <class... Ts, REQUIRES(!is_same_all<any, Ts...>::value)>
    std::remove_reference_t<srook::First_t<Ts...>> minus(Ts &&... args) const
    {
	return minus_core(
	    static_cast<
		const std::remove_reference_t<First_t<Ts...>>>(**static_cast<Erasure<std::remove_reference_t<First_t<Ts...>>> *>(ptr_.get())),
	    std::forward<Ts>(args)...);
    }
    template <class... Ts, REQUIRES(!is_same_all<any, Ts...>::value)>
    std::remove_reference_t<srook::First_t<Ts...>> multiply(Ts &&... args) const
    {
	return multiply_core(
	    static_cast<
		const std::remove_reference_t<First_t<Ts...>>>(**static_cast<Erasure<std::remove_reference_t<First_t<Ts...>>> *>(ptr_.get())),
	    std::forward<Ts>(args)...);
    }
    template <class... Ts, REQUIRES(!is_same_all<any, Ts...>::value)>
    std::remove_reference_t<srook::First_t<Ts...>> division(Ts &&... args) const
    {
	return division_core(
	    static_cast<
		const std::remove_reference_t<First_t<Ts...>>>(**static_cast<Erasure<std::remove_reference_t<First_t<Ts...>>> *>(ptr_.get())),
	    std::forward<Ts>(args)...);
    }

    operator bool() const { return has_value(); }

    template <class T, REQUIRES(!std::is_same<std::remove_cv_t<std::remove_reference_t<T>>, any>::value)>
    operator T() const
    {
	return get<std::remove_cv_t<std::remove_reference_t<T>>>();
    }

    template <class T>
    T &get() const noexcept
    {
	return **static_cast<Erasure<T> *>(ptr_.get());
    }
    template <class T>
    T &get()
    {
	return **static_cast<Erasure<T> *>(ptr_.get());
    }

    void reset() { ptr_.release(); }
    bool has_value() const { return bool(ptr_); }
    void swap(any &other) { std::swap(ptr_, other.ptr_); }

    const std::type_info &type() const { return ptr_->type(); }
    const std::string pretty_name() const { return ptr_->pretty_name(); }

    template <class T>
    static T &get(const any &this_)
    {
	return this_.get<T>();
    }

private:
    struct Erasure_core {
	virtual Erasure_core *clone() const = 0;
	virtual const std::type_info &type() const = 0;
#ifdef POSSIBLE_TO_INCLUDE_BOOST_TYPEINDEX
	virtual const std::string pretty_name() const = 0;
#endif
	virtual ~Erasure_core() = default;
    };
    template <class T>
    struct Erasure final : Erasure_core {
	explicit constexpr Erasure(const T &t) : data_(t) {}

	Erasure_core *clone() const override { return new Erasure<T>(data_); }

	const std::type_info &type() const override { return typeid(T); }

#ifdef POSSIBLE_TO_INCLUDE_BOOST_TYPEINDEX
	const std::string pretty_name() const override
	{
	    return boost::typeindex::type_id<T>().pretty_name();
	}
#endif
	T &operator*() const noexcept
	{
	    return data_;
	}
	T &operator*() { return data_; }

    private:
	T data_;
    };

    template <class, class>
    struct increment_core;
    template <class T>
    struct increment_core<T, pre> {
	static T &apply(any &an) { return ++an.get<T>(); }
    };
    template <class T>
    struct increment_core<T, post> {
	static T apply(any &an) { return an.get<T>()++; }
    };
    template <class, class>
    struct decrement_core;
    template <class T>
    struct decrement_core<T, pre> {
	static T &apply(any &an) { return --an.get<T>(); }
    };
    template <class T>
    struct decrement_core<T, post> {
	static T apply(any &an) { return an.get<T>()--; }
    };

    template <class Tail>
    constexpr Tail &&plus_core(Tail &&tail) const
    {
	return std::forward<Tail>(tail);
    }
    template <class Tail>
    constexpr Tail &&minus_core(Tail &&tail) const
    {
	return std::forward<Tail>(tail);
    }
    template <class Tail>
    constexpr Tail &&multiply_core(Tail &&tail) const
    {
	return std::forward<Tail>(tail);
    }
    template <class Tail>
    constexpr Tail &&division_core(Tail &&tail) const
    {
	return std::forward<Tail>(tail);
    }
    template <class Head, class... Tail>
    constexpr Head &&plus_core(Head &&head, Tail &&... tail) const
    {
	return std::forward<Head>(head + plus_core(std::forward<Tail>(tail)...));
    }
    template <class Head, class... Tail>
    constexpr Head &&minus_core(Head &&head, Tail &&... tail) const
    {
	return std::forward<Head>(head - minus_core(std::forward<Tail>(tail)...));
    }
    template <class Head, class... Tail>
    constexpr Head &&multiply_core(Head &&head, Tail &&... tail) const
    {
	return std::forward<Head>(head * multiply_core(std::forward<Tail>(tail)...));
    }
    template <class Head, class... Tail>
    constexpr Head &&division_core(Head &&head, Tail &&... tail) const
    {
	return std::forward<Head>(head / division_core(std::forward<Tail>(tail)...));
    }

private:
    std::unique_ptr<Erasure_core> ptr_;
};

template <class T, REQUIRES(!std::is_same<std::remove_cv_t<std::remove_reference_t<T>>, any>::value)>
T operator+(const T &t, const detail::any &any_ob)
{
    return t + any_ob.get<std::remove_reference_t<std::remove_cv_t<T>>>();
}

template <class T, REQUIRES(!std::is_same<std::remove_cv_t<std::remove_reference_t<T>>, any>::value)>
T operator-(const T &t, const detail::any &any_ob)
{
    return t - any_ob.get<std::remove_reference_t<std::remove_cv_t<T>>>();
}

template <class T, REQUIRES(!std::is_same<std::remove_cv_t<std::remove_reference_t<T>>, any>::value)>
T operator*(const T &t, const detail::any &any_ob)
{
    return t * any_ob.get<std::remove_reference_t<std::remove_cv_t<T>>>();
}

template <class T, REQUIRES(!std::is_same<std::remove_cv_t<std::remove_reference_t<T>>, any>::value)>
T operator/(const T &t, const detail::any &any_ob)
{
    return t / any_ob.get<std::remove_reference_t<std::remove_cv_t<T>>>();
}

} // namespace v1
} // namespace detail

using detail::any;

} // namespace srook

#endif
#ifdef POSSIBLE_TO_INCLUDE_BOOST_TYPEINDEX
#undef POSSIBLE_TO_INCLUDE_BOOST_TYPEINDEX
#endif

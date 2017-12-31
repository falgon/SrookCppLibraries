// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_ANY_HPP
#define INCLUDED_SROOK_ANY_HPP

#if __has_include(<any>)
#include <any>
#define POSSIBLE_TO_INCLUDE_STD_ANY 2017
#elif __has_include(<boost/any.hpp>)
#include <boost/any.hpp>
#define POSSIBLE_TO_INCLUDE_BOOST_ANY 2007
#elif (__cplusplus == 201703L)
#include <srook/cxx17/any.hpp>
#else

// C++03 code
#include <srook/config/nullptr.hpp>
#include <srook/memory/unique_ptr.hpp>
#include <srook/type_traits/enable_disable_if.hpp>
#include <stdexcept>
#include <typeinfo>

#ifdef POSSIBLE_TO_INCLUDE_STD_MEMORY
#define UNIQUE_PTR std::unique_ptr
#elif defined(POSSIBLE_TO_INCLUDE_BOOST_UNIQUE_PTR)
#define UNIQUE_PTR boost::unique_ptr
#else
#define UNIQUE_PTR srook::unique_ptr
#endif

#ifdef POSSIBLE_TO_USE_STD_NULLPTR
#define NULLPTR nullptr
#define NULLPTR_T std::nullptr_t
#else
#define NULLPTR srook::nullptr
#define NULLPTR_T srook::nullptr_t
#endif

namespace srook {
namespace adl_firewall {

class any {
    struct erasure_base {
	virtual erasure_base *clone() const = 0;
	virtual bool bool_tester() const throw() = 0;
	virtual const std::type_info &type() const = 0;
	virtual ~erasure_base() throw() {}
    };
    template <class T>
    struct erasure : erasure_base {
	erasure(const T &data) : data_(data) {}

	erasure_base *clone() const { return new erasure<T>(data_); }
	bool bool_tester() const throw() { return static_cast<bool>(data_); }
	const std::type_info &type() const { return typeid(T); }

	T &get() { return data_; }
	T &get() const { return data_; }

    private:
	T data_;
    };

    class Mover {
	Mover(any &a) : a(a) {}

    public:
	static Mover instance(any &a) throw() { return Mover(a); }
	any &a;
    };

public:
    explicit any() throw() : data_(NULLPTR) {}

    template <class T>
    any(const T &value) : data_(new erasure<T>(value))
    {
    }

    template <class T>
    any &operator=(const T &value)
    {
	data_.reset(new erasure<T>(value));
	return *this;
    }

    any(const any &other) : data_(other.data_->clone()) {}

    any(Mover other) : data_(other.a.data_.release()) {} // simulating move constructor

    any &operator=(const any &other)
    {
	data_.reset(other.data_->clone());
	return *this;
    }

    any &operator=(Mover other) // simulating move assign
    {
	data_.reset(other.a.data_.release());
	return *this;
    }

    operator bool() const
    {
	return data_->bool_tester();
    }

    template <class T>
    static T &get(any &this_)
    {
	return static_cast<erasure<T> *>(this_.data_.get())->get();
    }

    template <class T>
    static T &get(const any &this_)
    {
	return static_cast<erasure<T> *>(this_.data_.get())->get();
    }

    static Mover move(any &a) { return Mover::instance(a); }

    void reset()
    {
	data_.release();
    }

    bool has_value() const throw()
    {
	return bool(data_);
    }

    void swap(any &other) throw()
    {
	std::swap(other.data_, data_);
    }

    template <class T>
    operator T()
    {
	return get<T>(*this);
    }

private:
    UNIQUE_PTR<erasure_base> data_;
};

template <class T>
T operator+(const T &value, const any &a)
{
    return value + adl_firewall::any::get<T>(a);
}
template <class T>
T operator+(const any &a, const T &value)
{
    return adl_firewall::any::get<T>(a) + value;
}
template <class T>
T &operator+=(T &value, const any &a)
{
    return value += adl_firewall::any::get<T>(a) + value;
}
template <class T>
T &operator+=(any &a, const T &value)
{
    return adl_firewall::any::get<T>(a) += value;
}

template <class T>
T operator-(const T &value, const any &a)
{
    return value + adl_firewall::any::get<T>(a);
}
template <class T>
T operator-(const any &a, const T &value)
{
    return adl_firewall::any::get<T>(a) - value;
}
template <class T>
T &operator-=(T &value, const any &a)
{
    return value -= adl_firewall::any::get<T>(a);
}
template <class T>
T &operator-=(any &a, const T &value)
{
    return adl_firewall::any::get<T>(a) -= value;
}

template <class T>
T operator*(const T &value, const any &a)
{
    return value * adl_firewall::any::get<T>(a);
}
template <class T>
T operator*(const any &a, const T &value)
{
    return adl_firewall::any::get<T>(a) * value;
}
template <class T>
T &operator*=(T &value, const any &a)
{
    return value *= adl_firewall::any::get<T>(a);
}
template <class T>
T &operator*=(any &a, const T &value)
{
    return adl_firewall::any::get<T>(a) *= value;
}

template <class T>
T operator/(const T &value, const any &a) throw(std::range_error)
{
    if (!adl_firewall::any::get<T>(a)) throw std::range_error("Divided by zero.");
    return value / adl_firewall::any::get<T>(a);
}
template <class T>
T operator/(const any &a, const T &value) throw(std::range_error)
{
    if (!value) throw std::range_error("Divided by zero.");
    return adl_firewall::any::get<T>(a) / value;
}
template <class T>
T &operator/=(T &value, const any &a) throw(std::range_error)
{
    if (!adl_firewall::any::get<T>(a)) throw std::range_error("Divided by zero.");
    return value / adl_firewall::any::get<T>(a);
}
template <class T>
T &operator/=(any &a, const T &value) throw(std::range_error)
{
    if (!value) throw std::range_error("Divided by zero.");
    return adl_firewall::any::get<T>(a) /= value;
}
} // namespace adl_firewall

using adl_firewall::any;

} // namespace srook

#undef UNIQUE_PTR
#endif
#endif

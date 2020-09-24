// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TYPE_TRAITS_IS_ALL_SAME_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_IS_ALL_SAME_HPP
#include <array>
#include <map>
#include <srook/algorithm/for_each.hpp>
#include <srook/config/attribute/deprecated.hpp>
#include <srook/config/require.hpp>
#include <srook/mpl/expression.hpp>
#include <srook/mpl/variadic_player.hpp>
#include <srook/type_traits/is_same_all.hpp>
#include <tuple>
#include <type_traits>

namespace srook {
namespace detail {
namespace adl_firewall_expression {
inline namespace v1 {

template <class T, std::size_t Size>
struct SROOK_DEPRECATED array_impl {
    explicit constexpr array_impl() = default;

    template <class... Ts>
    explicit constexpr array_impl(Ts&&... param) : data_{{std::forward<Ts>(param)...}}
    {
    }

    array_impl(const array_impl&) = default;
    array_impl(array_impl&&) = default;

    array_impl& operator=(const array_impl&) = default;
    array_impl& operator=(array_impl&&) = default;

    template <class L, class Operator, class R>
    array_impl(const Expression<L, Operator, R>& exp)
    {
        size_type i = 0;
        for (iterator iter = begin(); iter != end(); ++iter) *iter = exp[i++];
    }
    template <class L, class Operator, class R>
    array_impl& operator=(const Expression<L, Operator, R>& exp) noexcept
    {
        size_type i = 0;
        for (iterator iter = begin(); iter != end(); ++iter) *iter = exp[i++];
        return *this;
    }

    void* operator new(std::size_t) = delete;
    void operator delete(void*) = delete;

    using reference = typename std::array<T, Size>::reference;
    using const_reference = typename std::array<T, Size>::const_reference;
    using iterator = typename std::array<T, Size>::iterator;
    using const_iterator = typename std::array<T, Size>::const_iterator;
    using reverse_iterator = typename std::array<T, Size>::reverse_iterator;
    using const_reverse_iterator = typename std::array<T, Size>::const_reverse_iterator;
    using size_type = typename std::array<T, Size>::size_type;
    using difference_type = typename std::array<T, Size>::difference_type;
    using pointer = typename std::array<T, Size>::pointer;
    using const_pointer = typename std::array<T, Size>::const_pointer;
    using value_type = typename std::array<T, Size>::value_type;

    const_iterator begin() const { return data_.begin(); }
    const_iterator end() const { return data_.end(); }
    iterator begin() { return data_.begin(); }
    iterator end() { return data_.end(); }
    const_iterator cbegin() const { return data_.cbegin(); }
    const_iterator cend() const { return data_.cbegin(); }
    const_reverse_iterator rbegin() const { return data_.rbegin(); }
    const_reverse_iterator rend() const { return data_.rend(); }
    reverse_iterator rbegin() { return data_.rbegin(); }
    reverse_iterator rend() { return data_.rend(); }
    const_reverse_iterator crbegin() const { return data_.crbegin(); }
    const_reverse_iterator crend() const { return data_.crend(); }

    reference at(size_type n) { return data_.at(std::move(n)); }
    constexpr const_reference at(size_type n) const { return data_.at(std::move(n)); }

    reference operator[](size_type n) { return data_[std::move(n)]; }
    constexpr const_reference operator[](size_type n) const { return data_[std::move(n)]; }

    reference front() { return data_.front(); }
    constexpr const_reference front() const { return data_.front(); }

    reference back() { return data_.back(); }
    constexpr const_reference back() const { return data_.back(); }

    T* data() noexcept { return data_.data(); }
    const T* data() const noexcept { return data_.data(); }

    constexpr bool empty() noexcept { return data_.empty(); }
    constexpr bool empty() const noexcept { return data_.empty(); }

    constexpr size_type size() noexcept { return data_.size(); }
    constexpr size_type size() const noexcept { return data_.size(); }

    constexpr size_type max_size() noexcept { return data_.max_size(); }
    constexpr size_type max_size() const noexcept { return data_.max_size(); }

    void fill(const T& u) { data_.fill(u); }

    void swap(array_impl& other) noexcept(noexcept(std::swap(std::declval<T&>(), std::declval<T&>()))) { data_.swap(other); }

    operator std::array<T, Size>() { return data_; }

    template <class UniformRandomNumberGenerator>
    void random_shuffle(UniformRandomNumberGenerator&& g)
    {
        std::shuffle(begin(), end(), std::forward<UniformRandomNumberGenerator>(g));
    }

    template <class... Ts>
    auto assign(Ts&&... value) -> decltype(std::enable_if_t<(sizeof...(value) <= Size)>(), void())
    {
        srook::for_each(srook::make_counter(std::make_tuple(std::forward<Ts>(value)...)), [this](const T& v, std::size_t i) { this->data_[i] = v; });
    }

protected:
    std::array<T, Size> data_;
};

struct def {
};
struct sequence {
};

template <class, std::size_t, class = def>
struct array;

template <class T, std::size_t n>
struct array<T, n, def> : array_impl<T, n> {
    using array_impl<T, n>::array_impl;

    template <class... Ts>
    array(Ts&&... value) : array_impl<T, n>::array_impl(std::forward<Ts>(value)...)
    {
    }
};

template <class T, std::size_t n>
struct array<T, n, sequence> : array_impl<T, n> {
    explicit constexpr array() : array_impl<T, n>::array_impl(), start_(0), interval_(0, 0) {}

    explicit array(T start_value, const T& interval = static_cast<T>(1))
        : start_(std::move(start_value)), interval_(std::make_pair(std::move(interval), std::move(interval)))
    {
        for (auto& v : this->data_) {
            v = start_value;
            start_value += interval;
        }
    }

    void change_interval(const T start, const T value)
    {
        if (interval_.first == interval_.second == value) return;
        *this->begin() = start_ = std::move(start);
        change_interval(std::move(value));
    }

    void change_interval(const T value)
    {
        if (interval_.first == interval_.second == value) return;
        T tmp = start_;

        for (typename array_impl<T, n>::iterator iter = std::next(this->begin(), 1); iter != this->end(); ++iter) *iter = (tmp += value);

        interval_.first = value;
        interval_.second = std::move(value);
    }

    bool apply_interval()
    {
        if (interval_.first != interval_.second) {
            T tmp = start_;
            for (typename array_impl<T, n>::iterator iter = std::next(this->begin(), 1); iter != this->end(); ++iter) *iter = (tmp += interval_.second);
            interval_.first = interval_.second;
            return true;
        }
        return false;
    }

    T summation(std::size_t index = n) const
    {
        if (n < index) return 0;
        return (((2 * start_) + ((n - 1) * interval_.first)) * n) / 2;
    }

    const T& operator[](std::size_t index)
    {
        apply_interval();
        return this->data[std::move(index)];
    }

    const T& at(std::size_t index)
    {
        apply_interval();
        return this->at(std::move(index));
    }

    const T& interval() const { return interval_.second; }
    T& interval() { return interval_.second; }

    void assign() = delete;
    void fill() = delete;

private:
    T start_;
    std::pair<T, T> interval_;
};

} // namespace v1
} // namespace adl_firewall_expression
} // namespace detail

using detail::adl_firewall_expression::array;
using detail::adl_firewall_expression::def;
using detail::adl_firewall_expression::sequence;

} // namespace srook
#    undef remove_cv_t
#endif

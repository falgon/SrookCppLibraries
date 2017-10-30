// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_ALGORITHM_FOREACH_HPP
#define INCLUDED_SROOK_ALGORITHM_FOREACH_HPP
#include <algorithm>
#include <initializer_list>
#include <srook/config/require.hpp>
#include <srook/config/cpp_predefined.hpp>
#include <srook/iterator/range_iterator.hpp>
#include <srook/type_traits/has_iterator.hpp>
#include <srook/type_traits/is_callable.hpp>
#include <srook/type_traits/remove_reference.hpp>
#include <srook/type_traits/remove_cv.hpp>
#include <srook/type_traits/decay.hpp>
#include <srook/type_traits/enable_if.hpp>
#include <srook/utility/declval.hpp>
#include <srook/utility/forward.hpp>
#include <srook/utility/index_sequence.hpp>
#include <tuple>
#include <type_traits>

#define remove_ref_cv(x) \
    typename remove_reference<typename remove_cv_t<x>::type>::type

namespace srook {
inline namespace v1 {

template <
    class Iterator,
    class Functor,
    REQUIRES(
	!has_iterator<remove_ref_cv(Iterator)>::value and
	is_callable<remove_ref_cv(Functor)>::value)>
auto for_each(Iterator &&first, Iterator &&last, Functor &&functor) -> decltype(srook::forward<Iterator>(first))
{
    std::for_each(srook::forward<Iterator>(first), srook::forward<Iterator>(last), srook::forward<Functor>(functor));
    return srook::forward<Iterator>(first);
}

template <
    class Range,
    class Functor,
    REQUIRES(
	(has_iterator<remove_ref_cv(Range)>::value or is_range_iterator_v<remove_ref_cv(Range)>)and is_callable<remove_ref_cv(Functor)>::value)>
auto for_each(Range &&r, Functor &&functor) -> decltype(srook::forward<Range>(r))
{
    std::for_each(std::begin(r), std::end(r), srook::forward<Functor>(functor));
    return srook::forward<Range>(r);
}

#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS14_CONSTANT
#define INDEX_SEQUENCE(...) std::index_sequence<__VA_ARGS__>
#define MAKE_INDEX_SEQUENCE(x) std::make_index_sequence<x>
#else
#define INDEX_SEQUENCE(...) srook::index_sequence<__VA_ARGS__>
#define MAKE_INDEX_SEQUENCE(x) typename make_index_sequence_type<x>::type
#endif

namespace {

template <class Functor>
void tuple_for_eacher(Functor &&)
{
}
template <class Functor, class Head, class... Tail, REQUIRES(is_callable<remove_ref_cv(Functor)>::value)>
void tuple_for_eacher(Functor &&functor, Head &&head, Tail &&... tail)
{
    functor(srook::forward<Head>(head));
    tuple_for_eacher(srook::forward<Functor>(functor), srook::forward<Tail>(tail)...);
}

template <class... Ts, class Functor, std::size_t... I, REQUIRES(is_callable<remove_ref_cv(Functor)>::value)>
std::tuple<Ts...> &tuple_for_eacher(std::tuple<Ts...> &t, Functor &&functor, const INDEX_SEQUENCE(I...) &&)
{
    tuple_for_eacher(srook::forward<Functor>(functor), std::get<I>(t)...);
    return t;
}

template <class... Ts, class Functor, std::size_t... I, REQUIRES(is_callable<remove_ref_cv(Functor)>::value)>
const std::tuple<Ts...> &tuple_for_eacher(const std::tuple<Ts...> &t, Functor &&functor, const INDEX_SEQUENCE(I...) &&)
{
    tuple_for_eacher(srook::forward<Functor>(functor), std::get<I>(t)...);
    return t;
}

} // namespace

template <
    class Tuple,
    class Functor,
    REQUIRES(
	is_callable<remove_ref_cv(Functor)>::value and
	!std::is_const<Tuple>::value and
	(std::tuple_size<typename remove_reference<Tuple>::type>::value or !std::tuple_size<typename remove_reference<Tuple>::type>::value))>
auto for_each(Tuple &&t, Functor &&functor) noexcept(noexcept(tuple_for_eacher(declval<decltype(static_cast<Tuple &&>(t))>(), declval<decltype(static_cast<Functor &&>(functor))>(), declval<MAKE_INDEX_SEQUENCE(std::tuple_size<typename decay<Tuple>::type>::value)>())))
    -> decltype(tuple_for_eacher(srook::forward<Tuple>(t), srook::forward<Functor>(functor), MAKE_INDEX_SEQUENCE(std::tuple_size<typename decay<Tuple>::type>::value)()))
{
    return tuple_for_eacher(srook::forward<Tuple>(t), srook::forward<Functor>(functor), MAKE_INDEX_SEQUENCE(std::tuple_size<typename decay<Tuple>::type>::value)());
}

template <
    class... Ts,
    class Functor,
    REQUIRES(is_callable<remove_ref_cv(Functor)>::value)>
auto for_each(const std::tuple<Ts...> &t, Functor &&functor) noexcept(noexcept(tuple_for_eacher(t, declval<decltype(srook::forward<Functor>(functor))>(), declval<MAKE_INDEX_SEQUENCE(std::tuple_size<std::tuple<Ts...>>::value)>())))
    -> const std::tuple<Ts...> &
{
    return tuple_for_eacher(t, srook::forward<Functor>(functor), MAKE_INDEX_SEQUENCE(std::tuple_size<std::tuple<Ts...>>::value)());
}

namespace {

template <class Range>
struct lvalue_counter {
    explicit constexpr lvalue_counter(Range &r, std::size_t value)
	: r_(r), value_(std::move(value)) {}
    using reference_type = Range &;

protected:
    reference_type r_;
    std::size_t value_;
};
template <class Range>
struct rvalue_counter {
    explicit constexpr rvalue_counter(Range &&r, std::size_t value)
	: r_(std::move(r)), value_(std::move(value)) {}
    using reference_type = Range &&;

protected:
    reference_type r_;
    std::size_t value_;
};

template <class Range>
using select_ref = typename std::conditional<std::is_lvalue_reference<Range>::value, lvalue_counter<remove_ref_cv(Range)>, rvalue_counter<remove_ref_cv(Range)>>::type;

template <class Range>
struct counter : select_ref<Range> {
    using select_ref<Range>::select_ref;
    using iterator = remove_ref_cv(Range)::iterator;
    using const_iterator = remove_ref_cv(Range)::const_iterator;
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS14_CONSTANT
    const_iterator begin() const { return std::begin(this->r_); }
    const_iterator end() const { return std::end(this->r_); }
#endif
    iterator begin() { return std::begin(this->r_); }
    iterator end() { return std::end(this->r_); }
    const_iterator cbegin() const { return this->r_.cbegin(); }
    const_iterator cend() const { return this->r_.cend(); }

    std::size_t &get_counter() { return this->value_; }
    typename select_ref<Range>::reference_type operator*() { return static_cast<typename select_ref<Range>::reference_type>(this->r_); }
};

template <bool, class Tuple>
struct counter_tuple {
    explicit constexpr counter_tuple(Tuple &&t, std::size_t value)
	: t_(std::move(t)), value_(std::move(value)) {}

    Tuple &&operator*() { return std::move(t_); }
    std::size_t &get_counter() { return value_; }

    using reference_type = Tuple &&;

private:
    reference_type t_;
    std::size_t value_;
};

template <class Tuple>
struct counter_tuple<true, Tuple> {
    explicit constexpr counter_tuple(Tuple &t, std::size_t value)
	: t_(t), value_(std::move(value)) {}

    Tuple &operator*() { return t_; }
    std::size_t &get_counter() { return value_; }

    using reference_type = Tuple &;

private:
    reference_type t_;
    std::size_t value_;
};

template <class Iterator>
struct counter_iters {
    explicit constexpr counter_iters(Iterator first, Iterator last, std::size_t value)
	: first_(std::move(first)), last_(std::move(last)), value_(std::move(value)) {}

    using iterator = remove_ref_cv(Iterator);
    using const_iterator = const iterator;

    iterator begin() const { return first_; }
    iterator end() const { return last_; }
    iterator begin() { return first_; }
    iterator end() { return last_; }
    const_iterator cbegin() const { return first_; }
    const_iterator cend() const { return last_; }

    std::size_t &get_counter() { return value_; }

private:
    Iterator first_, last_;
    std::size_t value_;
};

template <class Functor>
void counting_for_eacher(std::size_t &, Functor &&)
{
}

template <class Functor, class Head, class... Tail, REQUIRES(is_callable<remove_ref_cv(Functor)>::value)>
void counting_for_eacher(std::size_t &counter, Functor &&functor_, Head &&head, Tail &&... tail)
{
    functor_(srook::forward<Head>(head), counter);
    counting_for_eacher(++counter, srook::forward<Functor>(functor_), srook::forward<Tail>(tail)...);
}

template <class Tuple, class Functor, std::size_t... I, REQUIRES(is_callable<remove_ref_cv(Functor)>::value)>
auto counting_for_eacher(Tuple &&t, std::size_t &counter, Functor &&functor, const INDEX_SEQUENCE(I...) &&) -> decltype(srook::forward<Tuple>(t))
{
    counting_for_eacher(counter, srook::forward<Functor>(functor), std::get<I>(t)...);
    return srook::forward<Tuple>(t);
}

} // namespace

#undef INDEX_SEQUENCE
#undef MAKE_INDEX_SEQUENCE

template <class T, std::size_t s>
constexpr auto make_counter(const std::array<T, s> &ar, std::size_t value = 0)
    -> counter<decltype(ar)>
{
    return counter<decltype(ar)>(ar, std::move(value));
}

template <class T, std::size_t s>
constexpr auto make_counter(std::array<T, s> &ar, std::size_t value = 0)
    -> counter<decltype(ar)>
{
    return counter<decltype(ar)>(ar, std::move(value));
}

template <class Tuple,REQUIRES(!has_iterator<remove_ref_cv(Tuple)>::value)>
constexpr auto make_counter(Tuple &&t, std::size_t value = 0)
    -> typename enable_if<!has_iterator<remove_ref_cv(Tuple)>::value or !is_range_iterator_v<remove_ref_cv(Tuple)>, typename counter_tuple<std::is_lvalue_reference<Tuple>::value, Tuple>::type>::type
{
    return counter_tuple<std::is_lvalue_reference<Tuple>::value, Tuple>(srook::forward<Tuple>(t), std::move(value));
}

template <class Range, REQUIRES(has_iterator<remove_ref_cv(Range)>::value or is_range_iterator_v<remove_ref_cv(Range)>)>
constexpr auto make_counter(Range &&r, std::size_t value = 0) -> counter<decltype(srook::forward<Range>(r))>
{
    return counter<decltype(srook::forward<Range>(r))>(srook::forward<Range>(r), std::move(value));
}

template <class T>
constexpr auto make_counter(const std::initializer_list<T> &init_list, std::size_t value = 0) -> counter<const std::initializer_list<T> &>
{
    return counter<const std::initializer_list<T> &>(init_list, std::move(value));
}

template <class Iterator, REQUIRES(not has_iterator<remove_ref_cv(Iterator)>::value)>
constexpr auto make_counter(Iterator &&first, Iterator &&last, std::size_t value = 0) -> counter_iters<remove_ref_cv(Iterator)>
{
    return counter_iters<Iterator>(srook::forward<Iterator>(first), srook::forward<Iterator>(last), std::move(value));
}

template <
    bool b,
    class Tuple,
    class Functor,
    REQUIRES(is_callable<remove_ref_cv(Functor)>::value)>
constexpr auto for_each(counter_tuple<b, Tuple> t, Functor &&functor) -> typename counter_tuple<b, Tuple>::reference_type
{
    return counting_for_eacher(srook::forward<Tuple>(*t), t.get_counter(), srook::forward<Functor>(functor), MAKE_INDEX_SEQUENCE(std::tuple_size<remove_ref_cv(Tuple)>::value)());
}

template <
    class Range,
    class Functor,
    REQUIRES(
	(has_iterator<remove_ref_cv(Range)>::value or is_range_iterator_v<remove_ref_cv(Range)>)and is_callable<remove_ref_cv(Functor)>::value)>
auto for_each(counter<Range> cr, Functor &&functor) -> typename counter<Range>::reference_type
{
    for (decltype(std::begin(cr)) iter = std::begin(cr); iter != std::end(cr); ++iter) {
	functor(*iter, cr.get_counter());
	++cr.get_counter();
    }
    return *cr;
}

template <
    class Iterator,
    class Functor,
    REQUIRES(!has_iterator<remove_ref_cv(Iterator)>::value and is_callable<remove_ref_cv(Functor)>::value)>
auto for_each(counter_iters<Iterator> cr, Functor &&functor) -> decltype(std::begin(cr))
{
    for (typename counter_iters<Iterator>::iterator iter = std::begin(cr); iter != std::end(cr); ++iter) {
	functor(*iter, cr.get_counter());
	++cr.get_counter();
    }
    return std::begin(cr);
}

template <
    class T,
    class Functor,
    REQUIRES(is_callable<remove_ref_cv(Functor)>::value)>
auto for_each(std::initializer_list<T> init_list, Functor &&functor) -> decltype(std::begin(init_list))
{
    return for_each(std::begin(init_list), std::end(init_list), srook::forward<Functor>(functor));
}

} // namespace v1
} // namespace srook

#undef remove_cv_t
#endif

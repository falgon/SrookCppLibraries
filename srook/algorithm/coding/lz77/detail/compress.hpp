// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_ALGORITHM_ENCODING_LZ77_DETAIL_COMPRESS_HPP
#define INCLUDED_SROOK_ALGORITHM_ENCODING_LZ77_DETAIL_COMPRESS_HPP

#include <srook/algorithm/encoding/lz77/config.hpp>

#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
#    include <algorithm>
#    include <iterator>
#    include <list>
#    include <map>
#    include <srook/optional.hpp>
#    include <srook/thread.hpp>
#    include <string>

#    include <iostream>
#    include <srook/iterator.hpp>

namespace srook {
namespace algorithm {
namespace encoding {
namespace lz77 {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <typename CharacterType, template <class, class> class Container = std::list>
class window {
public:
    typedef Container<CharacterType, std::allocator<CharacterType> > base_type;
    typedef SROOK_DEDUCED_TYPENAME base_type::value_type value_type;
    typedef SROOK_DEDUCED_TYPENAME base_type::size_type size_type;
    typedef SROOK_DEDUCED_TYPENAME base_type::iterator iterator;
    typedef SROOK_DEDUCED_TYPENAME base_type::const_iterator const_iterator;

    window(size_type x) : max_size(srook::move(x)) {}
    const_iterator begin() const { return data_.begin(); }
    const_iterator end() const { return data_.end(); }
    iterator begin() { return data_.begin(); }
    iterator end() { return data_.end(); }
    const_iterator cbegin() const { return begin(); }
    const_iterator cend() const { return end(); }
    size_type size() const { return data_.size(); }

    template <class... Ts>
    enable_if_t<type_traits::detail::Land<is_same<value_type, decay_t<Ts> >...>::value> emplace_back(Ts&&... ts)
    {
        if (accumulation_counter >= max_size) {
            data_.pop_front();
            data_.emplace_back(srook::forward<Ts>(ts)...);
        } else {
            data_.emplace_back(srook::forward<Ts>(ts)...);
            ++accumulation_counter;
        }
    }

    template <class T>
    enable_if_t<is_same<value_type, decay_t<T> >::value> push_back(T&& x)
    {
        emplace_back(srook::forward<T>(x));
    }

    void pop_front()
    {
        --accumulation_counter;
        data_.pop_front();
    }

    const value_type& front() const SROOK_NOEXCEPT_TRUE { return data_.front(); }
    const value_type& back() const SROOK_NOEXCEPT_TRUE { return data_.back(); }

private:
    base_type data_;
    std::size_t max_size;
    std::size_t accumulation_counter = 0;

    friend std::ostream& operator<<(std::ostream& os, const window& w)
    {
        std::copy(w.begin(), w.end(), make_ostream_joiner(os, " "));
        return os;
    }
};

template <class T>
using unique_ptr_default_delete =
#    ifdef POSSIBLE_TO_INCLUDE_STD_MEMORY
    std::unique_ptr<T>
#    elif defined(POSSIBLE_TO_INCLUDE_BOOST_UNIQUE_PTR)
    boost::unique_ptr<T>
#    else
    unique_ptr<T>
#    endif
    ;

#    ifdef POSSIBLE_TO_INCLUDE_STD_MEMORY
using std::make_unique
#    elif defined(POSSIBLE_TO_INCLUDE_BOOST_UNIQUE_PTR)
using boost::make_unique
#    else
using srook::make_unique
#    endif
    ;

template <class ForwardIterator1, class ForwartIterator2>
std::pair<ForwardIterator1, ForwardIterator1>
head_lcs(ForwardIterator1 first1, ForwardIterator1 last1, ForwartIterator2 first2, ForwartIterator2 last2)
{
    if (first1 == first2 && last1 == last2) return {first1, last1}; // same range

    std::vector<ForwardIterator1> memo;
    memo.reserve(std::distance(first1, last1));
    for (ForwardIterator1 f1 = first1; f1 != last1; ++f1) {
        if (*f1 == *first2) memo.emplace_back(f1);
    }
    if (!memo.size()) return {last1, last1}; // not found
    memo.shrink_to_fit();

    typedef SROOK_DEDUCED_TYPENAME std::iterator_traits<ForwardIterator1>::difference_type ForwardIterator1_diff;
    std::map<ForwardIterator1_diff, ForwardIterator1, std::greater<ForwardIterator1_diff> > m;
    for (const ForwardIterator1 x : memo) {
        ForwardIterator1 next = std::next(x, 1);
        for (ForwartIterator2 f2 = std::next(first2, 1); f2 != last2; ++f2, ++next) {
            if (*f2 != *next) break;
        }
        m.emplace(std::distance(x, next), x);
    }

    return {std::begin(m)->second, std::next(std::begin(m)->second, std::begin(m)->first)};
}

template <typename CharacterType>
//optional<unique_ptr_default_delete<CharacterType[]>>
std::basic_string<CharacterType>
compress(std::basic_string<CharacterType> t, std::size_t window_size, std::size_t lookahead_size)
{
    if (t.empty()) return {};
    if (t.size() < window_size) window_size = t.size();

    //  auto buffer = make_unique<CharacterType[]>(t.size());

    window<CharacterType> w(srook::move(window_size));
    typedef SROOK_DEDUCED_TYPENAME window<CharacterType>::base_type list;
    list text(std::make_move_iterator(std::begin(t)), std::make_move_iterator(std::end(t)));

    std::basic_string<CharacterType> test_code;

    while (!text.empty()) {
        lookahead_size = lookahead_size < text.size() ? lookahead_size : text.size();
        const std::pair<SROOK_DEDUCED_TYPENAME window<CharacterType>::iterator, SROOK_DEDUCED_TYPENAME window<CharacterType>::iterator> p = head_lcs(w.begin(), w.end(), text.begin(), std::next(text.begin(), lookahead_size));
        const SROOK_DEDUCED_TYPENAME std::iterator_traits<SROOK_DEDUCED_TYPENAME window<CharacterType>::iterator>::difference_type distance = std::distance(p.first, p.second);

        if ((p.first == w.end() && p.second == w.end()) || distance == 1) {
            w.emplace_back(text.front());
            test_code += w.back();
            text.pop_front();
        } else {
            test_code += "[" + std::to_string(distance + std::distance(p.second, w.end())) + "," + std::to_string(distance) + "]";
            std::copy(std::begin(text), std::next(std::begin(text), distance), std::back_inserter(w));
            text.erase(std::begin(text), std::next(std::begin(text), distance));
        }
    }
    return test_code;
}

template <typename CharacterType>
optional<std::basic_string<CharacterType>>
decompress(std::basic_string<CharacterType> t)
{
    typedef std::basic_string<CharacterType> string;
    typedef SROOK_DEDUCED_TYPENAME string::size_type size_type;
    typedef SROOK_DEDUCED_TYPENAME string::iterator iterator;
    typedef SROOK_DEDUCED_TYPENAME iterator::difference_type iterdiff_type;

    const size_type find_first_sep = t.find_first_of('[');
    if (find_first_sep == string::npos) return { t };
    const size_type find_first_delim = t.find_first_of(',', find_first_sep);
    if (find_first_delim == string::npos) return {};
    const size_type find_last_sep = t.find_first_of(']', find_first_delim);
    if (find_last_sep == string::npos) return {};

    string pre_position_str(std::next(std::begin(t), find_first_sep + 1), std::next(std::begin(t), find_first_delim));
    string continue_position_str(std::next(std::begin(t), find_first_delim + 1), std::next(std::begin(t), find_last_sep));
    const int pre_position = std::stoi(pre_position_str);
    const int continue_len = std::stoi(continue_position_str);

    string result;
    result.reserve(t.size());
    std::copy_n(std::begin(t), find_first_sep, std::back_inserter(result));
    
    iterator b = std::next(std::next(std::begin(t), find_first_sep), -pre_position);
    iterator l = std::next(b, continue_len);
    std::copy(b, l, std::back_inserter(result));
    iterator iter = std::next(l);

 //   for (; iter < t.end(); ) {
        const size_type first_sep = t.find_first_of('[', find_last_sep + 1);
        if (first_sep == string::npos) {
            std::copy(std::next(std::next(t.begin(), find_last_sep)), t.end(), std::back_inserter(result));
            return result;
        }
        const size_type first_delim = t.find_first_of(',', first_sep);
        if (first_delim == string::npos) return {};
        const size_type last_sep = t.find_first_of(']', first_delim);
        if (last_sep == string::npos) return {};

        std::copy_n(std::next(std::next(t.begin(), find_last_sep)), first_sep, std::back_inserter(result));

   /*     string pps(std::next(std::begin(t), first_sep + 1), std::next(std::begin(t), first_delim));
        string cps(std::next(std::begin(t), first_delim + 1), std::next(std::begin(t), last_sep));
        const int prep = std::stoi(srook::move(pps));
        const int contl = std::stoi(srook::move(cps));

        iterator b_ = std::next(std::next(std::end(result), -1), prep);
        iterator l_ = std::next(b_, contl);
        std::copy(b_, l_, std::back_inserter(result));
        std::advance(iter, first_sep + std::distance(b_, l_));*/
   // }
    
    return result;
}

} // namespace detail

SROOK_INLINE_NAMESPACE_END
} // namespace lz77
} // namespace encoding
} // namespace algorithm
} // namespace srook

#    endif
#endif

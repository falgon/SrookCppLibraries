// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_ALGORITHM_DETAIL_TEMPBUF_HPP
#define INCLUDED_SROOK_ALGORITHM_DETAIL_TEMPBUF_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/algorithm/detail/config.hpp>
#include <srook/limits/numeric_limits.hpp>
#include <srook/type_traits/has_trivial_constructor.hpp>
#include <srook/type_traits/iterator/is_forwarditerator.hpp>
#include <srook/memory/destroy.hpp>
#include <srook/utility/noncopyable.hpp>

SROOK_NESTED_NAMESPACE(srook, algorithm) {
SROOK_INLINE_NAMESPACE(v1)
namespace detail {

template <bool>
struct uninitialized_construct_buf_dispatcher {
    template <class Pointer, class ForwardIter>
    static void ucr(Pointer first, Pointer last, ForwardIter seed)
    {
        if (first == last) return;
        Pointer cur = first;
        SROOK_TRY {
            typedef std::allocator<SROOK_DEDUCED_TYPENAME std::iterator_traits<ForwardIter>::value_type> alloc_type;
            typedef std::allocator_traits<alloc_type> traits_type;
            alloc_type alloc;
            traits_type::construct(alloc, srook::addressof(*first), srook::move(*seed));
            Pointer prev = cur;
            ++cur;
            for (; cur != last; ++cur, ++prev) {
                traits_type::construct(srook::addressof(*cur), srook::move(*prev));
            }
            *seed = srook::move(*prev);
        } SROOK_CATCH (...) {
            srook::memory::destroy(first, cur);
            SROOK_THROW;
        }
    }
};
 
template <>
struct uninitialized_construct_buf_dispatcher<true> {
    template <class Pointer, class ForwardIter>
    static void ucr(Pointer, Pointer, ForwardIter) {}
};

template <class ForwardIter, class T>
class temporary_buffer : noncopyable<temporary_buffer<ForwardIter, T>> {
    SROOK_ST_ASSERT(is_forwarditerator<ForwardIter>::value);
#ifdef __GNU_LIBRARY__
    __glibcxx_class_requires(ForwardIterator, _ForwardIteratorConcept)
#endif
public:
    typedef T value_type;
    typedef value_type* pointer;
    typedef pointer iterator;
    typedef std::ptrdiff_t size_type;
protected:
    size_type original_len_;
    size_type len_;
    pointer buffer_;
public:
    SROOK_CONSTEXPR size_type size() const { return len_; }
    SROOK_CONSTEXPR size_type requested_size() const { return original_len_; }
    iterator begin() { return buffer_; }
    iterator end() { return buffer_ + len_; }

    temporary_buffer(ForwardIter first, ForwardIter last)
        : original_len_(srook::iterator::distance(first, last)),
        len_(0), buffer_(SROOK_NULLPTR)
    {
        SROOK_TRY {
            std::pair<pointer, size_type> p(get_temporary_buffer<value_type>(original_len_));
            buffer_ = p.first;
            len_ = p.second;
            if (buffer_) uninitialized_construct_buf(buffer_, buffer_ + len_, first);
        } SROOK_CATCH (...) {
            delete_temporary_buffer(buffer_);
            buffer_ = SROOK_NULLPTR;
            len_ = 0;
            SROOK_THROW;
        }
    }

    ~temporary_buffer() SROOK_NOEXCEPT_TRUE
    {
        srook::memory::destroy(buffer_, buffer_ + len_);
        delete_temporary_buffer(buffer_);
    }
private:
    template <class U>
    std::pair<U*, std::ptrdiff_t> get_temporary_buffer(std::ptrdiff_t len) SROOK_NOEXCEPT_TRUE
    {
        const std::ptrdiff_t max = srook::numeric_limits<std::ptrdiff_t>::max() / sizeof(U);
        if (len > max) len = max;
        while (len > 0) {
            U* ptr = static_cast<U*>(::operator new(len * sizeof(U), std::nothrow));
            if (ptr) return std::make_pair(ptr, len);
            len >>= 1;
        }
        return std::make_pair(static_cast<U*>(SROOK_NULLPTR), std::ptrdiff_t(0));
    }

    template <class U>
    SROOK_FORCE_INLINE void delete_temporary_buffer(U* p) SROOK_NOEXCEPT_TRUE
    {
        ::operator delete(p, std::nothrow);
    }

    template <class Pointer>
    SROOK_FORCE_INLINE void uninitialized_construct_buf(Pointer first, Pointer last, ForwardIter seed)
    {
        typedef SROOK_DEDUCED_TYPENAME std::iterator_traits<Pointer>::value_type value_type;
        uninitialized_construct_buf_dispatcher<srook::has_trivial_constructor<value_type>::value>::ucr(first, last, seed);
    }
};

} // namespace detail
SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(algorithm, srook)

#endif

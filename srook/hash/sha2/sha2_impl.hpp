// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_HASH_SHA_256_DETAIL_SHA2_IMPL_HPP
#define INCLUDED_SROOK_HASH_SHA_256_DETAIL_SHA2_IMPL_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/hash/sha2/detail/sha2_traits.hpp>
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
#include <srook/hash/sha2/detail/is_callable_begin_end.hpp>
#include <srook/cxx20/concepts/iterator/InputIterator.hpp>
#include <srook/algorithm/min.hpp>
#include <srook/algorithm/rotate.hpp>
#include <srook/algorithm/copy.hpp>
#include <srook/algorithm/fill.hpp>
#include <srook/algorithm/transform.hpp>
#include <srook/type_traits/detail/sfinae_types.hpp>
#include <srook/iterator/range_access.hpp>
#include <srook/mutex.hpp>
#include <atomic>
#include <memory>
#include <iterator>
#include <sstream>

#if 0 && !defined(SROOK_CONFIG_ENABLE_PMR_PRIORITY)
#   include <memory_resource>
#elif !defined(SROOK_HAS_EXPERIMENTAL_STD_STRING) && !defined(SROOK_CONFIG_ENABLE_PMR_PRIORITY)
#   if SROOK_HAS_INCLUDE(<experimental/string>) // for pmr::string
#       include <experimental/string>
#       define SROOK_HAS_EXPERIMENTAL_STD_STRING 1
#   endif
#elif !defined(SROOK_HAS_BOOST_CONTAINER_PMR_STRING_HPP) && !defined(SROOK_CONFIG_ENABLE_PMR_PRIORITY)
#   if SROOK_HAS_INCLUDE(<boost/container/pmr/string.hpp>)
#       include <boost/container/pmr/string.hpp>
#       define SROOK_HAS_BOOST_CONTAINER_PMR_STRING_HPP 1
#   endif
#else
#   define SROOK_CONFIG_PMR_STD_BASIC_STRING_INCLUDE 1
#   include <srook/memory_resource/polymorphic_allocator.hpp>
#   include <srook/memory_resource/pmrlib.hpp>
#   include <srook/memory_resource/global_memory_resources.hpp>
#endif

SROOK_NESTED_NAMESPACE(srook, hash) {
SROOK_INLINE_NAMESPACE(v1)

#if SROOK_HAS_CONCEPTS
template <std::size_t B1, std::size_t B2 = 0, srook::concepts::InputIterator InputIter = std::string::const_iterator>
#else
template <std::size_t B1, std::size_t B2 = 0, class InputIter = std::string::const_iterator>
#endif
class sha2 {
    SROOK_STATIC_ASSERT(CHAR_BIT == 8, 
            "CHAR_BIT must be 8 bits in order to use the shaX hashing algorithm.\n"
            "See also: FIPS PUB 180-4 Secure Hash Standard Section 2.1 Glossary of Terms and Acronyms");
public:
    struct to_character {};
    typedef sha2_traits<B1, B2> traits_type;
    typedef SROOK_DEDUCED_TYPENAME traits_type::value_type integer_type;
    typedef srook::uint8_t value_type;
    static SROOK_CONSTEXPR std::size_t message_digest_size = traits_type::message_digest_size;
private:
    typedef srook::array<value_type, message_digest_size> internal_container_type;
public:
    SROOK_CONSTEXPR sha2(InputIter first, InputIter last)
        : message_(first), 
        len_(std::distance(message_, last)),
        digest_(),
        s_{ SROOK_NULLPTR }
    {
        context ctx_{ 0, 0, {}, traits_type::init_hash };
        sha2_update(ctx_);
        sha2_fin(ctx_);
    }

    template <class SinglePassRange, SROOK_REQUIRES(detail::is_callable_begin_end<SinglePassRange>::value)>
    SROOK_CONSTEXPR explicit sha2(const SinglePassRange& range)
        : sha2(srook::begin(range), srook::end(range)) {}

    SROOK_FORCE_INLINE SROOK_CXX14_CONSTEXPR sha2& assign(InputIter first, InputIter last)
    {
        destroy_str();
        srook::lock_guard<srook::mutex> lk(m_);
        
        message_ = first;
        len_ = std::distance(message_, last);

        context ctx_{ 0, 0, {}, traits_type::init_hash };
        sha2_update(ctx_);
        sha2_fin(ctx_);

        return *this;
    }

    template <class SinglePassRange>
    SROOK_FORCE_INLINE SROOK_CXX14_CONSTEXPR SROOK_DEDUCED_TYPENAME enable_if<detail::is_callable_begin_end<SinglePassRange>::value, sha2&>::type
    assign(const SinglePassRange& range)
    {
        return assign(range.cbegin(), range.cend());
    }

    SROOK_FORCE_INLINE SROOK_CXX14_CONSTEXPR srook::array<value_type, traits_type::message_digest_size>&
    operator()() 
    { 
        return digest_; 
    }
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS14_CONSTANT
    SROOK_FORCE_INLINE SROOK_CXX14_CONSTEXPR const srook::array<value_type, traits_type::message_digest_size>&
    operator()() const 
    { 
        return digest_; 
    }
#endif
    template <class Container>
    SROOK_FORCE_INLINE SROOK_CXX14_CONSTEXPR Container&
    operator()(Container& c) const
    {
        assert(c.size() >= message_digest_size);
        srook::algorithm::copy(cbegin(), cend(), c.begin());
        return c;
    }

    template <class Container>
    SROOK_FORCE_INLINE SROOK_CXX14_CONSTEXPR Container&
    operator()(Container& c, to_character)
    {
        std::string s(str());
        c.clear();
        c.reserve(s.size());
        srook::algorithm::copy(s, std::back_inserter(c));
        return c;
    }

    SROOK_FORCE_INLINE SROOK_CONSTEXPR
    SROOK_DEDUCED_TYPENAME internal_container_type::iterator 
    begin() SROOK_NOEXCEPT(digest_.begin())
    {
        return digest_.begin();
    }

    SROOK_FORCE_INLINE SROOK_CONSTEXPR SROOK_DEDUCED_TYPENAME internal_container_type::iterator 
    end() SROOK_NOEXCEPT(digest_.end())
    {
        return digest_.end();
    }
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS14_CONSTANT
    SROOK_FORCE_INLINE SROOK_CONSTEXPR SROOK_DEDUCED_TYPENAME internal_container_type::const_iterator 
    begin() const SROOK_NOEXCEPT(digest_.begin())
    {
        return digest_.cbegin();
    }
    SROOK_FORCE_INLINE SROOK_CONSTEXPR SROOK_DEDUCED_TYPENAME internal_container_type::const_iterator 
    end() const SROOK_NOEXCEPT(digest_.end())
    {
        return digest_.cend();
    }
#endif

    SROOK_FORCE_INLINE SROOK_CONSTEXPR SROOK_DEDUCED_TYPENAME internal_container_type::const_iterator
    cbegin() const SROOK_NOEXCEPT(digest_.cbegin())
    {
        return digest_.cbegin();
    }

    SROOK_FORCE_INLINE SROOK_CONSTEXPR SROOK_DEDUCED_TYPENAME internal_container_type::const_iterator
    cend() const SROOK_NOEXCEPT(digest_.cend())
    {
        return digest_.cend();
    }

    SROOK_FORCE_INLINE SROOK_CONSTEXPR SROOK_DEDUCED_TYPENAME internal_container_type::size_type
    size() const SROOK_NOEXCEPT_TRUE
    {
        return message_digest_size;
    }

    SROOK_FORCE_INLINE SROOK_CONSTEXPR bool
    empty() const SROOK_NOEXCEPT_TRUE
    {
        return digest_.empty();
    }

    SROOK_FORCE_INLINE SROOK_CONSTEXPR SROOK_DEDUCED_TYPENAME internal_container_type::pointer 
    data() const SROOK_NOEXCEPT_TRUE
    {
        return digest_.data();
    }

    SROOK_FORCE_INLINE std::string 
    str() const { return do_str(); }

#if 0 && SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS17_CONSTANT // not yet implemented various vendors.
    SROOK_FORCE_INLINE SROOK_CONSTEXPR std::pmr::string
    pmr_str(const std::pmr::polymorphic_allocator<std::pmr::string::value_type>& pa = std::pmr::get_default_resource()) const
    {
        const std::string rs(do_str());
        return { srook::begin(rs), srook::end(rs), pa };
    }
    SROOK_FORCE_INLINE SROOK_CONSTEXPR std::pmr::string
    pmr_str(const std::pmr::memory_resoure* resource = std::get_default_resource()) const
    {
        const std::string rs(do_str());
        return { srook::begin(rs), srook::end(rs), std::pmr::polymorphic_allocator<std::pmr::string::value_type>{ resource } };
    }
#   define SROOK_SHA_VALID_STD_PMR_STR 1
#elif defined(SROOK_HAS_EXPERIMENTAL_STD_STRING) && !defined(__GNUC__)
    SROOK_FORCE_INLINE std::experimental::pmr::string
    pmr_str(const std::experimental::pmr::polymorphic_allocator<std::experimental::pmr::string::value_type>& pa = std::experimental::pmr::get_default_resource()) const
    {
        const std::string rs(do_str());
        return { srook::begin(rs), srook::end(rs), pa };
    }
    SROOK_FORCE_INLINE std::experimental::pmr::string
    pmr_str(std::experimental::pmr::memory_resource* resource = std::experimental::pmr::get_default_resource()) const
    {
        const std::string rs(do_str());
        return { srook::begin(rs), srook::end(rs), std::experimental::pmr::polymorphic_allocator<std::experimental::pmr::string::value_type>{ resource } };
    }
#   define SROOK_SHA_VALID_STD_EXPERIMENTAL_PMR_STR 1
#elif defined(SROOK_HAS_BOOST_CONTAINER_PMR_STRING_HPP)
    SROOK_FORCE_INLINE boost::container::pmr::string
    pmr_str(const boost::container::pmr::polymorphic_allocator<boost::container::pmr::string::value_type>& pa = boost::container::pmr::get_default_resource()) const
    {
        const std::string rs(do_str());
        return { srook::begin(rs), srook::end(rs), pa };
    }
    SROOK_FORCE_INLINE boost::container::pmr::string
    pmr_str(boost::container::pmr::memory_resource* resource = boost::container::pmr::get_default_resource()) const
    {
        const std::string rs(do_str());
        return { srook::begin(rs), srook::end(rs), boost::container::pmr::polymorphic_allocator<boost::container::pmr::string::value_type>{ resource } };
    }
#   define SROOK_SHA_VALID_BOOST_PMR_STR 1
#elif defined(SROOK_CONFIG_ENABLE_PMR_PRIORITY)
    SROOK_FORCE_INLINE srook::pmr::string
    pmr_str(const srook::pmr::polymorphic_allocator<srook::pmr::string::value_type>& pa = srook::pmr::get_default_resource()) const
    {
        const std::string rs(do_str());
        return { srook::begin(rs), srook::end(rs), pa };
    }
    SROOK_FORCE_INLINE srook::pmr::string
    pmr_str(srook::pmr::memory_resource* resource = srook::pmr::get_default_resource()) const
    {
        const std::string rs(do_str());
        return { srook::begin(rs), srook::end(rs),srook::pmr::polymorphic_allocator<srook::pmr::string::value_type>{ resource } };
    }
#   define SROOK_SHA_VALID_SROOK_PMR_STR 1
#endif
    ~sha2()
    {
        destroy_str();
    }
private:
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS17_CONSTANT
    // The class sha is non-copy able so it is not neccesary reference counts.
    void destroy_str()
    {
        std::string* s = s_.load(std::memory_order_acquire);
        if (s) {
            srook::lock_guard<srook::mutex> lk_(m_);
            s = s_.load(std::memory_order_relaxed);
            if (s) {
                delete s;
                s_.store(SROOK_NULLPTR, std::memory_order_release);
            }
        }
    }
#else
    void destroy_str()
    {
        std::string* s = s_.load(std::memory_order_consume);
        if (s) {
            srook::lock_guard<srook::mutex> lk_(m_);
            s = s_.load(std::memory_order_relaxed);
            if (s) {
                delete s;
                s_.store(SROOK_NULLPTR, std::memory_order_release);
            }
        }
    }
#endif

#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS17_CONSTANT
    SROOK_FORCE_INLINE std::string do_str() const
    {
        std::string* s = s_.load(std::memory_order_acquire);
        if (!s) {
            srook::lock_guard<srook::mutex> lk_(m_);
            s = s_.load(std::memory_order_relaxed);
            if (!s) {
                std::ostringstream oss;
                oss.setf(std::ios::hex, std::ios::basefield);
                srook::algorithm::transform(digest_, std::ostream_iterator<integer_type>(oss), 
                        [&oss](const SROOK_DEDUCED_TYPENAME internal_container_type::value_type& e) -> integer_type { oss.width(2); oss.fill('0'); return static_cast<integer_type>(e); });
                oss.setf(std::ios::dec, std::ios::basefield);
                s = new std::string(oss.str());
                s_.store(s, std::memory_order_release);
            }
        }
        return *s;
    }
#else
    [[carries_dependency]] SROOK_FORCE_INLINE std::string do_str() const
    {
        std::string* s = s_.load(std::memory_order_consume);
        if (!s) {
            srook::lock_guard<srook::mutex> lk_(m_);
            s = s_.load(std::memory_order_relaxed);
            if (!s) {
                std::ostringstream oss;
                oss.setf(std::ios::hex, std::ios::basefield);
                srook::algorithm::transform(digest_, std::ostream_iterator<integer_type>(oss),
                        [&oss](const SROOK_DEDUCED_TYPENAME internal_container_type::value_type& e) -> integer_type { oss.width(2); oss.fill('0'); return static_cast<integer_type>(e); });
                oss.setf(std::ios::dec, std::ios::basefield);
                s = new std::string(oss.str());
                s_.store(s, std::memory_order_release);
            }
        }
        return *s;
    }
#endif

    struct context;

    SROOK_CXX14_CONSTEXPR void sha2_update(context& ctx_)
    {
        const std::size_t t = traits_type::block_size - len_;
        std::size_t rem_len = srook::algorithm::min(len_, t);
        srook::algorithm::copy(message_, std::next(message_, rem_len), std::next(srook::begin(ctx_.block), ctx_.len));
        if (ctx_.len + len_ < traits_type::block_size) {
            ctx_.len += len_;
            return;
        }
    
        const std::size_t new_len = len_ - rem_len;
        const std::size_t block_nb = new_len / traits_type::block_size;
        const InputIter shifted_message = std::next(message_, rem_len);

        sha2_compute(ctx_, ctx_.block.begin(), 1);
        sha2_compute(ctx_, shifted_message, block_nb);

        rem_len = new_len % traits_type::block_size;
        srook::algorithm::copy(std::next(shifted_message, block_nb << traits_type::message_shift), std::next(shifted_message, rem_len), srook::begin(ctx_.block));
        ctx_.len = rem_len;
        ctx_.tot_len += (block_nb + 1) << traits_type::message_shift;
    }

    template <class Iter>
    SROOK_CXX14_CONSTEXPR void sha2_compute(context& ctx_, const Iter message, std::size_t block_nb)
    {
        srook::array<integer_type, traits_type::k_size> w{};
        srook::array<integer_type, CHAR_BIT> wv{};
        Iter sub_block{};

        for (std::size_t i = 0; i < block_nb; ++i) {
            sub_block = std::next(message, (i << traits_type::message_shift));
            for (std::size_t j = 0; j < 16; ++j) traits_type::pack(std::next(sub_block, j << traits_type::subblock_shift), w[j]);
            for (std::size_t j = 16; j < w.size(); ++j) traits_type::SCR(w, j);
            srook::algorithm::copy(srook::begin(ctx_.h), srook::end(ctx_.h), srook::begin(wv));
            for (std::size_t j = 0; j < w.size(); ++j) {
                const integer_type t1 = wv[7] + traits_type::s_4_1::f_2(wv[4]) + traits_type::Ch(wv[4], wv[5], wv[6]) + traits_type::round_constant[j] + w[j];
                const integer_type t2 = traits_type::s_4_1::f_1(wv[0]) + traits_type::Maj(wv[0], wv[1], wv[2]);
                traits_type::rotate(wv, t1, t2);
            }
            ctx_.h = traits_type::sum(ctx_.h, wv);
        }
    }

    SROOK_CXX14_CONSTEXPR void sha2_fin(context& ctx_)
    {
        const std::size_t block_nb = (1 + ((traits_type::block_size - (9 + traits_type::disone_bit)) < (ctx_.len % traits_type::block_size)));
        const std::size_t len_b = (ctx_.tot_len + ctx_.len) << 3;
        const std::size_t pm_len = block_nb << traits_type::message_shift;
    
        srook::algorithm::fill(std::next(srook::begin(ctx_.block), ctx_.len), std::next(srook::begin(ctx_.block), pm_len - ctx_.len), 0); 
        ctx_.block[ctx_.len] = 0x80;
        traits_type::unpack2(static_cast<integer_type>(len_b), std::next(srook::begin(ctx_.block), pm_len - 4));
        sha2_compute(ctx_, ctx_.block.begin(), block_nb);
        for (std::size_t i = 0; i < ctx_.h.size() - traits_type::last_unpack_distance; ++i) traits_type::unpack1(ctx_.h[i], std::next(srook::begin(digest_), i << traits_type::subblock_shift));
    }
private:
    const InputIter message_;
    const std::size_t len_;
    internal_container_type digest_;
    mutable std::atomic<std::string*> s_;
    mutable srook::mutex m_;
    
    struct context SROOK_FINAL {
        std::size_t tot_len;
        std::size_t len;
        srook::array<srook::uint8_t, 2 * traits_type::block_size> block;
        srook::array<integer_type, CHAR_BIT> h;
    };
};

#if SROOK_HAS_CONCEPTS
template <std::size_t B1, std::size_t B2 = 0, srook::concepts::InputIterator InputIter>
#else
template <std::size_t B1, std::size_t B2 = 0, class InputIter>
#endif
SROOK_CONSTEXPR SROOK_FORCE_INLINE sha2<B1, B2, InputIter> make_sha2(InputIter first, InputIter last)
{
    return sha2<B1, B2, InputIter>(first, last);
}

template <std::size_t B1, std::size_t B2 = 0, class SinglePassRange>
SROOK_CONSTEXPR SROOK_FORCE_INLINE sha2<B1, B2, SROOK_DEDUCED_TYPENAME SinglePassRange::const_iterator> make_sha2(const SinglePassRange& range)
{
    return sha2<B1, B2, SROOK_DEDUCED_TYPENAME SinglePassRange::const_iterator>(srook::begin(range), srook::end(range));
}

SROOK_INLINE_NAMESPACE(literals)
namespace hash_literals {

SROOK_FORCE_INLINE sha2<224, 0, const char*> operator"" _sha224(const char* s, std::size_t length)
{
    return sha2<224, 0, const char*>(s, s + length);
}

SROOK_FORCE_INLINE sha2<256, 0, const char*> operator"" _sha256(const char* s, std::size_t length)
{
    return sha2<256, 0, const char*>(s, s + length);
}

SROOK_FORCE_INLINE sha2<384, 0, const char*> operator"" _sha384(const char* s, std::size_t length)
{
    return sha2<384, 0, const char*>(s, s + length);
}

SROOK_FORCE_INLINE sha2<512, 0, const char*> operator"" _sha512(const char* s, std::size_t length)
{
    return sha2<512, 0, const char*>(s, s + length);
}

SROOK_FORCE_INLINE sha2<512, 224, const char*> operator"" _sha512_224(const char* s, std::size_t length)
{
    return sha2<512, 224, const char*>(s, s + length);
}

SROOK_FORCE_INLINE sha2<512, 256, const char*> operator"" _sha512_256(const char* s, std::size_t length)
{
    return sha2<512, 256, const char*>(s, s + length);
}

} // namespace hash_literals
SROOK_INLINE_NAMESPACE_END

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(hash, srook)

#endif
#endif

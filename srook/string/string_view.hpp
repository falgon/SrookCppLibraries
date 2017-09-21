#ifndef INCLUDED_SROOK_STRING_STRING_VIEW_HPP
#define INCLUDED_SROOK_STRING_STRING_VIEW_HPP

#include <srook/config/feature/constexpr.hpp>
#include <srook/config/feature/inline_namespace.hpp>
#include <srook/config/noexcept_detection.hpp>
#include <srook/cxx20/concepts/workaround/workaround.hpp>
#include <srook/type_traits/is_swappable.hpp>
#if SROOK_HAS_CONCEPT
#	include <srook/cxx20/concepts/CharType.hpp>
#else
#	include <srook/type_traits/is_character.hpp>
#endif
#include <algorithm>
#include <stdexcept>
#include <string>
#include <utility>

namespace srook {
namespace string {
SROOK_INLINE_NAMESPACE(v1)

template <class charT, class Traits>
class basic_string_view {
public:
#if SROOK_HAS_CONCEPT
    static_assert(srook::concepts::CharType<charT>, "charT must be a character type.");
#else
	static_assert(srook::is_character<charT>(), "charT must be a character type.");
#endif
    typedef Traits traits_type;
    typedef charT value_type;
    typedef charT *pointer;
    typedef const charT *const_pointer;
    typedef charT &reference;
    typedef const charT &const_reference;
    typedef const_pointer const_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
    typedef const_reverse_iterator reverse_iterator;
    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;
    static SROOK_CONSTEXPR_OR_CONST size_type npos = size_type(-1);

    SROOK_CONSTEXPR basic_string_view() SROOK_NOEXCEPT_TRUE
	: data_(nullptr), length_(0) {}

    SROOK_CONSTEXPR basic_string_view(const basic_string_view &) SROOK_NOEXCEPT_TRUE = default;

    basic_string_view &operator=(const basic_string_view &) SROOK_NOEXCEPT_TRUE = default;

    template <class Allocator>
    basic_string_view(const std::basic_string<charT, Traits, Allocator> &s) SROOK_NOEXCEPT_TRUE
	: data_(s.data()),length_(s.length()) {}

    SROOK_CONSTEXPR basic_string_view(const charT *s)
	: data_(s), length_(Traits::length(s)) {}

    SROOK_CONSTEXPR basic_string_view(const charT *s, size_type len)
	: data_(s), length_(std::move(len)) {}

    SROOK_CONSTEXPR const_iterator begin() const SROOK_NOEXCEPT_TRUE { return data_; }
    SROOK_CONSTEXPR const_iterator cbegin() const SROOK_NOEXCEPT_TRUE { return data_; }
    SROOK_CONSTEXPR const_iterator end() const SROOK_NOEXCEPT_TRUE { return data_ + length_; }
    SROOK_CONSTEXPR const_iterator cend() const SROOK_NOEXCEPT_TRUE { return data_ + length_; }
    const_reverse_iterator rbegin() const SROOK_NOEXCEPT_TRUE { return const_reverse_iterator(end()); }
    const_reverse_iterator crbegin() const SROOK_NOEXCEPT_TRUE { return const_reverse_iterator(end()); }
    const_reverse_iterator rend() const SROOK_NOEXCEPT_TRUE { return const_reverse_iterator(begin()); }
    const_reverse_iterator crend() const SROOK_NOEXCEPT_TRUE { return const_reverse_iterator(begin()); }

#define CAPACITY_SIZE(FUNCNAME) \
    SROOK_CONSTEXPR size_type FUNCNAME() const SROOK_NOEXCEPT_TRUE { return length_; }
    CAPACITY_SIZE(size)
    CAPACITY_SIZE(length)
    CAPACITY_SIZE(max_size)
#undef CAPACITY_SIZE
    SROOK_CONSTEXPR bool empty() const SROOK_NOEXCEPT_TRUE
    {
	return length_ == 0;
    }

    SROOK_CONSTEXPR const_reference operator[](size_type pos) const SROOK_NOEXCEPT_TRUE { return data_[pos]; }
    SROOK_CONSTEXPR const_reference at(size_type pos) const
    {
	return pos >= length_ ? throw std::out_of_range("srook::string_view::at"), data_[0] : data_[pos];
    }

    SROOK_CONSTEXPR const_reference front() const { return data_[0]; }
    SROOK_CONSTEXPR const_reference back() const { return data_[length_ - 1]; }
    SROOK_CONSTEXPR const_pointer data() const SROOK_NOEXCEPT_TRUE { return data_; }

    SROOK_CXX14_CONSTEXPR void remove_prefix(size_type n)
    {
	if (n > length_) n = length_;
	data_ += n;
	length_ -= n;
    }
    SROOK_CXX14_CONSTEXPR void remove_suffix(size_type n)
    {
	if (n > length_) n = length_;
	length_ -= n;
    }

    SROOK_CXX14_CONSTEXPR void swap(basic_string_view &s) SROOK_NOEXCEPT_TRUE
    {
	std::swap(data_, s.data_);
	std::swap(length_, s.length_);
    }

    template <class Allocator>
    explicit operator std::basic_string<charT, Traits, Allocator>() const
    {
	return std::basic_string<charT, Traits, Allocator>(begin(), end());
    }

    template <class Allocator = std::allocator<charT>>
    std::basic_string<charT, Traits, Allocator> to_string(const Allocator &alloc = Allocator()) const
    {
	return std::basic_string<charT, Traits, Allocator>(begin(), end(), alloc);
    }

    size_type copy(charT *s, size_type n, size_type pos = 0)
    {
	if (pos > size()) throw std::out_of_range("srook::string_view::copy");
	const size_type len = std::min(n, length_ - pos);
	traits_type::copy(s, data() + pos, len);
	return len;
    }

    SROOK_CXX14_CONSTEXPR basic_string_view substr(size_type pos, size_type n = npos) const
    {
	if (pos > size()) throw std::out_of_range("srook::string_view::substr");
	return basic_string_view(data() + pos, std::min(size() - pos, n));
    }

    SROOK_CXX14_CONSTEXPR int compare(basic_string_view x) const SROOK_NOEXCEPT_TRUE
    {
	const int cmp = Traits::compare(data_, x.data_, std::min(length_, x.length_));
	return cmp != 0 ? cmp : (length_ == x.length_ ? 0 : length_ < x.length_ ? -1 : 1);
    }

    SROOK_CXX14_CONSTEXPR int compare(size_type pos, size_type n, basic_string_view x) const SROOK_NOEXCEPT_TRUE
    {
	return substr(pos, n).compare(x);
    }

    SROOK_CXX14_CONSTEXPR int compare(size_type pos1, size_type n1, basic_string_view x, size_type pos2, size_type n2) const
    {
	return substr(pos1, n1).compare(x.substr(pos2, n2));
    }

    SROOK_CXX14_CONSTEXPR int compare(const charT *x) const
    {
	return compare(basic_string_view(x));
    }

    SROOK_CXX14_CONSTEXPR int compare(size_type pos, size_type n, const charT *x) const
    {
	return substr(pos, n).compare(basic_string_view(x));
    }

    SROOK_CXX14_CONSTEXPR int compare(size_type pos, size_type n1, const charT *x, size_type n2) const
    {
	return substr(pos, n1).compare(basic_string_view(x, n2));
    }

    SROOK_CONSTEXPR bool starts_with(charT c) const SROOK_NOEXCEPT_TRUE
    {
	return !empty() && Traits::eq(c, front());
    }

    SROOK_CONSTEXPR bool starts_with(basic_string_view x) const SROOK_NOEXCEPT_TRUE
    {
	return length_ >= x.length_ && Traits::compare(data_, x.data_, x.length_) == 0;
    }

    SROOK_CONSTEXPR bool ends_with(charT c) const SROOK_NOEXCEPT_TRUE
    {
	return !empty() && Traits::eq(c, back());
    }

    SROOK_CONSTEXPR bool ends_with(basic_string_view x) const SROOK_NOEXCEPT_TRUE
    {
	return length_ >= x.length_ && Traits::compare(data_ + length_ - x.length_, x.data_, x.length_) == 0;
    }

    SROOK_CXX14_CONSTEXPR size_type find(basic_string_view s, size_type pos = 0) const SROOK_NOEXCEPT_TRUE
    {
	if (pos > size()) return npos;
	if (s.empty()) return pos;

	const_iterator iter = std::search(cbegin() + pos, cend(), s.cbegin(), s.cend(), Traits::eq);
	return iter == cend() ? npos : std::distance(cbegin(), iter);
    }

    SROOK_CXX14_CONSTEXPR size_type find(charT c, size_type pos = 0) const SROOK_NOEXCEPT_TRUE
    {
	return find(basic_string_view(&c, 1), pos);
    }

    SROOK_CXX14_CONSTEXPR size_type find(const charT *s, size_type pos, size_type n) const SROOK_NOEXCEPT_TRUE
    {
	return find(basic_string_view(s, n), pos);
    }

    SROOK_CXX14_CONSTEXPR size_type find(const charT *s, size_type pos = 0) const SROOK_NOEXCEPT_TRUE
    {
	return find(basic_string_view(s), pos);
    }

    SROOK_CXX14_CONSTEXPR size_type rfind(basic_string_view s, size_type pos = npos) const SROOK_NOEXCEPT_TRUE
    {
	if (length_ < s.length_) return npos;
	if (pos > length_ - s.length_) pos = length_ - s.length_;
	if (s.length_ == 0u) return pos;

	for (const charT *cur = data_ + pos;; --cur) {
	    if (Traits::compare(cur, s.data_, s.length_) == 0) return cur - data_;
	    if (cur == data_) return npos;
	}
    }

    SROOK_CXX14_CONSTEXPR size_type rfind(charT c, size_type pos = npos) const SROOK_NOEXCEPT_TRUE
    {
	return rfind(basic_string_view(&c, 1), pos);
    }

    SROOK_CXX14_CONSTEXPR size_type rfind(const charT *s, size_type pos, size_type n) const SROOK_NOEXCEPT_TRUE
    {
	return rfind(basic_string_view(s, n), pos);
    }

    SROOK_CXX14_CONSTEXPR size_type rfind(const charT *s, size_type pos = npos) const SROOK_NOEXCEPT_TRUE
    {
	return rfind(basic_string_view(s), pos);
    }

    SROOK_CXX14_CONSTEXPR size_type find_first_of(basic_string_view s, size_type pos = 0) const SROOK_NOEXCEPT_TRUE
    {
	if (pos >= length_ || s.length_ == 0) return npos;

	const_iterator iter = std::find_first_of(std::next(cbegin(), pos), cend(), s.cbegin(), s.cend(), Traits::eq);
	return iter == cend() ? npos : std::distance(cbegin(), iter);
    }

    SROOK_CXX14_CONSTEXPR size_type find_first_of(charT c, size_type pos = 0) const SROOK_NOEXCEPT_TRUE
    {
	return find_first_of(basic_string_view(&c, 1), pos);
    }

    SROOK_CXX14_CONSTEXPR size_type find_first_of(const charT *s, size_type pos, size_type n) const SROOK_NOEXCEPT_TRUE
    {
	return find_first_of(basic_string_view(s, n), pos);
    }

    SROOK_CXX14_CONSTEXPR size_type find_first_of(const charT *s, size_type pos = 0) const SROOK_NOEXCEPT_TRUE
    {
	return find_first_of(basic_string_view(s), pos);
    }

    SROOK_CXX14_CONSTEXPR size_type find_first_not_of(basic_string_view s, size_type pos = 0) const SROOK_NOEXCEPT_TRUE
    {
	if (pos >= length_) return npos;
	if (s, length_ == 0) return pos;

	const_iterator iter = find_not_of(std::next(cbegin(), pos), cend(), s);
	return iter == cend() ? npos : std::distance(cbegin(), iter);
    }

    SROOK_CXX14_CONSTEXPR size_type find_first_not_of(charT c, size_type pos = 0) const SROOK_NOEXCEPT_TRUE
    {
	return find_first_not_of(basic_string_view(&c, 1), pos);
    }

    SROOK_CXX14_CONSTEXPR size_type find_first_not_of(const charT *s, size_type pos, size_type n) const SROOK_NOEXCEPT_TRUE
    {
	return find_first_not_of(basic_string_view(s), pos);
    }

    SROOK_CXX14_CONSTEXPR size_type find_last_not_of(basic_string_view s, size_type pos = npos) const SROOK_NOEXCEPT_TRUE
    {
	if (pos >= length_) pos = length_ - 1;
	if (s.length_ == 0u) return pos;

	pos = length_ - (pos + 1);
	const_reverse_iterator iter = find_not_of(std::next(crbegin(), pos), crend(), s);
	return iter == crend() ? npos : reverse_distance(crbegin(), iter);
    }

    SROOK_CXX14_CONSTEXPR size_type find_last_not_of(charT c, size_type pos = npos) const SROOK_NOEXCEPT_TRUE
    {
	return find_last_not_of(basic_string_view(&c, 1), pos);
    }

    SROOK_CXX14_CONSTEXPR size_type find_last_not_of(const charT *s, size_type pos, size_type n) const SROOK_NOEXCEPT_TRUE
    {
	return find_last_not_of(basic_string_view(s, n), pos);
    }

    SROOK_CXX14_CONSTEXPR size_type find_last_not_of(const charT *s, size_type pos = npos) const SROOK_NOEXCEPT_TRUE
    {
	return find_last_not_of(basic_string_view(s), pos);
    }

private:
    const charT *data_;
    size_type length_;

    template <class reverse_iter>
    size_type reverse_distance(reverse_iter first, reverse_iter last) const SROOK_NOEXCEPT_TRUE
    {
	return length_ - 1 - std::distance(first, last);
    }

    template <class Iterator>
    Iterator find_not_of(Iterator first, Iterator last, basic_string_view s) const SROOK_NOEXCEPT_TRUE
    {
	for (; first != last; ++first)
	    if (0 == Traits::find(s.data_, s.length_, *first)) return first;
	return last;
    }

    friend inline SROOK_CXX14_CONSTEXPR bool operator==(basic_string_view x, basic_string_view y) SROOK_NOEXCEPT_TRUE
    {
	if (x.size() != y.size()) return false;
	return x.compare(y) == 0;
    }

    friend inline SROOK_CXX14_CONSTEXPR bool operator!=(basic_string_view x, basic_string_view y) SROOK_NOEXCEPT_TRUE
    {
	if (x.size() != y.size()) return true;
	return x.compare(y) != 0;
    }

#define DEFINE_COMPARISON(OP)                                                                                          \
    friend inline SROOK_CXX14_CONSTEXPR bool operator OP(basic_string_view x, basic_string_view y) SROOK_NOEXCEPT_TRUE \
    {                                                                                                                  \
	return x.compare(y) OP 0;                                                                                      	   \
    }
    DEFINE_COMPARISON(<)
    DEFINE_COMPARISON(>)
    DEFINE_COMPARISON(<=)
    DEFINE_COMPARISON(>=)
#undef DEFINE_COMPARISON

    template <class Allocator>
    friend inline SROOK_CXX14_CONSTEXPR bool operator==(basic_string_view x, const std::basic_string<charT, Traits, Allocator> &y) SROOK_NOEXCEPT_TRUE
    {
	return x == basic_string_view(y);
    }

    template <class Allocator>
    friend inline SROOK_CXX14_CONSTEXPR bool operator==(const std::basic_string<charT, Traits, Allocator> &x, basic_string_view y) SROOK_NOEXCEPT_TRUE
    {
	return basic_string_view(x) == y;
    }

    friend inline SROOK_CXX14_CONSTEXPR bool operator==(basic_string_view x, const charT *y) SROOK_NOEXCEPT_TRUE
    {
	return x == basic_string_view(y);
    }

    friend inline SROOK_CXX14_CONSTEXPR bool operator==(const charT *x, basic_string_view y) SROOK_NOEXCEPT_TRUE
    {
	return basic_string_view(x) == y;
    }

    template <class Allocator>
    friend inline SROOK_CXX14_CONSTEXPR bool operator!=(basic_string_view x, const std::basic_string<charT, Traits, Allocator> &y) SROOK_NOEXCEPT_TRUE
    {
	return x != basic_string_view(y);
    }

    template <class Allocator>
    friend inline SROOK_CXX14_CONSTEXPR bool operator!=(const std::basic_string<charT, Traits, Allocator> &x, basic_string_view y) SROOK_NOEXCEPT_TRUE
    {
	return basic_string_view(x) != y;
    }

    friend inline SROOK_CXX14_CONSTEXPR bool operator!=(basic_string_view x, const charT *y) SROOK_NOEXCEPT_TRUE
    {
	return x != basic_string_view(y);
    }

    friend inline SROOK_CXX14_CONSTEXPR bool operator!=(const charT *x, basic_string_view y) SROOK_NOEXCEPT_TRUE
    {
	return basic_string(x) != y;
    }

    template <class Allocator>
    friend inline SROOK_CXX14_CONSTEXPR bool operator<(const std::basic_string<charT, Traits, Allocator> &x, basic_string_view y) SROOK_NOEXCEPT_TRUE
    {
	return basic_string_view(x) < y;
    }

    template <class Allocator>
    friend inline SROOK_CXX14_CONSTEXPR bool operator<(basic_string_view x, const std::basic_string<charT, Traits, Allocator> &y) SROOK_NOEXCEPT_TRUE
    {
	return x < basic_string_view(y);
    }

    friend inline SROOK_CXX14_CONSTEXPR bool operator<(basic_string_view x, const charT *y) SROOK_NOEXCEPT_TRUE
    {
	return x < basic_string_view(y);
    }

    friend inline SROOK_CXX14_CONSTEXPR bool operator<(const charT *x, basic_string_view y) SROOK_NOEXCEPT_TRUE
    {
	return basic_string_view(x) < y;
    }

    template <class Allocator>
    friend inline SROOK_CXX14_CONSTEXPR bool operator>(const std::basic_string<charT, Traits, Allocator> &x, basic_string_view y) SROOK_NOEXCEPT_TRUE
    {
	return basic_string_view(x) > y;
    }

    template <class Allocator>
    friend inline SROOK_CXX14_CONSTEXPR bool operator>(basic_string_view x, const std::basic_string<charT, Traits, Allocator> &y) SROOK_NOEXCEPT_TRUE
    {
	return x > basic_string_view(y);
    }

    friend inline SROOK_CXX14_CONSTEXPR bool operator>(basic_string_view x, const charT *y) SROOK_NOEXCEPT_TRUE
    {
	return x > basic_string(y);
    }

    friend inline SROOK_CXX14_CONSTEXPR bool operator>(const charT *x, basic_string_view y) SROOK_NOEXCEPT_TRUE
    {
	return basic_string(x) > y;
    }

    template <class Allocator>
    friend inline SROOK_CXX14_CONSTEXPR bool operator<=(basic_string_view x, const std::basic_string<charT, Traits, Allocator> &y) SROOK_NOEXCEPT_TRUE
    {
	return x <= basic_string_view(y);
    }

    template <class Allocator>
    friend inline SROOK_CXX14_CONSTEXPR bool operator<=(const std::basic_string<charT, Traits, Allocator> &x, basic_string_view y) SROOK_NOEXCEPT_TRUE
    {
	return basic_string_view(x) <= y;
    }

    template <class Allocator>
    friend inline SROOK_CXX14_CONSTEXPR bool operator<=(basic_string_view x, const charT *y) SROOK_NOEXCEPT_TRUE
    {
	return x <= basic_string_view(y);
    }

    template <class Allocator>
    friend inline SROOK_CXX14_CONSTEXPR bool operator<=(const charT *x, basic_string_view y) SROOK_NOEXCEPT_TRUE
    {
	return basic_string_view(x) <= y;
    }

    template <class Allocator>
    friend inline SROOK_CXX14_CONSTEXPR bool operator>=(basic_string_view x, const std::basic_string<charT, Traits, Allocator> &y) SROOK_NOEXCEPT_TRUE
    {
	return x >= basic_string_view(y);
    }

    template <class Allocator>
    friend inline SROOK_CXX14_CONSTEXPR bool operator>=(const std::basic_string<charT, Traits, Allocator> &x, basic_string_view y) SROOK_NOEXCEPT_TRUE
    {
	return basic_string_view(x) >= y;
    }

    template <class Allocator>
    friend inline SROOK_CXX14_CONSTEXPR bool operator>=(basic_string_view x, const charT *y) SROOK_NOEXCEPT_TRUE
    {
	return x >= basic_string_view(y);
    }

    template <class Allocator>
    friend inline SROOK_CXX14_CONSTEXPR bool operator>=(const charT *x, basic_string_view y) SROOK_NOEXCEPT_TRUE
    {
	return basic_string_view(x) >= y;
    }

    inline void sv_insert_fill_chars(std::basic_ostream<charT, Traits> &os, std::size_t n) const 
    {
	constexpr std::size_t chunk_size = 8;
	charT fill_chars[chunk_size];
	std::fill_n(fill_chars, static_cast<std::size_t>(chunk_size), os.fill());
	for (; n >= chunk_size && os.good(); n -= chunk_size) os.write(fill_chars, static_cast<std::size_t>(chunk_size));
	if (n > 0 && os.good()) os.write(fill_chars, n);
    }

    void sv_insert_aligned(std::basic_ostream<charT, Traits> &os) const
    {
	const std::size_t alignment_size = static_cast<std::size_t>(os.width()) - size();
	const bool align_left = (os.flags() & std::basic_ostream<charT, Traits>::adjustfield) == std::basic_ostream<charT, Traits>::left;

	if (!align_left) {
	    sv_insert_fill_chars(os, std::move(alignment_size));
	    if (os.good()) os.write(data(), size());
	} else {
	    os.write(data(), size());
	    if (os.good()) sv_insert_fill_chars(os, std::move(alignment_size));
	}
    }

    friend inline std::basic_ostream<charT, Traits> &operator<<(std::basic_ostream<charT, Traits> &os, const basic_string_view &str)
    {
	if (os.good()) {
	    const std::size_t size = str.size();
	    const std::size_t w = static_cast<std::size_t>(os.width());
		if(w <= size) {
			os.write(str.data(), size);
		} else {
			str.sv_insert_aligned(os);
	    }
	    os.width(0);
	}

	return os;
    }
};

typedef basic_string_view<char, std::char_traits<char> > string_view;
typedef basic_string_view<wchar_t, std::char_traits<wchar_t> > wstring_view;
typedef basic_string_view<char16_t, std::char_traits<char16_t> > u16string_view;
typedef basic_string_view<char32_t, std::char_traits<char32_t> > u32string_view;

#if SROOK_CPP_USER_DEFINED_LITERALS

SROOK_CONSTEXPR string_view operator "" _sv(const char* str, std::size_t len) SROOK_NOEXCEPT_TRUE
{
	return string_view{str, len};
}

SROOK_CONSTEXPR u16string_view operator "" _sv(const char16_t* str, std::size_t len) SROOK_NOEXCEPT_TRUE
{
	return u16string_view{str, len};
}

SROOK_CONSTEXPR u32string_view operator "" _sv(const char32_t* str, std::size_t len) SROOK_NOEXCEPT_TRUE
{
	return u32string_view{str, len};
}

SROOK_CONSTEXPR wstring_view operator "" _sv(const wchar_t* str, std::size_t len) SROOK_NOEXCEPT_TRUE
{
	return wstring_view{str, len};
}

#endif

SROOK_INLINE_NAMESPACE_END
} // namespace string

#if SROOK_CPP_USER_DEFINED_LITERALS
namespace literals{
namespace string_view_literals{

using string::operator "" _sv;

} // namespace string_view_literals 

using string_view_literals::operator "" _sv;

} // namespace literals

namespace string_view_literals{

using string::operator "" _sv;

} // namespace string_view_literals
#endif

using string::string_view;
using string::wstring_view;
using string::u16string_view;
using string::u32string_view;

} // namespace srook
#endif

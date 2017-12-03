#ifndef INCLUDED_SROOK_IOS_JPEG_BIFSTREAM_HPP
#define INCLUDED_SROOK_IOS_JPEG_BIFSTREAM_HPP
#include <algorithm>
#include <fstream>
#include <memory>
#include <srook/array.hpp>
#include <srook/config.hpp>
#include <srook/config/require.hpp>
#include <srook/cstddef/byte.hpp>
#include <srook/optional.hpp>
#include <srook/type_traits/has_iterator.hpp>
#include <srook/type_traits/is_callable.hpp>
#include <type_traits>

namespace srook {
namespace io {
namespace jpeg {
inline namespace v1 {

struct bifstream SROOK_FINAL : std::ifstream {
    using std::ifstream::ifstream;

    explicit bifstream(const char* filename, const std::ios_base::openmode& open_mode = std::ios::in | std::ios::binary)
        : std::ifstream{},
          buffer{},
          last(nullptr),
          forward_iter(nullptr)
    {
        try {
            exceptions(std::ios::eofbit | std::ios::failbit | std::ios::badbit);
            open(filename, open_mode);
            seekg(0, std::fstream::end);
            const std::size_t end_pos = std::size_t(tellg());
            clear();
            seekg(0, std::fstream::beg);
            const std::size_t begin_pos = std::size_t(tellg());
            const std::size_t size = end_pos - begin_pos;

            buffer = std::make_unique<srook::byte[]>(size);

            exceptions(std::ios::badbit);
            read(reinterpret_cast<char*>(buffer.get()), long(size));
            close();

            forward_iter = buffer.get();
            last = std::next(buffer.get(), size);
        } catch (const std::ios_base::failure& e) {
            buffer.reset();
            nextflag = readflag = false;
            last = forward_iter = nullptr;
            bit_position = srook::nullopt;
        }
    }

    void skip_byte(std::size_t n)
    {
        if (forward_iter + n > last) throw std::out_of_range(__func__);
        if ((forward_iter += n) >= last) readflag = false;
        bit_position = 7;
    }

    explicit operator bool() const noexcept
    {
        return readflag;
    }

    std::size_t size() const noexcept
    {
        return last - buffer.get();
    }

    srook::byte* next_address() const noexcept
    {
        if (bit_position == 7) {
            return forward_iter;
        } else if (forward_iter < last) {
            return forward_iter + 1;
        } else {
            return nullptr;
        }
    }

    ~bifstream() noexcept override {}
private: 
    struct tag_argument {
        explicit constexpr tag_argument(int num) : n(std::move(num)) {}
        int n;
    };

public:
    static constexpr auto Byte = [] {};
    static constexpr auto Word = [] {};
    static constexpr auto Bytes = [] {};

    struct Byte_n : tag_argument {
        using tag_argument::tag_argument;
    };
    struct Bits : tag_argument {
        using tag_argument::tag_argument;
    };

private:
    std::unique_ptr<srook::byte[]> buffer;
    srook::byte* last;
    srook::byte* forward_iter;

    srook::optional<int> bit_position = 7;
    const srook::array<int, 8> bit_fullmask{{0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80}};
    bool nextflag = true;
    bool readflag = true;

private:
    void increment_buffer() noexcept
    {
        if (++forward_iter >= last) readflag = false;
    }

    template <class Range, REQUIRES(srook::has_iterator_v<std::decay_t<Range> >)>
    friend std::pair<const decltype(Bytes) &, bifstream&>
    operator>>(std::pair<const decltype(Bytes) &, bifstream&> p, Range& ar) noexcept(false)
    {
        bifstream& this_ = p.second;

        if (!this_.bit_position) throw std::runtime_error("invalid construct");

        if (this_.bit_position.value() != 7) {
            this_.increment_buffer();
            this_.bit_position = 7;
        }
        if (this_.forward_iter + ar.size() > this_.last) throw std::out_of_range("Bytes operator<<");

        std::generate(std::begin(ar), std::end(ar), [&this_]() { return typename std::decay_t<Range>::value_type(*this_.forward_iter++); });
        if ((this_.forward_iter) >= this_.last) this_.readflag = false;

        return p;
    }

    template <class Value, REQUIRES(!srook::is_callable_v<std::decay_t<Value> > and !srook::has_iterator_v<std::decay_t<Value> >)>
    friend std::pair<const decltype(Byte) &, bifstream&>
    operator>>(std::pair<const decltype(Byte) &, bifstream&> p, Value& src) noexcept(false)
    {
        bifstream& this_ = p.second;

        if (!this_.bit_position) throw std::runtime_error("invalid construct");

        if (this_.readflag) {
            if (this_.bit_position.value() != 7) {
                this_.increment_buffer();
                this_.bit_position = 7;
            }
            src = Value(*this_.forward_iter);
            this_.increment_buffer();
            this_.nextflag = true;
        } else {
            throw std::runtime_error("Byte operator<<: cannot read");
        }

        return p;
    }

    template <class T, REQUIRES(std::is_integral<std::decay_t<T> >::value)>
    friend std::pair<const decltype(Word) &, bifstream&>
    operator>>(std::pair<const decltype(Word) &, bifstream&> p, T& value) noexcept(false)
    {
        bifstream& this_ = p.second;

        if (!this_.bit_position) throw std::runtime_error("invalid construct");

        if (this_.readflag) {
            if (this_.bit_position.value() != 7) {
                this_.increment_buffer();
                this_.bit_position = 7;
            }
            unsigned int r = srook::to_integer<unsigned>(*this_.forward_iter) << 8;
            this_.increment_buffer();
            r |= srook::to_integer<unsigned>(*this_.forward_iter);
            this_.increment_buffer();
            value = T(r);
        } else {
            throw std::runtime_error("Word operator<<: cannot read");
        }
        return p;
    }

    template <class T, REQUIRES(std::is_integral<std::decay_t<std::decay_t<T> > >::value)>
    friend std::pair<Bits, bifstream&>
    operator>>(std::pair<Bits, bifstream&> p, T& value) noexcept(false)
    {
        if (p.first.n <= 0) {
            value = T(0);
            return p;
        }

        bifstream& this_ = p.second;
        if (!this_.bit_position) throw std::runtime_error("invalid construct");

        int r = 0;
        for (srook::byte c{}; p.first.n; --p.first.n) {
            if (this_.bit_position.value() < 0) {
                this_.bit_position = 7;
                this_.increment_buffer();
                if (!this_.nextflag) {
                    this_.increment_buffer();
                    this_.nextflag = true;
                }

                c = *this_.forward_iter;
                if (srook::to_integer<std::underlying_type_t<srook::byte> >(c) == 0xff) {
                    c = *(this_.forward_iter + 1);
                    if (srook::to_integer<std::underlying_type_t<srook::byte> >(c) != 0) {
                        value = -srook::to_integer<std::underlying_type_t<srook::byte> >(c);
                    }
                    this_.nextflag = false;
                }
            }
            r <<= 1;
            r |= (srook::to_integer<std::underlying_type_t<srook::byte> >(*this_.forward_iter) & this_.bit_fullmask[std::size_t(this_.bit_position.value())]) ? 1 : 0;
            this_.bit_position = this_.bit_position.value() - 1;
        }
        value = T(r);
        return p;
    }

    template <class Range, REQUIRES(srook::has_iterator_v<std::decay_t<Range> >)>
    friend std::pair<const Byte_n&, bifstream&>
    operator>>(std::pair<const Byte_n&, bifstream&> p, Range& r) noexcept(false)
    {
        bifstream& this_ = p.second;

        if (this_.bit_position != 7) {
            this_.increment_buffer();
            this_.bit_position = 7;
        }
        if (this_.forward_iter + p.first.n > this_.last) throw std::out_of_range("Byte_n operator>> out of range");

        if (r.size() >= std::size_t(p.first.n)) {
            std::generate(std::begin(r), std::end(r), [&this_] { return typename Range::value_type(*this_.forward_iter++); });
        } else {
            r.resize(std::size_t(p.first.n));
            std::generate(std::begin(r), std::end(r), [&this_] { return typename Range::value_type(*this_.forward_iter++); });
        }
        if (this_.forward_iter >= this_.last) this_.readflag = false;

        return p;
    }

    template <class Tag>
    constexpr friend std::pair<Tag, bifstream&> operator|(bifstream& ofps, const Tag& t)
        SROOK_NOEXCEPT(std::make_pair(t, std::ref(ofps)))
    {
        static_assert(
            std::is_same_v<Tag, Byte_n> or std::is_same_v<Tag, std::decay_t<decltype(Byte)> > or std::is_same_v<Tag, std::decay_t<decltype(Bytes)> > or std::is_same_v<Tag, std::decay_t<decltype(Word)> > or "Invalid tag");
        return std::make_pair(t, std::ref(ofps));
    }

    friend std::pair<Bits, bifstream&> operator|(bifstream& ofps, const Bits& bits)
        SROOK_NOEXCEPT(std::make_pair(bits, std::ref(ofps)))
    {
        return std::make_pair(bits, std::ref(ofps));
    }
};

} // namespace v1
} // namespace jpeg
} // namespace io
} // namespace srook
#endif

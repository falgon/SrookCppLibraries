// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_BRAINFXXK_INTERPINTER_HPP
#define INCLUDED_SROOK_BRAINFXXK_INTERPINTER_HPP
#include <codecvt>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <locale>
#include <map>
#include <sstream>
#include <vector>

#if __has_include(<boost/algorithm/cxx11/all_of.hpp>)
#include <boost/algorithm/cxx11/all_of.hpp>
#define ALL_OF(X,FUNCTOR) boost::algorithm::all_of(X,FUNCTOR)
#else
#include <algorithm>
#define ALL_OF(X,FUNCTOR) std::all_of(std::begin(X),std::end(X),FUNCTOR)
#endif
#include<srook/config/libraries/optional.hpp>
#if __has_include(<boost/parameter/name.hpp>)
#include <boost/parameter/name.hpp>
#endif
#include <srook/array.hpp>
#include <srook/config.hpp>
#include <srook/mpl/variadic_player.hpp>

namespace srook {
namespace brainfk {
SROOK_INLINE_NAMESPACE(v1)

    template <class String, class FileStream, class BYTE, std::size_t BUFFER_SIZE = 300000>
    struct brainfk_syntax_core {
        using string_type = std::string;
        using byte = BYTE;

        brainfk_syntax_core(const std::array<String, 8>& tokens)
            : token(tokens)
            , token_syn{ { Syn::LEFT_ARROW, Syn::RIGHT_ARROW, Syn::PLUS, Syn::MINUS, Syn::DOT, Syn::CAMMA, Syn::LEFT_BRACE, Syn::RIGHT_BRACE } }
        {}

        const OPTIONAL<String>& file_open(std::string file_name)
        {
            FileStream ifs;
            return file_open_core(ifs, std::move(file_name));
        }

        const OPTIONAL<String>& analyze()
        {
            return analyze_core(String());
        }

        const OPTIONAL<String>& exec()
        {
            return exec_core(String());
        }

        virtual ~brainfk_syntax_core() = default;

    protected:
        enum struct Syn {
            LEFT_ARROW,
            RIGHT_ARROW,
            PLUS,
            MINUS,
            DOT,
            CAMMA,
            LEFT_BRACE,
            RIGHT_BRACE
        };
        static constexpr std::size_t syntax_size = 8;

        const std::array<String, syntax_size>& token;
        const std::array<Syn, syntax_size> token_syn;
        std::vector<Syn> tokenizer;

        const OPTIONAL<std::string>& file_open_core(std::ifstream& ifs, std::string file_name)
        {
            if (ifs.fail())
                return (fl = NULLOPT);

            ifs.open(std::move(file_name), std::ios::in);
            std::ostringstream os;
            os << ifs.rdbuf();
            return (fl = os.str());
        }

        const OPTIONAL<std::wstring>& file_open_core(std::wifstream& ifs, std::string file_name)
        {
            const std::codecvt_mode kBom = static_cast<std::codecvt_mode>(std::generate_header | std::consume_header);
            using WideConvUtf8Bom = std::codecvt_utf8<wchar_t, 0x10ffff, kBom>;
            WideConvUtf8Bom cvt(1);

            std::locale loc(ifs.getloc(), &cvt);
            auto oldLocale = ifs.imbue(std::move(loc));
            ifs.open(std::move(file_name), std::ios::in | std::ios::binary);

            std::wstringstream wss;
            wss << ifs.rdbuf();

            std::wstring removeStr = L"\r";
            auto pos(wss.str().find(removeStr));

            while (pos != std::wstring::npos) {
                wss.str().replace(pos, removeStr.length(), L"");
                pos = wss.str().find(removeStr, pos);
            }
            ifs.close();
            ifs.imbue(oldLocale);

            return (fl = wss.str());
        }

        const OPTIONAL<String>& analyze_core(const std::string&&)
        {
            return analyzer(std::string::npos);
        }
        const OPTIONAL<String>& analyze_core(const std::wstring&&)
        {
            return analyzer(std::string::npos);
        }

        template <class T>
        OPTIONAL<String>& analyzer(const T& npos)
        {
            if (!fl) {
                return fl;
            }
            const std::size_t fl_size = fl->size();
            for (std::size_t c = 0; !(*fl).empty() || c < fl_size; ++c) {
                std::map<std::size_t, std::pair<String, Syn>> indexer;
                std::array<bool, syntax_size> bits;
                bits.fill(true);

                std::size_t pos = 0, i = 0;
                for (const auto& t : token) {
                    if ((pos = (*fl).find(t)) == npos)
                        bits[i] = false;
                    else
                        indexer[pos] = std::make_pair(t, token_syn[i]);
                    ++i;
                }
                if (ALL_OF(bits, [](const bool b) { return b == false; }))
                    break;

                tokenizer.emplace_back(indexer.begin()->second.second);
                (*fl).erase(indexer.begin()->first, indexer.begin()->second.first.size());
            }
            return fl;
        }

        template <class Str>
        const OPTIONAL<String>& exec_core(const Str&&)
        {
            return execer(std::cout);
        }

        virtual const OPTIONAL<String>& execer(decltype(std::cout) & outer)
        {
            std::array<byte, BUFFER_SIZE> buff;
            std::size_t buff_ptr = 0, loop_b = 0;

            if (!fl) {
                return fl;
            }
            for (std::size_t i = 0; i < tokenizer.size(); ++i) {
                switch (tokenizer[i]) {
                case Syn::LEFT_ARROW:
                    ++buff_ptr;
                    break;
                case Syn::RIGHT_ARROW:
                    --buff_ptr;
                    break;
                case Syn::PLUS:
                    ++buff[buff_ptr];
                    break;
                case Syn::MINUS:
                    --buff[buff_ptr];
                    break;
                case Syn::DOT:
                    outer << buff[buff_ptr];
                    break;
                case Syn::CAMMA:
                    buff[buff_ptr] = std::getchar();
                    break;
                case Syn::LEFT_BRACE:
                    if (!buff[buff_ptr]) {
                        for (++i; loop_b > 0 || tokenizer[i] != Syn::RIGHT_BRACE; ++i) {
                            if (tokenizer[i] == Syn::LEFT_BRACE)
                                ++loop_b;
                            else if (tokenizer[i] == Syn::RIGHT_BRACE)
                                --loop_b;
                        }
                    }
                    break;
                case Syn::RIGHT_BRACE:
                    if (buff[buff_ptr] != 0) {
                        for (--i; loop_b > 0 || tokenizer[i] != Syn::LEFT_BRACE; --i) {
                            if (tokenizer[i] == Syn::RIGHT_BRACE)
                                ++loop_b;
                            if (tokenizer[i] == Syn::LEFT_BRACE)
                                --loop_b;
                        }
                        --i;
                    }
                    break;
                }
            }
            return fl;
        }

    public:
        OPTIONAL<String> fl;
    };

#if __cplusplus >= 201703L
    template <class, class = std::underlying_type_t<std::byte>, std::size_t = 300000>
#else
    template <class, class = unsigned char, std::size_t = 300000>
#endif
    struct brainfk_syntax;
    template <class BYTE, std::size_t size>
    struct brainfk_syntax<std::string, BYTE, size> final : brainfk_syntax_core<std::string, std::ifstream, BYTE, size> {
        using brainfk_syntax_core<std::string, std::ifstream, BYTE, size>::brainfk_syntax_core;
    };
    template <class BYTE, std::size_t size>
    struct brainfk_syntax<std::wstring, BYTE, size> final : brainfk_syntax_core<std::wstring, std::wifstream, BYTE, size> {
        using brainfk_syntax_core<std::wstring, std::wifstream, BYTE, size>::brainfk_syntax_core;
    };

#if __has_include(<boost/parameter/name.hpp>)
namespace label {
	BOOST_PARAMETER_NAME(INCREMENT_THE_POINTER)
	BOOST_PARAMETER_NAME(DECREMENT_THE_POINTER)
    BOOST_PARAMETER_NAME(INCREMENT_THE_BYTE_AT_THE_POINTER)
    BOOST_PARAMETER_NAME(DECREMENT_THE_BYTE_AT_THE_POINTER)
   	BOOST_PARAMETER_NAME(OUTPUT)
   	BOOST_PARAMETER_NAME(INPUT)
   	BOOST_PARAMETER_NAME(JUMP_FORWARD)
    BOOST_PARAMETER_NAME(JUMP_BACKWARD)
} // namespace label

namespace detail {

template <class string_type>
constexpr std::array<string_type, 8> make_keywords_impl(string_type incr_ptr, string_type decr_ptr, string_type incr_byte, string_type decr_byte, string_type output, string_type input, string_type jump_forward, string_type jump_backward)
{
	return std::array<string_type, 8>{{ std::move(incr_ptr), std::move(decr_ptr), std::move(incr_byte), std::move(decr_byte), std::move(output), std::move(input), std::move(jump_forward), std::move(jump_backward) }};
}

} // namespace detail
	
template <class ArgPack>
constexpr decltype(auto) make_keywords(const ArgPack& args)
{
	using namespace label;
	return detail::make_keywords_impl(
			args[_INCREMENT_THE_POINTER],args[_DECREMENT_THE_POINTER],args[_INCREMENT_THE_BYTE_AT_THE_POINTER],args[_DECREMENT_THE_BYTE_AT_THE_POINTER],args[_OUTPUT],args[_INPUT],args[_JUMP_FORWARD],args[_JUMP_BACKWARD]);
}
#endif

SROOK_INLINE_NAMESPACE_END
} // namespace brainfk
} // namespace srook
#endif

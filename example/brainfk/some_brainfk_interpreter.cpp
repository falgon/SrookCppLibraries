// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#include <srook/brainfk/brainfk.hpp>

int main(const int argc, const char* argv[])
{
    if (argc < 2) {
        return -1;
    }
    using namespace std::string_literals;
    namespace br_keywords = srook::brainfk::label;

    const auto brainfxxk_keywords = srook::brainfk::make_keywords((
        br_keywords::_INCREMENT_THE_POINTER = ">"s,
        br_keywords::_DECREMENT_THE_POINTER = "<"s,
        br_keywords::_INCREMENT_THE_BYTE_AT_THE_POINTER = "+"s,
        br_keywords::_DECREMENT_THE_BYTE_AT_THE_POINTER = "-"s,
        br_keywords::_OUTPUT = "."s,
        br_keywords::_INPUT = ","s,
        br_keywords::_JUMP_FORWARD = "["s,
        br_keywords::_JUMP_BACKWARD = "]"s));

    const auto kemono_keywords = srook::brainfk::make_keywords((
        br_keywords::_INCREMENT_THE_POINTER = L"たのしー！"s,
        br_keywords::_DECREMENT_THE_POINTER = L"すごーい！"s,
        br_keywords::_INCREMENT_THE_BYTE_AT_THE_POINTER = L"たーのしー！"s,
        br_keywords::_DECREMENT_THE_BYTE_AT_THE_POINTER = L"すっごーい！"s,
        br_keywords::_OUTPUT = L"なにこれなにこれ！"s,
        br_keywords::_INPUT = L"おもしろーい！"s,
        br_keywords::_JUMP_FORWARD = L"うわー！"s,
        br_keywords::_JUMP_BACKWARD = L"わーい！"s));

    const auto ponkotsu_keywords = srook::brainfk::make_keywords((
        br_keywords::_INCREMENT_THE_POINTER = L"ブラック企業かよ"s,
        br_keywords::_DECREMENT_THE_POINTER = L"アイスうめー"s,
        br_keywords::_INCREMENT_THE_BYTE_AT_THE_POINTER = L"ﾋｮｳﾄﾞ！"s,
        br_keywords::_DECREMENT_THE_BYTE_AT_THE_POINTER = L"ﾄﾞﾙﾌｧﾍｷｾﾝﾀﾞｰ"s,
        br_keywords::_OUTPUT = L"おもらひ"s,
        br_keywords::_INPUT = L"おねひ"s,
        br_keywords::_JUMP_FORWARD = L"労災はおりない"s,
        br_keywords::_JUMP_BACKWARD = L"ﾊﾝﾏｰ"s));

    srook::brainfk::brainfk_syntax<std::string> bk_syn(brainfxxk_keywords);
    srook::brainfk::brainfk_syntax<std::wstring> km_syn(kemono_keywords);
    srook::brainfk::brainfk_syntax<std::wstring> pq_syn(ponkotsu_keywords);

    const auto& status0 = bk_syn.file_open(argv[1]);
    if (!status0) {
        return EXIT_FAILURE;
    }

    const auto& status1 = km_syn.file_open(argv[2]);
    if (!status1) {
        return EXIT_FAILURE;
    }

    const auto& status2 = pq_syn.file_open(argv[3]);
    if (!status2) {
        return EXIT_FAILURE;
    }

    bk_syn.analyze();
    bk_syn.exec();

    std::cout << std::endl;

    km_syn.analyze();
    km_syn.exec();

    std::cout << std::endl;

    pq_syn.analyze();
    pq_syn.exec();

    std::cout << std::endl;
}

// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_PLOT_GNU_PLOTER_HPP
#define INCLUDED_SROOK_PLOT_GNU_PLOTER_HPP

#include <fstream>
#include <srook/algorithm/for_each.hpp>
#include <srook/config/feature.hpp>
#include <srook/functional/deduction_negate.hpp>
#include <srook/process.hpp>
#include <srook/scope/unique_resource.hpp>
#include <srook/string/string_view.hpp>
#include <string>

namespace srook {
namespace plot {
namespace gnu {
SROOK_INLINE_NAMESPACE(v1)

struct ploter {
    constexpr ploter(const char* file) : file_(file) {}

    void output(const size_t index_size)
    {
        using namespace std;
        using namespace std::string_literals;

        std::string str = "plot \"" + std::string(file_) + "\"";
        for (size_t i = 0; i < index_size; ++i) {
            str += " index " + std::to_string(i) + ", \"" + std::string(file_) + "\"";
        }
        str.erase(next(end(str), deduction_negate()(file_.size() - 4)), end(str));
        cout << str << endl;
        str += "\n";

        const auto resource = srook::make_unique_resource(srook::process::popen("gnuplot", "w"), resource_closer());

        std::string file_type;
        copy(next(begin(file_), file_.find(".") + 1), end(file_), back_inserter(file_type));
        const std::string first_cmd = "set terminal "s + file_type + "\n"s;
        const std::string second_cmd = "set output \""s + std::string(file_.data()) + "\"\n"s;

        fputs(first_cmd.c_str(), resource.get());
        fputs(second_cmd.c_str(), resource.get());
        fputs(str.c_str(), resource.get());
    }

    void output(const char* plt_command)
    {
        using namespace std;
        using namespace std::string_literals;

        const auto resource = srook::make_unique_resource(srook::process::popen("gnuplot", "w"), resource_closer());

        std::string file_type, plt_cmd = plt_command;
        plt_cmd += "\n";

        copy(next(begin(file_), file_.find(".") + 1), end(file_), back_inserter(file_type));
        std::string first_cmd = "set terminal "s + file_type + "\n"s;
        std::string second_cmd = "set output \""s + std::string(file_.data()) + "\"\n"s;

        fputs(first_cmd.c_str(), resource.get());
        fputs(second_cmd.c_str(), resource.get());
        fputs(plt_cmd.c_str(), resource.get());
    }

private:
    struct resource_closer {
        void operator()(FILE* fp) const
        {
            std::fflush(fp);
            srook::process::pclose(fp);
        }
    };
    const srook::string_view file_;
};

SROOK_INLINE_NAMESPACE_END
} // namespace gnu
} // namespace plot
} // namespace srook

#endif

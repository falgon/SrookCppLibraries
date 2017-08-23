// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_PLOT_GNU_PLOTER_HPP
#define INCLUDED_SROOK_PLOT_GNU_PLOTER_HPP

#include <cstdio>
#include <fstream>
#include <srook/algorithm/for_each.hpp>
#include <stdexcept>
#include <string>
#include <string_view>

namespace srook {
namespace plot {
namespace gnu {

struct ploter {
    constexpr ploter(const char *file) : file_(file) {}

    void output(const std::size_t index_size) noexcept(false)
    {
	using namespace std::string_literals;

	std::string str = "plot \"" + std::string(file_) + "\"";
	for (std::size_t i = 0; i < index_size; ++i) {
	    str += " index " + std::to_string(i) + ", \"" + std::string(file_) + "\"";
	}
	str.erase(std::next(std::end(str),-file_.size()-4),std::end(str));
	std::cout << str << std::endl;
	str += "\n";

	std::FILE *fp = popen("gnuplot", "w");
	if (fp == nullptr) throw std::runtime_error("could not start gnuplot properly");
	
	std::string file_type;
	std::copy(std::next(std::begin(file_), file_.find(".") + 1), std::end(file_), std::back_inserter(file_type));
	const std::string first_cmd = "set terminal "s + file_type + "\n"s;
	const std::string second_cmd = "set output \""s + std::string(file_.data()) + "\"\n"s;

	std::fputs(first_cmd.c_str(), fp);
	std::fputs(second_cmd.c_str(), fp);
	std::fputs(str.c_str(), fp);

	std::fflush(fp);
	pclose(fp);
    }

    void output(const char *plt_command) noexcept(false)
    {
	using namespace std::string_literals;

	std::FILE *fp = popen("gnuplot", "w");
	if (fp == nullptr) throw std::runtime_error("could not start gnuplot properly");
	std::string file_type, plt_cmd = plt_command;
	plt_cmd += "\n";

	std::copy(std::next(std::begin(file_), file_.find(".") + 1), std::end(file_), std::back_inserter(file_type));
	std::string first_cmd = "set terminal "s + file_type + "\n"s;
	std::string second_cmd = "set output \""s + std::string(file_.data()) + "\"\n"s;

	std::fputs(first_cmd.c_str(), fp);
	std::fputs(second_cmd.c_str(), fp);
	std::fputs(plt_cmd.c_str(), fp);

	std::fflush(fp);
	pclose(fp);
    }

private:
    const std::string_view file_;
};

} // namespace gnu
} // namespace plot
} // namespace srook

#endif

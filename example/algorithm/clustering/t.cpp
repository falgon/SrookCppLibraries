// Copyright (C) 2017 roki
#include <srook/algorithm/clustering/k_means.hpp>
#include <srook/plot/gnu/ploter.hpp>

int main()
{
    srook::clustering::k_means km("sample_dataset/mouse_data.txt", 3);
    km.clustering();

    const char *result = "result";
    std::ofstream ofs(result);
    ofs << km;

    using namespace std::string_literals;

    srook::plot::gnu::ploter pl("output.png");
    std::string cmd = "plot \""s + result + "\" index 0,\"\" index 1,\"\" index 2";
    try {
	pl.output(cmd.c_str());
    } catch (...) {
    }
}

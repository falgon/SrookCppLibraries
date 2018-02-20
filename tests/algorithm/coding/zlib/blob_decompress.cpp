#include <srook/algorithm/coding/zlib.hpp>
#include <iostream>

void decompress(std::istream& is, std::ostream& os)
{
    constexpr std::streamsize buffer_size = 1 << 16;
    auto buffer = std::make_unique<char[]>(buffer_size);

    while (is.get() != '\0'); // skip header: "<blob> <contents_size><\0><contents...>"
    while (true) {
        is.read(buffer.get(), buffer_size);
        std::streamsize c = is.gcount();
        if (!c) break;
        os.write(buffer.get(), c);
    }
}

int main(const int argc, const char* const* const argv)
{
    if (argc < 2) return EXIT_FAILURE;

    try {
        srook::algorithm::zlib::ifstream ifs(argv[1]);
        decompress(ifs, std::cout);
    } catch (const std::exception& ex) {
        std::cerr << ex.what() << std::endl;
    }
}

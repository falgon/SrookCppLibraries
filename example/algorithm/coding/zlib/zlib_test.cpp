#include <boost/program_options.hpp>
#include <boost/range/algorithm/copy.hpp>
#include <boost/range/adaptor/transformed.hpp>
#include <boost/iterator/zip_iterator.hpp>
#include <srook/range/adaptor/copied.hpp>
#include <srook/algorithm/coding/zlib.hpp>
#include <srook/optional.hpp>
#include <srook/expected.hpp>
#include <vector>
#include <string>

class program_options {
public:
    program_options(int ac, const char* const* const av)
        : description_("Allowed options"), ac_(srook::move(ac)), av_(av) 
    {
        description_.add_options()
            ("help,h", "help")
            ("compress,c", boost::program_options::value<int>()->default_value(6), "compressing")
            ("decompress,d", "uncompress files")
            ("in,i", boost::program_options::value<std::vector<std::string>>(), "set input files. if you not set this flags, it will read from stdin")
            ("out,o", boost::program_options::value<std::vector<std::string>>(), "set name of output. if you not set this flags, it will output the file that added suffix `_out`");
    }

    void store()
    {
        boost::program_options::store(boost::program_options::parse_command_line(ac_, av_, description_), vm_);
        boost::program_options::notify(vm_);
    }

    const boost::program_options::variable_value& operator[](const char* key) const
    SROOK_NOEXCEPT(srook::declval<boost::program_options::variables_map>()[const char*()])
    { return vm_[key]; }

    const boost::program_options::variables_map* operator->() const SROOK_NOEXCEPT_TRUE
    { return srook::addressof(vm_); }

    const boost::program_options::options_description& description() const SROOK_NOEXCEPT_TRUE
    { return description_; }

private:
    boost::program_options::options_description description_;
    boost::program_options::variables_map vm_;
    const int ac_;
    const char* const* const av_;
};

srook::optional<std::vector<std::string>> make_filelist(const char* key, const program_options& opt)
{
    if (opt->count(key)) return { opt[key].as<std::vector<std::string>>() };
    return {};
}

srook::algorithm::zlib::compress_level narrowing_level(int level)
{
    if (level > Z_BEST_COMPRESSION) return srook::algorithm::zlib::compress_level::best;
    if (level < Z_NO_COMPRESSION) return srook::algorithm::zlib::compress_level::none;
    return static_cast<srook::algorithm::zlib::compress_level>(level);
}

void cat_stream(std::istream& is, std::ostream& os)
{
    const std::streamsize buff_size = 1 << 16;
    auto buffer = std::make_unique<char[]>(buff_size);
    while (true) {
        is.read(buffer.get(), buff_size);
        std::streamsize c = is.gcount();
        if (!c) break;
        os.write(buffer.get(), c);
    }
}

void compress(int level, const std::vector<std::string>& in_file, const std::vector<std::string>& out_file)
{
    auto begin = boost::make_zip_iterator(boost::make_tuple(std::begin(in_file), std::begin(out_file)));
    auto end = boost::make_zip_iterator(boost::make_tuple(std::end(in_file), std::end(out_file)));
    std::for_each(begin, end, [&level](auto&& t) {
            srook::io::ifstream ifs(t.template get<0>());
            srook::algorithm::zlib::ofstream ofs(t.template get<1>(), narrowing_level(level));
            cat_stream(ifs, ofs);
    });
}

void compress(int level, const std::vector<std::string>& out_file)
{
    for (auto&& o : out_file) {
        srook::algorithm::zlib::ofstream ofs(srook::forward<SROOK_DECLTYPE(o)>(o), narrowing_level(level));
        cat_stream(std::cin, ofs);
    }
}

void compress(int level)
{
    srook::algorithm::zlib::ostream os(std::cout, narrowing_level(srook::move(level)));
    cat_stream(std::cin, os);
}

void decompress(const std::vector<std::string>& in_file, const std::vector<std::string>& out_file)
{
    auto begin = boost::make_zip_iterator(boost::make_tuple(std::begin(in_file), std::begin(out_file)));
    auto end = boost::make_zip_iterator(boost::make_tuple(std::end(in_file), std::end(out_file)));
    std::for_each(begin, end, [](auto&& t) {
            srook::algorithm::zlib::ifstream ifs(t.template get<0>());
            srook::io::ofstream ofs(t.template get<1>());
            cat_stream(ifs, ofs);
    });
}

std::vector<std::string> addsuffix_out(const std::vector<std::string>& s)
{
    std::vector<std::string> r = s | boost::adaptors::transformed([](const std::string& s){ return s + "_out"; }) | srook::adaptors::copied;
    return r;
}

int main(int ac, const char* const* const av) try
{
    program_options opt(srook::move(ac), av);
    opt.store();

    if (opt->count("help")) {
        std::cout << opt.description() << std::endl;
        return EXIT_SUCCESS;
    }

    srook::optional<std::vector<std::string>> in_file(make_filelist("in", opt)), out_file(make_filelist("out", opt));
    if (opt->count("compress")) {
        int lv = opt["compress"].as<int>();
        if (in_file && !out_file) {
            compress(srook::move(lv), srook::move(*in_file), addsuffix_out(*in_file));
        } else if (in_file && out_file) {
            compress(srook::move(lv), srook::move(in_file.value()), srook::move(out_file.value()));
        } else if (!in_file && out_file) {
            compress(srook::move(lv), srook::move(out_file.value()));
        } else {
            compress(srook::move(lv));
        }
    }

    if (opt->count("decompress")) {
        if (in_file && !out_file) {
            decompress(srook::move(*in_file), addsuffix_out(*in_file));
        } else if (in_file && out_file) {
            decompress(srook::move(*in_file), srook::move(*out_file));
        } 
    }
} catch (const std::exception& ex) {
    std::cerr << ex.what() << std::endl;
}

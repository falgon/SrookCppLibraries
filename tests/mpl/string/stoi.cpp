#include <srook/mpl/string/stoi.hpp>

int main()
{
    typedef srook::string::stoi<'0', 'x', '3', '5'> hex_type;
    typedef srook::string::stoi<'5', '3'> dec_type;
    typedef srook::string::stoi<'0', '6', '5'> oc_type;
    SROOK_CONSTEXPR int v = 53;

    SROOK_ST_ASSERT(hex_type::value == v);
    SROOK_ST_ASSERT(dec_type::value == v);
    SROOK_ST_ASSERT(oc_type::value == v);

    typedef srook::string::stoi<' ', ' ', '0', 'x', '3', '5'> hex_space_type;
    typedef srook::string::stoi<' ', ' ', '5', '3'> dec_space_type;
    typedef srook::string::stoi<' ', ' ', '0', '6', '5'> oc_space_type;

    SROOK_ST_ASSERT(hex_space_type::value == v);
    SROOK_ST_ASSERT(dec_space_type::value == v);
    SROOK_ST_ASSERT(oc_space_type::value == v);
}

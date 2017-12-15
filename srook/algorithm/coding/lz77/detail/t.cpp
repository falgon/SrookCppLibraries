#include "compress.hpp"
#include <iostream>

int main()
{
    std::string s = "012340123012340123012340123";
 
    std::cout << s << std::endl;
    std::string en = srook::algorithm::encoding::lz77::detail::compress(s, 16, 100);
    std::cout << en << std::endl;

    auto r = srook::algorithm::encoding::lz77::detail::decompress(en);
    std::cout << r.value_or("error") << std::endl;
}

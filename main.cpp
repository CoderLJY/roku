#include <iostream>
#include "BufferTunnel.h"
#include "unicode_conv.h"

int main() {

    std::string test{"test"};
    roku::BufferTunnel<std::string, std::string> tunnel{test};

    std::u32string u32String{};
    if (roku::unicode::ConvU8ToU32(test, u32String))
        for (const char32_t &c : u32String)
            std::wcout << static_cast<wchar_t >(c) << std::endl;


//    auto i = test.begin();
//    while (i != test.end())
//        std::cout << *(++i) << std::endl;
//    auto it = tunnel.begin();
//    while (it != tunnel.end())
//        std::cout << it++ << std::endl;
}

#include <iostream>
#include "BufferTunnel.h"
#include "unicode_conv.h"

int main() {

    std::string test{"   \n \t   ++ -- test"};
    roku::BufferTunnel<std::string, std::string> tunnel{test};

    std::u32string u32String{};
    if (roku::unicode::ConvU8ToU32(test, u32String)) {
        std::vector<std::string> ngram_str = roku::utils::get_ngram_groups(u32String, 2);
    }


}

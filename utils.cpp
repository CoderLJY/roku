//
// Created by jianyuelin on 12/18/2020.
//
#include <codecvt>
#include "utils.h"
#include "unicode_conv.h"

int roku::utils::wiser_is_ignored_char(const char32_t ustr) {
    switch (ustr) {
        case ' ':
        case '\f':
        case '\n':
        case '\r':
        case '\t':
        case '\v':
        case '!':
        case '"':
        case '#':
        case '$':
        case '%':
        case '&':
        case '\'':
        case '(':
        case ')':
        case '*':
        case '+':
        case ',':
        case '-':
        case '.':
        case '/':
        case ':':
        case ';':
        case '<':
        case '=':
        case '>':
        case '?':
        case '@':
        case '[':
        case '\\':
        case ']':
        case '^':
        case '_':
        case '`':
        case '{':
        case '|':
        case '}':
        case '~':
        case 0x3000: /* 全角空格 */
        case 0x3001: /* 、 */
        case 0x3002: /* 。 */
        case 0xFF08: /* （ */
        case 0xFF09: /* ） */
        case 0xFF01: /* ！ */
        case 0xFF0C: /* ， */
        case 0xFF1A: /* ： */
        case 0xFF1B: /* ； */
        case 0xFF1F: /* ? */
            return 1;
        default:
            return 0;
    }
}


int roku::utils::ngram_next(const char32_t *ustr, const char32_t *ustr_end,
                            unsigned int n, const char32_t **start) {
    int i;
    const char32_t *p;

    /* 读取时跳过文本开头的空格等字符 */
    for (; ustr < ustr_end && wiser_is_ignored_char(*ustr); ustr++) {
    }

    /* 不断取出最多包含n个字符的词元，直到遇到不属于索引对象的字符或到达了字符串的尾部 */
    for (i = 0, p = ustr; i < n && p < ustr_end
                          && !wiser_is_ignored_char(*p); i++, p++) {
    }

    *start = ustr;
    return p - ustr;
}


std::vector<std::string> roku::utils::get_ngram_groups(const std::u32string &str, unsigned int n) {
    std::vector<std::string> ngram_groups{};
    for (auto it = str.begin(); it != str.end(); ++it) {
        if (wiser_is_ignored_char(*it))
            continue;

        std::array<char, 4> u8char;
        roku::unicode::ConvChU32ToU8(*it, u8char);


        std::array<char, 4> u8char2;
        auto forward_it = it;
        ++forward_it;
        roku::unicode::ConvChU32ToU8(*forward_it, u8char2);

        ngram_groups.push_back(std::string{u8char.data()} + std::string{u8char2.data()});
    }

    return ngram_groups;
}

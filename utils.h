//
// Created by jianyuelin on 12/17/2020.
//

#ifndef ROKU_UTILS_H
#define ROKU_UTILS_H

#include <locale>
#include <functional>

namespace roku::utils {

    template<typename Callable>
    using return_type_of_t =
    typename decltype(std::function{std::declval<Callable>()})::result_type;

    template<typename T>
    concept HasCtyleStr = requires(T t)
    {
        std::is_same<decltype(&std::string::c_str), decltype(t.c_str())>::value;
        std::is_same<decltype(&std::string::length), decltype(t.length())>::value;
    };

    /**
    * 检查输入的字符（UTF-32）是否不属于索引对象
    * @param[in] ustr 输入的字符（UTF-32）
    * @return 是否是空白字符
    * @retval 0 不是空白字符
    * @retval 1 是空白字符
    */
    int wiser_is_ignored_char(const char32_t ustr);

    /**
    * 将输入的字符串分割为N-gram
    * @param[in] ustr 输入的字符串（UTF-8）
    * @param[in] ustr_end 输入的字符串中最后一个字符的位置
    * @param[in] n N-gram中N的取值。建议将其设为大于1的值
    * @param[out] start 词元的起始位置
    * @return 分割出来的词元的长度
    */
    int ngram_next(const char32_t *ustr, const char32_t *ustr_end,
                   unsigned int n, const char32_t **start);

    void loop_utf32(std::u32string &u32str, std::function<void(char32_t)> func);

}
#endif //ROKU_UTILS_H

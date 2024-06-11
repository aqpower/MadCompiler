#ifndef LEXER_HPP
#define LEXER_HPP

#include <string>

/**
 * @brief 分析源代码并构建符号表,支持识别各种单词，不检测句子的正确性。
 *
 * @param code 输入源代码
 */
void analyze(const std::string &code);

/**
 * @brief 读取输入文件内容
 *
 * @param path 文件路径
 * @return 返回文件内容的字符串
 */
std::string readInput(const std::string &path);

#endif // LEXER_HPP

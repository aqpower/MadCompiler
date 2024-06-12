#ifndef INTERMEDIATE_CODE_GENERATOR_H
#define INTERMEDIATE_CODE_GENERATOR_H

#include "ast.hpp"
#include <vector>
#include <string>

namespace Compiler {

class IntermediateCodeGenerator {
  public:
    std::vector<std::string> generate(const std::unique_ptr<ASTNode> &root);

  private:
    void generateCode(const std::unique_ptr<ASTNode> &node, std::vector<std::string> &code);
    // 其他中间代码生成相关的私有成员函数
};

} // namespace Compiler

#endif // INTERMEDIATE_CODE_GENERATOR_H

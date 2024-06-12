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
};

} // namespace Compiler

#endif // INTERMEDIATE_CODE_GENERATOR_H

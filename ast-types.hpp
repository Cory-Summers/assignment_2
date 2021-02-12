#ifndef AST_TYPES_HPP
#define AST_TYPES_HPP
#include <cstdint>
namespace ast
{
  enum class VariableType    { kUndefined = -1, kInt = 1, kChar = 2, kBool = 3};
  enum class IdentifierType  { kUndefined = -1, kVariable = 1, kFunction = 2, kParameter = 3};
  enum class ScopeType       { kUndefined = -1, kGlobal = 1, kFunction = 2, kParameter = 3, kLocal = 4, kBlock = 5 };

}
#endif //AST_TYPES_HPP
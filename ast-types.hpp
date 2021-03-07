#ifndef AST_TYPES_HPP
#define AST_TYPES_HPP
#include <cstdint>
#include <string>
namespace ast
{
  enum class VariableType
  {
    kUndefined = -1,
    kVoid = 0,
    kInt = 1,
    kChar = 2,
    kBool = 3
  };
  enum class IdentifierType
  {
    kUndefined = -1,
    kVariable = 1,
    kFunction = 2,
    kParameter = 3
  };
  enum class ScopeType
  {
    kUndefined = -1,
    kGlobal = 1,
    kFunction = 2,
    kParameter = 3,
    kLocal = 4,
    kBlock = 5
  };
  enum class ExpressionType
  {
    kNoOperation = -1,
    kConstant = 0,
    kCall = 1,
    kOperation = 2,
    kUnary = 3,
    kCompound = 4,
    kBreak = 5,
    kReturn,
    kFor,
    kRange,
    kWhile,
    kIf,
    kBranch
  };
  enum class BranchType
  {
    kUndefined = -1,
  };
  enum class OperationType
  {
    kNoOp = -1,
    kMinus = 0,
    kMulti = 1,
    kGenerator,
    kDiv,
    kModulo,
    kLOr,
    kLNot,
    kLAnd,
    kAdd,
    kMin,
    kMax,
    kLesEq,
    kLess,
    kGreat,
    kGreEq,
    kEqualive,
    kNEqualive,
    kBrack,
    kAssign = 0x100,
    kAddAss = 0x101,
    kMinAss,
    kMulAss,
    kDivAss,
    kIncrement,
    kDecrement
  };
  inline std::string ExpressionTypeStr(ExpressionType t)
  {
    const char * k_exp_cstr[] = {"", "", "", "", "", "", "Break", "Return", "For", "Range", "While", "If" };
    return k_exp_cstr[std::size_t(t) + 1];
  }
  inline std::string VariableTypeStr(VariableType t)
  {
    const char* k_id_cstr[] = {"undefined", "void", "int", "char", "bool" };
    return k_id_cstr[std::size_t(t) + 1];
  }
  inline std::string UnaryTypeStr(OperationType t)
  {
    const char * k_op_cstr[] = {"undefined", "CHSIGN", "SIZEOF", "?"};
    return k_op_cstr[std::size_t(t) + 1];
  }
  inline std::string OperationTypeStr(OperationType t)
  {
    const char * k_op_cstr[] = 
    {
      "undefined", "-", "*", "?", "/", "%", "OR", "NOT", "AND", "+", 
      ":<:", ":>:", "<=", "<", ">", ">=", "==", "!=", "["
    };
    const char * k_assign_cstr[] = 
    {
      "=", "+=", "-=", "*=", "/=", "++", "--"
    };
    if(t >= OperationType::kAssign)
    {
      return k_assign_cstr[std::size_t(t) - std::size_t(OperationType::kAssign)];
    }
    return k_op_cstr[std::size_t(t) + 1]; 
  }
} // namespace ast
#endif //AST_TYPES_HPP
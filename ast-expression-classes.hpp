#ifndef AST_EXPRESSION_CLASSES_HPP
#define AST_EXPRESSION_CLASSES_HPP
#include "ast-node-classes.hpp"
#include "ast-identifier-classes.hpp"
namespace ast
{
  class Expression : public INode
  {
    public:
    Expression() {}
    Expression(ExpressionType type) : m_exp_type(type) { m_form = Form::Expression;}
    Expression(ExpressionType type, parser::location const & loc )
    : m_exp_type(type)
    {
      m_form = Form::Expression;
      m_pos  = loc;
    }
    Expression(scanner::Token const & token, ExpressionType type = ExpressionType::kNoOperation) 
      : m_exp_type(type)
    { 
      m_form = Form::Expression; 
      m_pos = token.pos;
    }
    virtual string_type ToString() { return ExpressionTypeStr(m_exp_type) + " " + GetLine(); }
  protected:
    ExpressionType m_exp_type;
  };
  class ConstantExpr : public Expression
  {
    public:
    ConstantExpr(scanner::Token const & token)
      : Expression(token, ExpressionType::kConstant)
      {
        m_token = token;
      } 
    virtual string_type ToString()
    {
      string_type temp = "Const ";
      if(m_token.type == scanner::Token::Type::kString)
      {
        temp += "is array ";
      }
      temp += "of type " + scanner::Token::TypeToString(m_token) + ": ";
      switch(m_token.type)
      {
        case scanner::Token::Type::kString:
          temp += "\"" + m_token.string_value + "\"";
          break;
        case scanner::Token::Type::kChar:
          temp += "\'";
          temp.push_back(m_token.char_value);
          temp += "\'";
          break;
        case scanner::Token::Type::kNumeric:
          temp += std::to_string(m_token.num_value);
          break;
        case scanner::Token::Type::kBoolean:
        case scanner::Token::Type::kIdentifier:
          temp += m_token.token_string;
          break;
      }
      temp += ' ' + GetLine();
      return temp;
    }
    protected:
    scanner::Token m_token;
  };
  //Seperate type because I believe it will be important during language impl
  class CallExpression : public Expression
  {
    public:
      CallExpression(scanner::Token const & token, void * _reserved = nullptr)//Reserved for symbol table
        : Expression(token, ExpressionType::kCall)
      {
        m_name = token.token_string;
      } 
      virtual string_type ToString() override
      {
        string_type temp = "Call: " + m_name + " " + GetLine();
        return temp;
      }
      // [TODO] Include link to symbol table at later time
    private:
      string_type m_name;
  };
  //Seperate type due to scoping
  class CompoundExpr : public Expression
  {
    public:
      CompoundExpr(parser::location const & pos)
        : Expression(ExpressionType::kCompound, pos)
      {
        
      }
      virtual string_type ToString() override { return string_type("Compound ") + GetLine(); }
    private:
  };
  class OperationExpr : public Expression
  {
    public:
      OperationExpr(parser::location const & pos, OperationType type = OperationType::kNoOp) 
      : Expression(ExpressionType::kOperation, pos) 
      { m_oper_type = type; }
    virtual string_type ToString() override
    {
      string_type temp;
      if(m_oper_type >= OperationType::kAssign)
        temp = "Assign: ";
      else 
        temp = "Op: ";
      temp += OperationTypeStr(m_oper_type) + " " + GetLine();
      return temp;
    }
    protected:
      OperationType m_oper_type;
  };
  //This class has been written while tipsy, i'm pretty sure the purpose is so when called for the AST
  //that not just the fact of different printed string, that during code impl that it will have a different action
  class UnaryExpr : public OperationExpr
  {
    public:
      UnaryExpr(ast::OperationType type, parser::location const & pos)
        : OperationExpr(pos, type) 
      {
        m_exp_type = ExpressionType::kUnary;
      }
      virtual string_type ToString()
      {
        string_type temp = "Op: " + UnaryTypeStr(m_oper_type) + " " + GetLine();
        return temp;
      }
  };
  class BranchExpr : public Expression
  {
    public:
      BranchExpr(BranchType const type, parser::location const & loc)
        : Expression(ExpressionType::kBranch, loc)
        {
          m_branch_type = type;
        }
    protected:
      BranchType m_branch_type;
  };
}
#endif //AST_EXPRESSION_CLASSES_HPP
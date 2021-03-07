#ifndef ABSTRACT_SYNTAX_TREE_HPP
#define ABSTRACT_SYNTAX_TREE_HPP
#include <iostream>
#include <functional>
#include <initializer_list>
#include <type_traits>
#include "ast-tree-class.hpp"
#include "ast-node-classes.hpp"
#include "ast-types.hpp"
namespace scanner
{
  class Token;
}
namespace ast
{
  using node_pointer = std::shared_ptr<ast::INode>;
  using init_list = std::initializer_list<node_pointer>;
  namespace action
  {
    node_pointer & AddToTail(node_pointer &, node_pointer &);
    //Decl
    node_pointer  DeclList(node_pointer & lhs, node_pointer & rhs);
    //Variables
    node_pointer & VariableDecl(ast::VariableType type, node_pointer &head);
    node_pointer & VariableDeclList(node_pointer & head, node_pointer & tail);
    node_pointer & StaticDecl(ast::VariableType type, node_pointer & head);
    //Fuctions
    node_pointer   FunctionDecl(ast::VariableType type, scanner::Token const & token, node_pointer & parameters, node_pointer  expression = node_pointer());
    node_pointer & ParameterType(ast::VariableType type, node_pointer & head);
    node_pointer   ParameterID(scanner::Token const &, bool);
    //Expressions
    node_pointer   ImmuteConstant(scanner::Token const &);
    node_pointer & ArgumentList(node_pointer & head, node_pointer & tail);
    node_pointer   CallExpr(scanner::Token const & token, node_pointer & args);
    node_pointer   UnaryExpr(OperationType type, node_pointer & rhs, parser::location &);
    node_pointer   CompoundStmt(node_pointer & local_decl, node_pointer & stmt_list, parser::location const &);
    node_pointer   BracketOper(scanner::Token const &, node_pointer &);
    node_pointer   OrExpression(node_pointer &, node_pointer &, parser::location const & loc);
    //Impl
    template<typename T, typename ... TArgs>
    std::enable_if_t<std::is_base_of<Expression, T>::value, node_pointer> GenericExpression(
      init_list c_init_list, 
      TArgs && ...  args)
      {
        node_pointer temp = std::make_shared<T>(std::forward<TArgs>(args)...);
        for(auto & it : c_init_list)
        {
          temp->AddChild(it);
        }
        return temp;
      }
  }
  namespace debug
  {
    inline void test(node_pointer & lhs, node_pointer &rhs)
    {
      std::cout << static_cast<ast::VariableDecl *>(lhs.get())->GetName() << " -> "<<
       static_cast<ast::VariableDecl *>(rhs.get())->GetName() << '\n';
    }
  }
} // namespace ast
#endif //ABSTRACT_SYNTAX_TREE_HPP

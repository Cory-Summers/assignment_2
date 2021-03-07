#include "abstract-syntax-tree.hpp"
#include "scanner-token.hpp"
namespace ast
{
  namespace action
  {
    
    node_pointer & AddToTail(node_pointer &head, node_pointer & tail)
    {
      auto it = head;
      if(!head)
        return tail;
      while(it->GetSibling())
      {
        it = it->GetSibling();
      } 
      it->SetSibling(tail);
      return head;
    }
    node_pointer DeclList(node_pointer & lhs, node_pointer & rhs)
    {
      auto it = rhs;
      lhs->SetSibling(rhs);
      while(it->GetSibling())
      {
        it = it->GetSibling();
      }
      return it;

    }
    node_pointer &VariableDecl(ast::VariableType type, node_pointer &head)
    {
      static_cast<ast::VariableDecl *>(head.get())->SetVariableType(type);
      for (auto& it : *head){
        static_cast<ast::VariableDecl *>(&it)->SetVariableType(type);
      }
      return head;
    }
    node_pointer &StaticDecl(ast::VariableType type, node_pointer &head)
    {
      auto it = head;
      while(it)
      {
        static_cast<ast::VariableDecl *>(it.get())->SetVariableType(type);
        static_cast<ast::VariableDecl *>(it.get())->SetAsStatic(true);
        it = it->GetSibling();
      }
      return head;
    }
    node_pointer FunctionDecl(
        ast::VariableType type,
        scanner::Token const &token,
        node_pointer & parameters,
        node_pointer   expression)
    {
      node_pointer func = std::make_shared<ast::Function>(token, type);
      if(parameters)
        func->AddChild(parameters);
      if(expression)
        func->AddChild(expression);
      return func;
    }
    node_pointer & ParameterType(ast::VariableType type, node_pointer & head)
    {
      static_cast<ast::VariableDecl *>(head.get())->SetVariableType(type);
      static_cast<ast::VariableDecl *>(head.get())->SetAsParam(true);
      for (auto &it : *head){
        static_cast<ast::VariableDecl *>(&it)->SetVariableType(type);
        static_cast<ast::VariableDecl *>(&it)->SetAsParam(true);
      }
      return head;
    }
    node_pointer ParameterID(scanner::Token const & token, bool arr)
    {
      auto temp = std::make_shared<ast::VariableDecl>(token);
      temp->SetAsArray(arr);
      temp->SetAsParam(true);
      return temp;
    }
    node_pointer ImmuteConstant(scanner::Token const & token)
    {
      auto temp = std::make_shared<ConstantExpr>(token);
      return temp;
    }
    node_pointer   CallExpr(scanner::Token const & token, node_pointer & args)
    {
      auto temp = std::make_shared<ast::CallExpression>(token);
      if(args)
        temp->AddChild(args);
      return temp;
    }
    node_pointer UnaryExpr(OperationType type, node_pointer & rhs, parser::location & loc)
    {
      auto temp = std::make_shared<ast::UnaryExpr>(type, loc);
      temp->AddChild(rhs);
      return temp;
    }
    node_pointer   CompoundStmt(node_pointer & local_decl, node_pointer & stmt_list, parser::location const & loc)
    {
      auto temp = std::make_shared<ast::CompoundExpr>(loc);
      if(local_decl)
        temp->AddChild(local_decl);
      if(stmt_list)
        temp->AddChild(stmt_list);
      return temp;
    }
    node_pointer   BracketOper(scanner::Token const & tok, node_pointer & node)
    {
      
      return node;
    }

    //Expressions
    node_pointer   OrExpression(node_pointer &lhs , node_pointer & rhs, parser::location const & loc)
    {
      auto temp = std::make_shared<ast::OperationExpr>(loc, OperationType::kLOr);
      temp->AddChild(lhs);
      temp->AddChild(rhs);
      return temp;
    }
  } // namespace action
} // namespace ast
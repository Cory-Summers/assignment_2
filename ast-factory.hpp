#ifndef AST_FACTORY_HPP
#define AST_FACTORY_HPP
#include "ast-node-classes.hpp"
namespace ast
{
  using node_ident = std::shared_ptr<ast::Identifier>;

  node_ident IdentifierFactory();
}
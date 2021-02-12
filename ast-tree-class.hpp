#ifndef AST_TREE_CLASS
#define AST_TREE_CLASS
#include <iostream>
#include <map>
#include <memory>
#include <vector>
#include "ast-node-classes.hpp"
#include "ast-symbol-table.hpp"
namespace ast
{
  class Tree
  {
    public:
      using node_pointer = std::unique_ptr<INode>;
      using string_type  = std::string;
      using map_type     = std::map<string_type, Identifier *>;
    public:
    Tree();
    void Print(std::ostream & = std::cout);
    private:
      map_type  m_functions;
      node_pointer m_node_head; //Its a hydra okay.
      SymbolTable  m_symbol_head;
  };
}
#endif//AST_TREE_CLASS
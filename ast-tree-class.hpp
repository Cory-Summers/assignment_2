#ifndef AST_TREE_CLASS
#define AST_TREE_CLASS
#include <iostream>
#include <map>
#include <memory>
#include <vector>
#include "ast-node-classes.hpp"
#include "ast-symbol-table.hpp"
#include "ast-expression-classes.hpp"
namespace ast
{
  class Tree
  {
    public:
      using node_pointer = std::shared_ptr<INode>;
      using string_type  = std::string;
    public:
    Tree();
    void Print(std::ostream & = std::cout);
    INode * GetCurrent() { return m_current; }
    INode * SetCurrent(INode * node) { m_current = node; return node; }
    void    SetHead(node_pointer & node) { m_node_head = node; m_current = node.get(); }
    node_pointer GetHead() { return m_node_head; }
    private:
      void RecursivePrint(INode * current, string_type &, std::size_t idx, std::size_t depth, std::ostream &);
      void SiblingPrint(INode * current, string_type &, std::size_t idx, std::size_t depth, std::ostream &);
      void PrintIndent(std::size_t const & n, std::ostream &);
      INode *   m_current;
      node_pointer m_node_head; 
      //SymbolTable  m_symbol_head;
  };
}
#endif//AST_TREE_CLASS
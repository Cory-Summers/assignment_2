#include "ast-tree-class.hpp"
constexpr char DepthIndent[] = ".   ";
ast::Tree::Tree()
  : m_node_head()
  //, m_symbol_head()
{
}
void ast::Tree::Print(std::ostream & stream)
{
  INode * node;
  std::string str;
  node = m_node_head.get();
  if(node != nullptr)
    RecursivePrint(node, str, 0, kGlobalScopeDepth, stream);
}
//The string reference is hopefully optimize out RAII overhead from creating a new string obj everytime
void ast::Tree::RecursivePrint(INode * current, string_type & str, std::size_t idx, std::size_t depth, std::ostream & stream)
{
  INode * temp;
  const std::size_t num_of_children = current->NumOfChildren();
  PrintIndent(depth, stream);
  stream << str << current->ToString() << '\n';
  std::size_t sib_idx = 1;
  for(std::size_t i = 0; i < num_of_children; ++i)
  {
    temp = current->GetChild(i);
    str = "Child: " + std::to_string(i) + "  ";
    RecursivePrint(temp, str, i, depth + 1, stream);
    
  }
  for(auto & sib : *current)
  {
    str = "Sibling: " + std::to_string(sib_idx) + "  ";
   SiblingPrint(&sib, str, sib_idx++, depth, stream);
  }
}
void ast::Tree::SiblingPrint(INode * current, string_type & str, std::size_t idx, std::size_t depth, std::ostream & stream)
{
  INode * temp;
  const std::size_t num_of_children = current->NumOfChildren();
  PrintIndent(depth, stream);
  stream << str << current->ToString() << '\n';
  for(std::size_t i = 0; i < num_of_children; ++i)
  {
    temp = current->GetChild(i);
    str = "Child: " + std::to_string(i) + "  ";
    RecursivePrint(temp, str, i, depth + 1, stream);
  }
}
void ast::Tree::PrintIndent(std::size_t const & n, std::ostream & stream)
{
  for(size_t i = 0; i < n; ++i)
  {
    stream << DepthIndent;
  }
}
#include "symbol-table-class.hpp"

// table_type  m_table;
// depth_type  m_depth;
// scope_type  m_scope_type;
// string_type m_scope_string;
// //Weakptr to prevent circular references
// std::weak_ptr<SymbolTable> m_parent;
// child_vector m_children;
SymbolTable::SymbolTable()
    : m_table(), m_depth(0), m_scope_type(scope_type::kGlobal), m_scope_string("_EMPTYNAME"), m_parent(), m_children()
{
}
SymbolTable::SymbolTable(
    scope_type const &type,
    string_type const &scope_name,
    depth_type const &depth = 0,
    std::weak_ptr<SymbolTable> &parent = std::weak_ptr<SymbolTable>())
    : m_table(), m_depth(depth), m_scope_type(type), m_scope_string(), m_parent(parent), m_children()
{
  NameMangler(scope_name);
}

void SymbolTable::NameMangler(std::string const &name)
{ auto par = m_parent.lock();
  if(par && m_scope_type != scope_type::kGlobal)
  {
    m_scope_string = par->GetName() + m_depth + name;
    if()
  }
  else 
  {
    m_scope_string = "_" + name; 
  }
}
// iterator Access(std::string const &);
// iterator operator[](std::string const &);

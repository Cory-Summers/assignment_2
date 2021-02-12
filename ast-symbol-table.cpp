#include "ast-symbol-table.hpp"
#include "ast-node-classes.hpp"
#include <exception>
ast::SymbolTable::SymbolTable()
  : m_symbols()
  , m_parent(nullptr)
  , m_child_scopes()
  , m_depth(0)
{

}
ast::Identifier * ast::SymbolTable::operator[](string_cref key)
{
  ast::Identifier * ret = nullptr;
  auto iter = m_symbols.find(key);
  if(iter != m_symbols.end())
  {
    ret = iter->second;
  }
  else if(m_parent != nullptr){
    ret = m_parent->operator[](key);
  }
  return ret;
}
//The usage of references is ensure there is no empty Identifiers used
ast::Identifier&  ast::SymbolTable::insert(string_cref key, Identifier & ident)
{
  ast::Identifier * exists = this->operator[](key);
  if(exists != nullptr)
  {
    throw std::runtime_error(std::string("Symbol \'") + key + std::string("\' already exists."));
  }
  return *(m_symbols.insert({key, &ident}).first->second); //wtf stl
}
ast::SymbolTable & ast::SymbolTable::EmplaceScopeBack()
  {
    auto ptr = std::make_unique<SymbolTable>();
    ptr->m_parent = this;
    ptr->m_depth  = this->m_depth + 1;
    m_child_scopes.push_back(std::move(ptr));
    return *m_child_scopes.back();
  }
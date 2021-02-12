#ifndef SYMBOL_TABLE_CLASS_HPP
#define SYMBOL_TABLE_CLASS_HPP
#include <iostream>
#include <unordered_map>
#include <memory>
#include <string>
#include <vector>
#include "ast-types.hpp"
class SymbolTable
{
  public:
  public:
    using string_type  = std::string;
    using depth_type   = std::size_t;
    using scope_type   = ast::ScopeType;
    using table_type   = std::unordered_map<string_type, struct Symbol>;
    using child_vector = std::vector<std::shared_ptr<SymbolTable>>;
    using iterator     = child_vector::iterator;
    struct Symbol
    {
      string_type         name;
      ast::VariableType   var_type;
      ast::IdentifierType id_type;
      scope_type          scope;
    };
  public:
    SymbolTable();
    SymbolTable(
      scope_type const &, 
      string_type const &, 
      depth_type const & depth = 0,
      std::weak_ptr<SymbolTable> & parent = std::weak_ptr<SymbolTable>()
      );
    iterator Access(std::string const &);
    iterator operator[](std::string const &);

    //Getters
    inline constexpr
    string_type const & GetName() const noexcept { return m_scope_string; }
  private: 
    void NameMangler(std::string const &);
    table_type  m_table;
    depth_type  m_depth;
    scope_type  m_scope_type;
    string_type m_scope_string;
    //Weakptr to prevent circular references
    std::weak_ptr<SymbolTable> m_parent;
    child_vector m_children;
};


#endif //SYMBOL_TABLE_CLASS_HPP

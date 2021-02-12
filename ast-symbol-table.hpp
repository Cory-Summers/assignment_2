#ifndef AST_SYMBOL_TABLE_HPP
#define AST_SYMBOL_TABLE_HPP
#include <map>
#include <string>
#include <vector>
namespace ast
{
  constexpr std::size_t kGlobalScopeDepth = 0;
  class Identifier;
  class SymbolTable
  {
  public:
    using child_pointer = std::unique_ptr<SymbolTable>;
    using string_type = std::string;
    using string_cref = string_type const &;
    using map_type = std::map<string_type, Identifier *>;

  public:
    SymbolTable();
    Identifier *operator[](string_cref);
    Identifier &insert(string_cref, Identifier &);
    SymbolTable & EmplaceScopeBack();
  protected:
    map_type m_symbols;
    SymbolTable *m_parent; //Raw pointer to prevent circular dependance.
    std::vector<child_pointer> m_child_scopes;
    std::size_t m_depth;
  };

} // namespace ast

#endif //AST_SYMBOL_TABLE_HPP
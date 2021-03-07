#ifndef SEMANTIC_ANALYSIS_CLASS_HPP
#define SEMANTIC_ANALYSIS_CLASS_HPP
#include "abstract-syntax-tree.hpp"
#include <iostream>
namespace analysis
{
  struct Message : public ast::ILocation
  {
    public:
      Message() {}
      constexpr
      Message(loc_type const & loc, Type const type, std::string const & what)
        : m_type(type), m_what(what) { m_pos = loc; }
      std::string const & What();
      Type Type() const noexcept { return m_type; }
    protected:
    enum class Type {kUndefined, kMessage, kWarning, kError } m_type;
    std::string m_what;
  };
  class Semantic
  {
    
    using symbol_pointer = std::shared_ptr<ast::SymbolTable>;
    using 
    public:
      Semantic();
      Semantic(ast::Tree *);
      void Initialize(ast::Tree *);
      int Analyze();
      std::size_t const ErrorCount() const noexcept { return m_error_count; }
      std::size_t const WarningCount() const noexcept { return m_warning_count; }
    private:
    void CreateSymbolTable();
      void push_back(Message const &);
      Message & emplace_back(Message::loc_type const &, Message::Type const type, std::string const &);
      ast::Tree *    m_tree_ptr; 
      symbol_pointer m_symbol_head;
      std::vector<Message> m_messages;
      std::size_t m_error_count;
      std::size_t m_warning_count;
  };
}

#endif //SEMANTIC_ANALYSIS_CLASS_HPP
#ifndef AST_NODE_CLASSES_HPP
#define AST_NODE_CLASSES_HPP
#include <memory>
#include <list>
#include <string>
#include <vector>
#include "position.hh"
#include "ast-types.hpp"
#include "scanner-token.hpp"
namespace ast
{
  /* */
  class INode //Node Interface
  {
  public:
    using size_type = std::size_t;
    using pos_type = parser::position;
    enum class Form
    {
      kUndefined,
      Identifier,
      Expression
    };
  public:
    Form GetForm() { return m_form; }
    virtual pos_type GetLocation() { return m_pos; }
    virtual void SetLocation(pos_type const &pos) { m_pos = pos; }
    virtual std::string ToString() { return ""; }
    virtual size_type GetIndex() const noexcept { return m_idx; }
    virtual void SetIndex(size_type const & idx) { m_idx = idx; }
  protected:
    size_type m_idx;
    pos_type m_pos;
    Form m_form;
    std::list<std::shared_ptr<INode>> m_children;
  };

  class Identifier
  {
    public:
    using string_type = std::string;
    using string_cref = string_type const &;
    using size_type   = std::size_t;
    using size_cref   = size_type const &;
    public:
      Identifier();
    //Getters
      constexpr
      IdentifierType const & GetType() const noexcept { return m_type; }
      constexpr
      string_cref  GetName() const noexcept { return m_name; }
      constexpr
      bool IsArray() const noexcept { return m_is_array; }
      constexpr
      bool IsStatic() const noexcept { return m_is_static; }
    //Setters
      constexpr
      void SetType(IdentifierType const & type) { m_type = type; }
      constexpr
      void SetName(string_cref name)  { m_name = name; }
      constexpr
      void SetAsArray(bool val = true) { m_is_array = val; }
      constexpr
      void SetAsStatic(bool val = true) { m_is_static = val; }
    private:
      IdentifierType m_type;
      string_type    m_name;
      size_type      m_level;
      bool           m_is_array;
      bool           m_is_static;
  };
  
  class Expression : public INode
  {
    enum class Type
    {
      kNoOperation, kIntConst, kChar, kString, kIdentifier,
      kAdd, kMinus, kMul, kDiv
    };
    
    private:
    //Reusing this struct to quickly get all data needed
    scanner::Token m_token;  

  };
} // namespace ast
#endif//AST_NODE_CLASSES_HPP
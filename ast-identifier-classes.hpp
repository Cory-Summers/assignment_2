#ifndef AST_IDENTIFIER_CLASSES_HPP
#define AST_IDENTIFIER_CLASSES_HPP
#include "ast-node-classes.hpp"
namespace ast
{

  class Identifier : public INode
  {
  public:
    using string_type = std::string;
    using string_cref = string_type const &;
    using size_type = std::size_t;
    using size_cref = size_type const &;

  public:
    Identifier() {}
    Identifier(string_cref name, IdentifierType type = ast::IdentifierType::kUndefined)
        : m_type(type), m_name(name), m_level()
    {
      m_form = Form::Identifier;
    }
    Identifier(scanner::Token const &token, IdentifierType type = ast::IdentifierType::kUndefined)
        : m_type(type), m_name(token.token_string), m_level()
    {
      m_form = Form::Identifier;
      m_pos = token.pos;
    }
    //Getters
    constexpr IdentifierType const &GetType() const noexcept { return m_type; }
    constexpr string_cref GetName() const noexcept { return m_name; }
    //Setters
    constexpr void SetType(IdentifierType const &type) { m_type = type; }
    void SetName(string_cref name) { m_name = name; }
    virtual string_type ToString() 
    {
      return string_type("Id: " + m_name + " " + GetLine()); 
    } 
  protected:
    IdentifierType m_type;
    string_type m_name;
    size_type m_level;
  };
  //Interface for type declarations
  class ITypeDecl
  {
    using size_type = std::size_t;

  public:
    //Getter
    constexpr bool IsArray() const noexcept { return m_is_array; }
    constexpr VariableType const &GetVariableType() const noexcept { return m_var_type; }
    //Setter
    constexpr void SetVariableType(VariableType const &type) { m_var_type = type; }
    constexpr void SetAsArray(bool val = true, size_type size = 0)
    {
      m_is_array = val;
      m_array_size = size;
    }

  protected:
    size_type m_array_size;
    bool m_is_array;
    VariableType m_var_type;
  };
  class VariableDecl : public Identifier, public ITypeDecl
  {
  public:
    VariableDecl() {}
    VariableDecl(string_cref name)
        : Identifier(name, ast::IdentifierType::kVariable)
    {
      m_var_type = ast::VariableType::kUndefined;
      m_level = 0;
      m_array_size = 0;
      m_is_array = false;
      m_is_static = false;
      m_is_param = false;
    }
    VariableDecl(scanner::Token const &token)
        : Identifier(token, ast::IdentifierType::kVariable)
    {
      m_var_type = ast::VariableType::kUndefined;
      m_level = 0;
      m_array_size = 0;
      m_is_array = false;
      m_is_static = false;
      m_is_param = false;
    }
    VariableDecl(scanner::Token const & token, ast::VariableType type)
      : Identifier(token, ast::IdentifierType::kVariable)
    {
      m_var_type = type;
      m_level = 0;
      m_array_size = 0;
      m_is_array = false;
      m_is_static = false;
      m_is_param = false; 
    }
    virtual string_type ToString()
    {
      string_type temp;
      if (m_is_param)
        temp += "Parm: ";
      else
        temp += "Var: ";
      temp += m_name;
      if (m_is_array)
        temp += " is array";
      temp += " of type " + VariableTypeStr(m_var_type) + " " + GetLine();
      return temp;
    }
    //Getters
    constexpr bool IsStatic() const noexcept { return m_is_static; }
    constexpr bool IsParam() const noexcept { return m_is_param; }
    //Setters
    constexpr void SetAsParam(bool val = true)
    {
      m_is_param = val;
      m_type = val ? (IdentifierType::kParameter) : (IdentifierType::kVariable);
    }
    constexpr void SetAsStatic(bool val = true) { m_is_static = val; }

  protected:
    bool m_is_static;
    bool m_is_param;
  };
  class Function : public Identifier, public ITypeDecl
  {
  public:
    Function() {}
    Function(scanner::Token const &token, VariableType ret_type = VariableType::kVoid)
        : Identifier(token, IdentifierType::kFunction)
    {
      m_var_type = ret_type;
      m_is_array = false;
    }
    virtual string_type ToString()
    {
      string_type temp = "Func: " + m_name + " returns type " + VariableTypeStr(m_var_type) + " " + GetLine();
      return temp;
    }

  protected:
  };
}
#endif //AST_IDENTIFIER_CLASSES_HPP

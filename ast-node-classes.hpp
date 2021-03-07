#ifndef AST_NODE_CLASSES_HPP
#define AST_NODE_CLASSES_HPP
#include <iostream>
#include <iterator>
#include <memory>
#include <list>
#include <string>
#include <vector>
#include "location.hh"
#include "ast-types.hpp"
#include "scanner-token.hpp"
namespace ast
{
  /* */
  class ILocation
  {
    public:
      using loc_type = parser::location;
    loc_type GetLocation() { return m_pos; }
    void SetLocation(loc_type const &pos) { m_pos = pos; }
    protected:
      loc_type m_pos;
  }
  class INode : public ILocation //Node Interface
  {
  public:
    class Iterator
    {
    public:
      using iterator_category = std::forward_iterator_tag;
      using difference_type = std::ptrdiff_t;
      using value_type = INode;
      using pointer = value_type *;
      using reference = value_type &;

    public:
      INode *ptr;
      Iterator() : ptr(nullptr) {}
      Iterator(INode *p) : ptr(p) {}
      reference operator*() { return *ptr; }
      pointer operator->() { return ptr; }
      Iterator operator++(int);
      Iterator &operator++();
      friend bool operator==(Iterator const &lhs, Iterator const &rhs) { return (lhs.ptr == rhs.ptr); }
      friend bool operator!=(Iterator const &lhs, Iterator const &rhs) { return (lhs.ptr != rhs.ptr); }
    };
    using size_type = std::size_t;
    using loc_type = parser::location;
    using iterator = Iterator;
    using string_type = std::string;
    enum class Form
    {
      kUndefined,
      Identifier,
      Expression
    };

  public:
    const Form GetForm() { return m_form; }
    virtual std::string ToString() { return ""; }
    virtual size_type GetIndex() const noexcept { return m_idx; }
    virtual void SetIndex(size_type const &idx) { m_idx = idx; }
    void AddChild(std::shared_ptr<INode> const &node)
    {
      if (node)
      {
        node->m_parent = this;
        m_children.push_back(node);
      }
    }
    void AddChild(std::shared_ptr<INode> &node)
    {
      if (node)
      {
        node->m_parent = this;
        m_children.push_back(node);
      }
    }
    virtual std::shared_ptr<INode> &GetSibling() { return m_sibling; }
    virtual void SetSibling(std::shared_ptr<INode> &sib) { m_sibling = sib; }
    size_type NumOfChildren() const { return m_children.size(); }
    INode *GetChild(std::size_t idx) { return m_children[idx].get(); }
    iterator begin() { return iterator(m_sibling.get()); }
    iterator end() { return iterator(nullptr); }

  protected:
    string_type GetLine() const { return std::string("[line: " + std::to_string(m_pos.begin.line) + "]"); }
    size_type m_idx;
    Form m_form;
    INode *m_parent;
    std::vector<std::shared_ptr<INode>> m_children;
    std::shared_ptr<INode> m_sibling;
  };
} // namespace ast
#endif //AST_NODE_CLASSES_HPP
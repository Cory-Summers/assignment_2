#include "ast-node-classes.hpp"

namespace ast
{
  /*********    INode Section   *********/
  INode::Iterator INode::Iterator::operator++(int) //postfix
  {
    Iterator i = *this;
    ++(*this);
    return i;
  }
  INode::Iterator &INode::Iterator::operator++()
  {
    if (ptr)
      ptr = ptr->m_sibling.get();
    return *this;
  }
}
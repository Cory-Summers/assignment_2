#ifndef CONTEXT_CLASS_HPP
#define CONTEXT_CLASS_HPP
#include <iostream>
#include <string>
#include "position.hh"
//#include "abstract-syntax-tree.hpp"
namespace ast { class Tree { int i; }; }
namespace parser
{
  struct Context
  {
    using loc_type = position;
    Context() {};
    Context(std::string, std::istream *);
    std::string file_name;
    std::istream * file;
    loc_type loc;
    ast::Tree ast_tree;
  };
  inline parser::Context::Context(std::string name, std::istream * ptr)
  : file_name(name)
  , file(ptr)
  , loc(&name, 1, 1)
  , ast_tree()
  {}
}
#endif //CONTEXT_CLASS_HPP
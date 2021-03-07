#ifndef DRIVER_CLASS_HPP
#define DRIVER_CLASS_HPP
#include "parser.tab.hh"
#include "token-lexer-class.hpp"
#include <map>
#include <memory>
#include <string>
#include <vector>
struct Flag
{
  Flag(char c, int v) : id(c), value(v), string(), has_argument(false) {} 
  int id;
  int value;
  std::string string;
  bool has_argument;
};
struct Context
{
  using loc_type = position;
  Context() {};
  Context(std::string, std::istream *);
  std::string file_name;
  std::istream * file;
  std::ostream * output_stream;
  ast::Tree ast_tree;
};
/* Driver Class */
// Class acts the main driver of the compiler containing its discrete components
//
//
class Driver
{
  using string_type = std::string;
  public:
  Driver(int argc, char * argv[]);
  void Parse();
  void Initialize();
  private:
    void ProcessArguments(int, char * argv[]);
    void InitFlags();
    std::istream * RetrieveInput();
    std::istream * m_input; //Can't use smart pointers due usage of std::cin
    std::unique_ptr<scanner::TokenLexer> m_scanner;
    std::unique_ptr<parser::CMinParser> m_parser;
    Context                  m_context;
    std::vector<string_type> m_parameters;
    std::map<int, Flag>      m_flags;
    const std::string        m_opts = "pdhPS";
};
#endif //DRIVER_CLASS_HPP
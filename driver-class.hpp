#ifndef DRIVER_CLASS_HPP
#define DRIVER_CLASS_HPP
#include "token_parser.tab.hh"
#include "token-lexer-class.hpp"
#include "context-class.hpp"
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
    std::istream * RetrieveInput();
    std::istream * m_input; //Can't use smart pointers due usage of std::cin
    std::unique_ptr<scanner::TokenLexer> m_scanner;
    std::unique_ptr<parser::TokenParser> m_parser;
    parser::Context          m_context;
    std::vector<string_type> m_parameters;
    std::map<int, Flag>      m_flags;
    const std::string        m_opts = "pc";
};
#endif //DRIVER_CLASS_HPP
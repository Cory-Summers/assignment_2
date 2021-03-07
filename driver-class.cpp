#include "driver-class.hpp"
#include <fstream>
const char k_help_message[] =
    "Usage: c- [options] [sourceFile]\n"
    "  -d  turn on Bison debugging\n"
    "  -h  this usage message\n"
    "  -P  print abstract syntax tree + types"
    "  -S  turn on symbol table debugging";
Driver::Driver(int argc, char *argv[])
    : m_input()
{
  ProcessArguments(argc, argv);
  Initialize();
}
void Driver::Initialize()
{
  m_input = RetrieveInput();
  m_context = parser::Context(m_parameters[0], m_input);
  m_scanner = std::make_unique<scanner::TokenLexer>(m_input);
  m_parser = std::make_unique<parser::CMinParser>(*m_scanner, m_context, std::cout);
}
void Driver::Parse()
{
  if (m_parser->parse() != 0)
  {
    std::cerr << "Parser was unable parse!\n";
    return;
  }
  
  if (m_flags.find('P') != m_flags.end())
  {
    m_context.ast_tree.Print(std::cout);
  }
}
std::istream *Driver::RetrieveInput()
{
  std::istream *stream;
  if (m_parameters.empty())
  {
    m_flags.insert({static_cast<int>('s'), Flag('s', 1)});
    m_parameters.emplace_back("stdin");
    return &(std::cin);
  }
  else
  {
    try
    {
      stream = new std::ifstream();
      dynamic_cast<std::ifstream *>(stream)->open(m_parameters[0]);
      if (!*stream)
      {
        throw std::system_error(errno, std::system_category(), "failed to open " + m_parameters[0]);
      }
    }
    catch (std::ios::failure &e)
    {
      std::cerr << e.what() << '\n';
      delete stream;
    }
    return stream;
  }
}
void Driver::InitFlags()
{
  for(auto & flag : m_flags)
  {
    switch(flag.first)
    {
      case int('h'):
        std::cout << k_help_message <<'\n';
        std::exit(flag.first);
        break;
      case int('d'):
        m_parser->set_debug_level(1);
        m_parser->set_debug_stream(std::cerr);
        break;
      
    }
  }
}
/* For right now no need to write a proper get-opt. I hate the unix impl 
for using global variables for function call */
void Driver::ProcessArguments(int argc, char *argv[])
{
  std::vector<std::string> input(argv + 1, argv + argc);
  for (auto &in : input)
  {
    if (in[0] == '-')
    {
      auto opt_id = m_opts.find(in[1]);
      if (opt_id == string_type::npos || in[1] == '\0')
      {
        std::cerr << "Unknown Option \'" << in << "\'!\n";
        throw std::logic_error("Unknown Option.");
      }
      m_flags.insert({static_cast<int>(in[1]), Flag(in[1], 1)});
    }
    else
    {
      m_parameters.push_back(in);
    }
  }
}
parser::Context::Context(std::string name, std::istream * ptr)
: file_name(name)
, file(ptr)
, ast_tree()
{}
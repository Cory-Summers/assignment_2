#include "driver-class.hpp"
Driver::Driver(int argc, char *argv[])
    : m_input()
{
  ProcessArguments(argc, argv);
  Initialize();
}
void Driver::Initialize()
{
  m_input   = RetrieveInput();
  m_context = parser::Context(m_parameters[0], m_input);
  m_scanner = std::make_unique<scanner::TokenLexer>(m_input);
  m_parser  = std::make_unique<parser::TokenParser>(*m_scanner, m_context);
}
void Driver::Parse()
{
  if (m_parser->parse() != 0)
  {
    std::cerr << "Parser was unable parse!\n";
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
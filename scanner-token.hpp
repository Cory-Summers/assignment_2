#ifndef SCANNER_TOKEN_HPP
#define SCANNER_TOKEN_HPP
#include <fstream>
#include <string>
#include <cstdint>
#include "location.hh"
#include "encode-string.hpp"
namespace scanner
{

  struct Token
  {
    enum class Type { kString = 0, kNumeric, kChar, kIdentifier, kBoolean } type;
    std::string token_string;
    char char_value;
    std::int32_t num_value;
    std::string string_value;
    parser::location pos;
    Token()
        : token_string(), char_value(0), num_value(0), string_value()
    {
    }
    static std::string TypeToString(Token const &); 
  };
  namespace factory
  {
    Token TokenString(std::string str,  parser::location &pos);
    Token TokenNumeric(std::string str, parser::location &pos);
    Token TokenChar(std::string str,    parser::location & pos);
    Token TokenIdentifier(std::string str, parser::location & pos);
    Token TokenBoolean(bool value, parser::location & pos);
  }    // namespace factory
};     // namespace scanner
#endif //SCANNER_TOKEN_HPP
#ifndef ENCODE_STRING_HPP
#define ENCODE_STRING_HPP
#include <string>
namespace scanner
{
  std::string EncodeString(const char * str);
  std::string EncodeString(const char * str, std::size_t const & length); 
  std::string EncodeString(std::string const &);
  char EncodeChar(const char * str, std::size_t const & length);
  char EncodeChar(std::string const &);
}
#endif
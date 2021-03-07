#include "scanner-token.hpp"
scanner::Token scanner::factory::TokenString(std::string str, parser::location &pos)
{
  Token token;
  token.type = Token::Type::kString;
  token.token_string = str;
  token.string_value = EncodeString(str);
  token.pos = pos;
  return token;
}
scanner::Token scanner::factory::TokenNumeric(std::string str, parser::location &pos)
{
  Token token;
  token.type = Token::Type::kNumeric;
  token.token_string = str;
  token.num_value = std::stol(str, nullptr, 10);
  token.pos = pos;
  return token;
}
scanner::Token scanner::factory::TokenChar(std::string str, parser::location & pos)
{ 
  Token token;
  token.type = Token::Type::kChar;
  token.token_string = str;
  token.char_value   = EncodeChar(str.c_str(), str.size());
  token.pos = pos;
  return token;
}
scanner::Token scanner::factory::TokenIdentifier(std::string str, parser::location & pos)
{
  Token token;
  token.type = Token::Type::kIdentifier;
  token.token_string = str;
  token.pos = pos;
  return token;
}
scanner::Token scanner::factory::TokenBoolean(bool value, parser::location & pos)
{
  Token token;
  token.type = Token::Type::kBoolean;
  token.token_string = value ? ("true") : ("false");
  token.num_value = (std::int32_t)value;
  token.pos = pos;
  return token;
}
std::string scanner::Token::TypeToString(Token const & token)
{
  const char * kOptions[] { "char", "int", "char", "", "bool" };
  return kOptions[(std::size_t)token.type];
}
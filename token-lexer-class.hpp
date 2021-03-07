#ifndef TOKEN_LEXER_CLASS_HPP
#define TOKEN_LEXER_CLASS_HPP
#if !defined(yyFlexLexerOnce)
#include <FlexLexer.h>
#endif
#include "parser.tab.hh"
#include "location.hh"
namespace scanner
{
  class TokenLexer : public yyFlexLexer
  {
    public:
      TokenLexer(std::istream * in) : yyFlexLexer(in) { }
      using yyFlexLexer::yylex;
      virtual
      int yylex(
        parser::CMinParser::semantic_type * const lval, 
        parser::CMinParser::location_type *location, 
        parser::Context & context 
      );
      private:
         parser::CMinParser::semantic_type *yylval = nullptr;
         parser::CMinParser::location_type *loc    = nullptr;
  };
}
#endif //TOKEN_LEXER_CLASS_HPP
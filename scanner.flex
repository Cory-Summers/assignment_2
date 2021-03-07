/* Cory Summers */
%option c++
  // CM == C-
%option yyclass="scanner::TokenLexer"
%option noyywrap
%{
  #include <iostream>
  #include <numeric>
  #include "encode-string.hpp"
  #include "token-lexer-class.hpp"
  #include "context-class.hpp"
  //#include "token_parser.tab.hh"
  using std::cin;
  using std::cout;
  using std::cerr; //I hate using using std::blah;
  //OPERATOR [-][-]|[+][+]|[+\-<>*\/!=][=]|[\[\]()&|=*+\-\/%<>!?:,;]
  #undef  YY_DECL
  #define YY_DECL int scanner::TokenLexer::yylex( \
     parser::CMinParser::semantic_type * const lval, \
     parser::CMinParser::location_type *location, \
     parser::Context & context \
     )
  #define YY_USER_ACTION location->step(); location->columns(yyleng);
%}

IDENTIFIER  ([A-Za-z][_A-Za-z0-9]*)
STRING   (\"(\\.|[^\"\\])*\")
NUMCONST ([0-9]+)
  //('([^'\\\n]|\\.)')
CHARCONST (\'([\\].|[^']+)\') 
BADCHARCONST (\'([\\].+|.+)\')
WHITESPACE ([ \t]+)
COMMENT (\/\/[^\n\r]*)
  /*Compound Assignment Operators */

NEWLINE  ([\n]|(\r\n))
%%
%{
  yylval = lval;
%}
{COMMENT} {}
{STRING}  { 
  yylval->token = scanner::factory::TokenString(yytext, *location);
  return parser::CMinParser::token::T_STRINGCONST;
}
{NUMCONST} {
  
  yylval->token = scanner::factory::TokenNumeric(yytext, *location);
  return parser::CMinParser::token::T_NUMCONST;
}
{CHARCONST} {
  yylval->token = scanner::factory::TokenChar(yytext, *location);
  return parser::CMinParser::token::T_CHARCONST;
}
{BADCHARCONST} {
  std::cerr << context.file_name << ':' << location->begin.line << ": warning: multi-character wide character constant used\n\t"
  << yytext << '\n';
  yylval->token = scanner::factory::TokenChar(yytext, *location);
  return parser::CMinParser::token::T_CHARCONST;
}
"int"    { return parser::CMinParser::token::TYPE_INT;  }
"char"   { return parser::CMinParser::token::TYPE_CHAR; }
"bool"   { return parser::CMinParser::token::TYPE_BOOL; }
"if"     { return parser::CMinParser::token::T_KEY_IF;   }
"else"   { return parser::CMinParser::token::T_KEY_ELSE; }
"return" { return parser::CMinParser::token::T_KEY_RETURN; }
"for"    { return parser::CMinParser::token::T_KEY_FOR;    }
"while"  { return parser::CMinParser::token::T_KEY_WHILE;  }
"by"     { return parser::CMinParser::token::T_KEY_BY;     }
"do"     { return parser::CMinParser::token::T_KEY_DO;     }
"then"   { return parser::CMinParser::token::T_KEY_THEN;   }
"static" { return parser::CMinParser::token::T_KEY_STATIC; }
"break"  { return parser::CMinParser::token::T_KEY_BREAK;  }
"or"     { return parser::CMinParser::token::T_KEY_OR;     }
"and"    { return parser::CMinParser::token::T_KEY_AND;    }
"not"    { return parser::CMinParser::token::T_KEY_NOT;    }
"to"     { return parser::CMinParser::token::T_KEY_TO;     }
"true"   { yylval->token = scanner::factory::TokenBoolean(true, *location); return parser::CMinParser::token::T_BOOLCONST;   }
"false"  { yylval->token = scanner::factory::TokenBoolean(false, *location); return parser::CMinParser::token::T_BOOLCONST;   }
{IDENTIFIER} {
  yylval->token = scanner::factory::TokenIdentifier(yytext, *location);
  return parser::CMinParser::token::T_IDENTIFIER;
}
  /*Non Operator Symbols*/
":"  { return parser::CMinParser::token::T_COLON; }
";"  { return parser::CMinParser::token::T_END_STMT;  }
","  { return parser::CMinParser::token::T_DECL_SEP;  }
"{"  { return parser::CMinParser::token::T_LHS_BRACE; }
"}"  { return parser::CMinParser::token::T_RHS_BRACE; }
"("  { return parser::CMinParser::token::T_LHS_PAREN; }
")"  { return parser::CMinParser::token::T_RHS_PAREN; }
"["  { return parser::CMinParser::token::T_LHS_BRACK; }
"]"  { return parser::CMinParser::token::T_RHS_BRACK; }
  /* Operator Symbols */
  /* Operators will be scoped with parser::CMinParser::token::T_OP_(BLAH) */
"<="  { return parser::CMinParser::token::T_OP_LES_EQ; } //Less then Equals to
"<"   { return parser::CMinParser::token::T_OP_LESS;  }
">"   { return parser::CMinParser::token::T_OP_GREAT; }
">="  { return parser::CMinParser::token::T_OP_GRE_EQ; }
"=="  { return parser::CMinParser::token::T_OP_EQUALIVE; }
"!="  { return parser::CMinParser::token::T_OP_NOT_EQUAL; }
"--"  { return parser::CMinParser::token::T_DECREMENT; }
"++"  { return parser::CMinParser::token::T_INCREMENT; }
":>:" { return parser::CMinParser::token::T_OP_MAX; }
":<:" { return parser::CMinParser::token::T_OP_MIN; }
"+"   { return parser::CMinParser::token::T_OP_PLUS; }
"-"   { return parser::CMinParser::token::T_OP_MINUS; }
"*"   { return parser::CMinParser::token::T_OP_MULTI; }
"\/"  { return parser::CMinParser::token::T_OP_DIVIDE; }
"\%"  { return parser::CMinParser::token::T_OP_MODULO; }
"?"   { return parser::CMinParser::token::T_OP_GENERATOR; }
"+="  { return parser::CMinParser::token::T_OP_ADDASS; }
"-="  { return parser::CMinParser::token::T_OP_MINASS; }
"*="  { return parser::CMinParser::token::T_OP_MULASS; }
"\/=" { return parser::CMinParser::token::T_OP_DIVASS; }
"="   { return parser::CMinParser::token::T_OP_ASSIGN; }
{WHITESPACE} { }
{NEWLINE} { location->lines(); }
. { std::cerr << "ERROR(" << location->begin.line << "): Invalid or misplaced input character: \'" << yytext << "\'. Character Ignored.\n";}

%%
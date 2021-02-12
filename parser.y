%skeleton "lalr1.cc"
%language "C++"
%define api.namespace {parser}
%define parser_class_name { CMinParser }
%locations
%code requires{
  #include "scanner-token.hpp"
  #include "print-values.hpp"

  namespace parser
  {
    struct Context; //Forward Decl
    struct Token //I hate it but it works
    {
      Token() : token() {}
      scanner::Token token;
    };
  }
  namespace scanner
  {
    class TokenLexer; //Forward Decl
  };

} //code requiress
%parse-param { scanner::TokenLexer & scanner }
%parse-param { parser::Context & context }
%lex-param   { parser::Context & context}
%code {
  #include "driver-class.hpp"
  #include "context-class.hpp"
  #undef yylex
  #define yylex scanner.yylex
%}
%token TYPE_INT TYPE_CHAR TYPE_BOOL
%token T_DECL_SEP  ','
%token T_COLON     ':'
%token T_LHS_BRACK '['
%token T_RHS_BRACK ']'
%token T_END_STMT  ';'
%token T_LHS_PAREN '(' 
%token T_RHS_PAREN ')'
%token T_LHS_BRACE '{'
%token T_RHS_BRACE '}'

%token T_OP_ASSIGN '='
//Keywords
%token T_KEY_IF     "if"
%token T_KEY_THEN   "then"
%token T_KEY_ELSE   "else"
%token T_KEY_WHILE  "while"
%token T_KEY_DO     "do"
%token T_KEY_FOR    "for"
%token T_KEY_BY     "by"
%token T_KEY_RETURN "return"
%token T_KEY_IN     "in"
%token T_KEY_BREAK  "break"
%token T_KEY_OR     "or"
%token T_KEY_AND    "and"
%token T_KEY_STATIC "static"
%token T_KEY_NOT    "not"

%token T_DECREMENT  "--"
%token T_INCREMENT  "++"
%token T_OP_LES_EQ T_OP_LESS T_OP_GREAT T_OP_GRE_EQ T_OP_EQUALIVE T_OP_NOT_EQUAL T_OP_COMP_ASG T_OP_MAX T_OP_MIN
%token T_OP_MINUS T_OP_PLUS T_OP_MULTI T_OP_DIVIDE T_OP_MODULO T_OP_GENERATOR T_OP_ADDASS T_OP_MINASS T_OP_MULASS T_OP_DIVASS
%token <token>T_STRINGCONST 
%token <token>T_NUMCONST
%token <token>T_CHARCONST
%token <token>T_BOOLCONST
%token <token>T_IDENTIFIER 

%%

Program : DeclList {};
DeclList
  : DeclList Decl
  | Decl
  ;
Decl 
  : VariableDecl
  | FunctionDecl
  ;
/*** VARIABLE DECLARTIONS ***/
VariableDecl
  : TypeSpecifier VariableDeclList ';'
  ;
ScopedVariableDecl
  : T_KEY_STATIC TypeSpecifier VariableDeclList ';'
  | TypeSpecifier VariableDeclList ';'
  ;
VariableDeclList
  : VariableDeclList ',' VariableDeclInit
  | VariableDeclInit
  ;
VariableDeclInit
  : VariableDeclID ':' SimpleExpression
  | VariableDeclID 
  ;
VariableDeclID
  : T_IDENTIFIER
  | T_IDENTIFIER '[' T_NUMCONST ']'
  ;
TypeSpecifier
  : TYPE_INT
  | TYPE_CHAR
  | TYPE_BOOL
  ;
/*** Function Declarations ***/
FunctionDecl
  : TypeSpecifier T_IDENTIFIER '(' Parameters ')' Statement
  | T_IDENTIFIER '(' Parameters ')' Statement
  ;
Parameters
  : %empty 
  | ParameterList
  ;
ParameterList 
  : ParameterList ';' ParameterTypeList
  | ParameterTypeList
  ;
ParameterTypeList
  : TypeSpecifier ParameterIDList
  ;
ParameterIDList
  : ParameterIDList ',' ParameterID
  | ParameterID
  ;
ParameterID
  : T_IDENTIFIER
  | T_IDENTIFIER '[' ']'
  ;
/*** Statements ***/
Statement
  : ExpressionStmt
  | CompoundStmt
  | ConditionStmt
  | IteratorStmt
  | ReturnStmt
  | BreakStmt
  ;
/* This is need to resolve shift/reduce conflict within the if else Statement */

ExpressionStmt
  : Expression ';'
  | ';'
  ;
CompoundStmt
  : '{' LocalDecls StatementList '}'
  ;
LocalDecls 
  : %empty
  | LocalDecls ScopedVariableDecl
  ;
StatementList 
  : %empty
  | StatementList Statement
  ;
ConditionStmt
  : CompleteCondition 
  | IncompleteCondition
  ;
CompleteCondition
  : "if" SimpleExpression "then" Statement "else" Statement
  ;
IncompleteCondition
  : "if" SimpleExpression "then" Statement
  ;
IteratorStmt
  : "while" SimpleExpression "do" Statement
  | "for" T_IDENTIFIER '=' IteratorRange "do" Statement
  ;
IteratorRange
  : SimpleExpression 
  | SimpleExpression "to" SimpleExpression
  | SimpleExpression "to" SimpleExpression "by" SimpleExpression
  ;
ReturnStmt
  : "return" ';'
  | "return" Expression ';'
  ;
BreakStmt
  : "break" ';'
  ;
/*** Expressions ***/
Expression
  : Mutable '=' Expression
  | Mutable T_OP_COMP_ASG Expression
  | Mutable "++"
  | Mutable "--"
  | SimpleExpression
  ;
SimpleExpression
  : SimpleExpression "or" AndExpr 
  | AndExpr
  ;
AndExpr
  : AndExpr "and" UnaryReletiveExpr
  | UnaryReletiveExpr
  ;
UnaryReletiveExpr
  : "not" UnaryReletiveExpr
  | ReletiveExpr
  ;
ReletiveExpr
  : MinMaxExp ReletiveOper MinMaxExp
  | MinMaxExp
  ;
ReletiveOper
  : T_OP_LES_EQ
  | T_OP_LESS
  | T_OP_GREAT
  | T_OP_GRE_EQ  
  | T_OP_EQUALIVE
  | T_OP_NOT_EQUAL
  | T_OP_COMP_ASG 
  ;
MinMaxExp
  : MinMaxExp MinMaxOper SumExpr
  | SumExpr
  ;
MinMaxOper
  : T_OP_MIN
  | T_OP_MAX
  ;
SumExpr
  : SumExpr SumOper MulExp 
  | MulExp 
  ;
SumOper
  : T_OP_PLUS
  | T_OP_MINUS
  ;
MulExp
  : MulExp MulOp UnaryExpr
  | UnaryExpr
  ;
MulOp
  : T_OP_MULTI
  | T_OP_DIVIDE
  | T_OP_MODULO
  ;
UnaryExpr
  : UnaryOper UnaryExpr
  | Factor
  ;
UnaryOper
  : T_OP_MINUS
  | T_OP_MULTI
  | T_OP_GENERATOR
  ;
Factor
  : Immutable
  | Mutable
  ;
Mutable
  : T_IDENTIFIER
  | T_IDENTIFIER '[' Expression ']'
  ;
Immutable
  : '(' Expression ')'
  | Call
  | Constant
  ;
Call
  : T_IDENTIFIER '(' Arguments ')'
  ;
Arguments 
  : %empty
  | ArgumentList
  ;
ArgumentList
  : ArgumentList ',' Expression
  | Expression
  ;
Constant
  : T_NUMCONST
  | T_CHARCONST
  | T_STRINGCONST
  | T_BOOLCONST
  ;
%%

void parser::CMinParser::error(const location_type &l, const std::string & error_message)
{
  std::cerr << "Error: " << error_message << " at " << l << "\n";
}
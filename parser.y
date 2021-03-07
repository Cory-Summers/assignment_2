%skeleton "lalr1.cc"
%language "C++"
%define api.namespace {parser}
%define parser_class_name { CMinParser }
%locations
%error-verbose
%code requires{
  #include "scanner-token.hpp"
  #include "print-values.hpp"
  #include "abstract-syntax-tree.hpp"
  struct Context; //Forward Decl
  namespace parser
  {
    struct Token //I hate it but it works
    {
      Token() : token() {}
      scanner::Token token;
      std::shared_ptr<ast::INode> ast_node;
      union
      {
        ast::VariableType  var_type;
        ast::OperationType oper_type;
      };
    };
  }
  namespace scanner
  {
    class TokenLexer; //Forward Decl
  };

} //code requiress
%parse-param { scanner::TokenLexer & scanner }
%parse-param { Context & context }
%parse-param { std::ostream &   out }
%lex-param   { Context & context }
%define api.value.type {parser::Token}
%code {
  #include "driver-class.hpp"
  #undef yylex
  #define yylex scanner.yylex
}
%token TYPE_INT TYPE_CHAR TYPE_BOOL
%token T_DECL_SEP  ","
%token T_COLON     ":"
%token T_LHS_BRACK "["
%token T_RHS_BRACK "]"
%token T_END_STMT  ";"
%token T_LHS_PAREN "(" 
%token T_RHS_PAREN ")"
%token T_LHS_BRACE "{"
%token T_RHS_BRACE "}"
%token T_OP_ASSIGN "="
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
%token T_KEY_TO     "to"

%token T_DECREMENT  "--"
%token T_INCREMENT  "++"
%token T_OP_LES_EQ T_OP_LESS T_OP_GREAT T_OP_GRE_EQ T_OP_EQUALIVE T_OP_NOT_EQUAL T_OP_COMP_ASG T_OP_MAX T_OP_MIN
%token T_OP_MINUS T_OP_PLUS T_OP_MULTI T_OP_DIVIDE T_OP_MODULO T_OP_GENERATOR T_OP_ADDASS T_OP_MINASS T_OP_MULASS T_OP_DIVASS
%token <token>T_STRINGCONST 
%token <token>T_NUMCONST
%token <token>T_CHARCONST
%token <token>T_BOOLCONST
%token <token>T_IDENTIFIER 
%type  <token> Constant
%type  <ast_node> VariableDeclID VariableDeclInit VariableDeclList ScopedVariableDecl VariableDecl DeclList Decl
%type  <var_type> TypeSpecifier 
//Functions
%type  <ast_node> FunctionDecl Parameters ParameterList ParameterTypeList ParameterIDList ParameterID 
//Expressions
%type  <ast_node> Expression SimpleExpression ExpressionStmt CompoundStmt ConditionStmt IteratorStmt ReturnStmt BreakStmt
%type  <ast_node>   AndExpr UnaryReletiveExpr ReletiveExpr MinMaxExp SumExpr 
%type  <ast_node> MulExp  UnaryExpr Factor Mutable Call Arguments ArgumentList Immutable 
%type  <ast_node> LocalDecls StatementList Statement CompleteCondition IncompleteCondition IteratorRange
%type  <oper_type> UnaryOper MulOp SumOper OperAssign ReletiveOper MinMaxOper

%%

Program : DeclList {};
DeclList
  : DeclList Decl {$$ = ast::action::DeclList($1, $2);  }
  | Decl { context.ast_tree.SetHead($1); $$ = $1; }
  ;
Decl 
  : VariableDecl {  $$ = $1; }
  | FunctionDecl { $$ = $1; }
  ;
/*** VARIABLE DECLARTIONS ***/
VariableDecl
  : TypeSpecifier VariableDeclList ";" { $$ = ast::action::VariableDecl($1, $2); }
  ;
ScopedVariableDecl
  : T_KEY_STATIC TypeSpecifier VariableDeclList ";"  {$$ = ast::action::StaticDecl($2, $3);  }
  | TypeSpecifier VariableDeclList ";" { $$ = ast::action::VariableDecl($1, $2); }
  ;
VariableDeclList
  : VariableDeclInit { $$ = $1; } 
  | VariableDeclList "," VariableDeclInit {$$ = ast::action::AddToTail($1, $3); }
  ;
VariableDeclInit
  : VariableDeclID ":" SimpleExpression { $1->AddChild($3); $$ = $1; }
  | VariableDeclID {$$ = $1; }
  ;
VariableDeclID 
  : T_IDENTIFIER { $$ = std::make_shared<ast::VariableDecl>($1); }
  | T_IDENTIFIER T_LHS_BRACK T_NUMCONST T_RHS_BRACK { auto var =  std::make_shared<ast::VariableDecl>($1); var->SetAsArray(true, $3.num_value); $$ = var; }
  ;
TypeSpecifier
  : TYPE_INT   { $$ = ast::VariableType::kInt; }
  | TYPE_CHAR  { $$ = ast::VariableType::kChar; }
  | TYPE_BOOL  { $$ = ast::VariableType::kBool; }
  ;
/*** Function Declarations ***/
FunctionDecl
  : TypeSpecifier T_IDENTIFIER "(" Parameters ")" Statement { $$ = ast::action::FunctionDecl($1, $2, $4, $6);}
  | T_IDENTIFIER "(" Parameters ")" Statement { $$ = ast::action::FunctionDecl(ast::VariableType::kVoid, $1, $3, $5); }
  ;
Parameters
  : %empty { $$ = ast::node_pointer();}
  | ParameterList {$$ = $1; }
  ;
ParameterList 
  : ParameterList ";" ParameterTypeList { $$ = ast::action::AddToTail($1, $3); }
  | ParameterTypeList {$$ = $1; }
  ;
ParameterTypeList
  : TypeSpecifier ParameterIDList { $$ = ast::action::ParameterType($1, $2); }
  ;
ParameterIDList
  : ParameterIDList "," ParameterID {$$ = ast::action::AddToTail($1, $3); }
  | ParameterID { $$ = $1; }
  ;
ParameterID
  : T_IDENTIFIER { $$ = ast::action::ParameterID($1, false); }
  | T_IDENTIFIER "[" "]" { $$ = ast::action::ParameterID($1, true); }
  ;
/*** Statements ***/
Statement
  : ExpressionStmt {$$ = $1; }
  | CompoundStmt { $$ = $1; }
  | ConditionStmt {$$ = $1; }
  | IteratorStmt {$$ = $1; }
  | ReturnStmt { $$ = $1;}
  | BreakStmt {$$ = $1; }
  ;
/* This is need to resolve shift/reduce conflict within the if else Statement */

ExpressionStmt
  : Expression ";" { $$ = $1; }
  | ";" { $$ = ast::node_pointer(); }
  ;
CompoundStmt
  : "{" LocalDecls StatementList "}" { $$ = ast::action::CompoundStmt($2, $3, @1);}
  ;
LocalDecls 
  : %empty { $$ = ast::node_pointer(); }
  | LocalDecls ScopedVariableDecl { $$ = ast::action::AddToTail($1, $2); }
  ;
StatementList 
  : %empty { $$ = ast::node_pointer(); }
  | StatementList Statement {$$ = ast::action::AddToTail($1, $2); }
  ;
ConditionStmt
  : CompleteCondition { $$ = $1;}
  | IncompleteCondition {$$ = $1; }
  ;
CompleteCondition
  : "if" SimpleExpression "then" Statement "else" Statement {$$ = ast::action::GenericExpression<ast::Expression>({$2, $4, $6}, ast::ExpressionType::kIf, @1); }
  ;
IncompleteCondition
  : "if" SimpleExpression "then" Statement { \
      $$ = ast::action::GenericExpression<ast::Expression>({$2, $4}, ast::ExpressionType::kIf, @1); \
      }
  ;
IteratorStmt
  : "while" SimpleExpression "do" Statement { $$ = ast::action::GenericExpression<ast::Expression>({$2, $4}, ast::ExpressionType::kWhile, @1); }
  | "for" T_IDENTIFIER "=" IteratorRange "do" Statement { \
    $$ = ast::action::GenericExpression<ast::Expression>( \
    {std::make_shared<ast::VariableDecl>($2, ast::VariableType::kInt), $4, $6}, \
    ast::ExpressionType::kFor, @1); }
  ;
IteratorRange
  : SimpleExpression { $$ = $1; }
  | SimpleExpression "to" SimpleExpression { $$ = ast::action::GenericExpression<ast::Expression>({$1, $3}, ast::ExpressionType::kRange, @1); }
  | SimpleExpression "to" SimpleExpression "by" SimpleExpression { $$ = ast::action::GenericExpression<ast::Expression>({$1, $3, $5}, ast::ExpressionType::kRange, @1); }
  ;
ReturnStmt
  : "return" ";" { $$ = ast::action::GenericExpression<ast::Expression>({}, ast::ExpressionType::kReturn, @1); }
  | "return" Expression ";" { $$ = ast::action::GenericExpression<ast::Expression>({$2}, ast::ExpressionType::kReturn, @1); }
  ;
BreakStmt
  : "break" ";" { $$ = ast::action::GenericExpression<ast::Expression>({}, ast::ExpressionType::kBreak, @1); }
  ;
/*** Expressions ***/
Expression
  : Mutable "=" Expression { $$ = ast::action::GenericExpression<ast::OperationExpr>({$1, $3}, @2, ast::OperationType::kAssign); }   //ast::action::AssignOperation($1, $3, @2);  
  | Mutable OperAssign Expression { $$ = ast::action::GenericExpression<ast::OperationExpr>({$1, $3}, @2, $2); }
  | Mutable "++" { $$ = ast::action::GenericExpression<ast::OperationExpr>({$1}, @2, ast::OperationType::kIncrement); }
  | Mutable "--" { $$ = ast::action::GenericExpression<ast::OperationExpr>({$1}, @2, ast::OperationType::kDecrement); }
  | SimpleExpression { $$ = $1; }
  ;
OperAssign 
  : T_OP_ADDASS { $$ = ast::OperationType::kAddAss; }
  | T_OP_DIVASS { $$ = ast::OperationType::kDivAss; }
  | T_OP_MINASS { $$ = ast::OperationType::kMinAss; }
  | T_OP_MULASS { $$ = ast::OperationType::kMulAss; }
  ;
SimpleExpression 
  : SimpleExpression "or" AndExpr { $$ = ast::action::GenericExpression<ast::OperationExpr>({$1, $3}, @2, ast::OperationType::kLOr); }
  | AndExpr { $$ = $1; }
  ;
AndExpr
  : AndExpr "and" UnaryReletiveExpr { $$ = ast::action::GenericExpression<ast::OperationExpr>({$1, $3}, @2, ast::OperationType::kLAnd); }
  | UnaryReletiveExpr {$$ = $1; }
  ;
UnaryReletiveExpr
  : "not" UnaryReletiveExpr { $$ = ast::action::GenericExpression<ast::OperationExpr>({$2}, @1, ast::OperationType::kLNot); }
  | ReletiveExpr {$$ = $1; }
  ;
ReletiveExpr
  : MinMaxExp ReletiveOper MinMaxExp { $$ = ast::action::GenericExpression<ast::OperationExpr>({$1, $3}, @2, $2); }
  | MinMaxExp { $$ = $1; }
  ;
ReletiveOper
  : T_OP_LES_EQ { $$ = ast::OperationType::kLesEq; }
  | T_OP_LESS { $$ = ast::OperationType::kLess; }
  | T_OP_GREAT { $$ = ast::OperationType::kGreat; }
  | T_OP_GRE_EQ { $$ = ast::OperationType::kGreEq; }
  | T_OP_EQUALIVE { $$ = ast::OperationType::kEqualive; }
  | T_OP_NOT_EQUAL { $$ = ast::OperationType::kNEqualive; }
  ;
MinMaxExp
  : MinMaxExp MinMaxOper SumExpr { $$ = ast::action::GenericExpression<ast::OperationExpr>({$1, $3}, @2, $2); }
  | SumExpr {$$ = $1; }
  ;
MinMaxOper
  : T_OP_MIN { $$ = ast::OperationType::kMin; }
  | T_OP_MAX { $$ = ast::OperationType::kMax; }
  ;
SumExpr
  : SumExpr SumOper MulExp { $$ = ast::action::GenericExpression<ast::OperationExpr>({$1, $3}, @2, $2); }
  | MulExp {$$ = $1; }
  ;
SumOper
  : T_OP_PLUS { $$ = ast::OperationType::kAdd; }
  | T_OP_MINUS { $$ = ast::OperationType::kMinus; }
  ;
MulExp
  : MulExp MulOp UnaryExpr { $$ = ast::action::GenericExpression<ast::OperationExpr>({$1, $3}, @2, $2); }
  | UnaryExpr {$$ = $1; }
  ;
MulOp
  : T_OP_MULTI { $$ = ast::OperationType::kMulti; }
  | T_OP_DIVIDE { $$ = ast::OperationType::kDiv; }
  | T_OP_MODULO { $$ = ast::OperationType::kModulo; }
  ;
UnaryExpr
  : UnaryOper UnaryExpr { $$ = ast::action::UnaryExpr($1, $2, @1); }
  | Factor {$$ = $1; }
  ;
UnaryOper
  : T_OP_MINUS { $$ = ast::OperationType::kMinus; }
  | T_OP_MULTI { $$ = ast::OperationType::kMulti; }
  | T_OP_GENERATOR  { $$ = ast::OperationType::kGenerator; }
  ;
Factor
  : Immutable {$$ = $1;}
  | Mutable { $$ = $1; }
  ;
Mutable
  : T_IDENTIFIER { $$ = std::make_shared<ast::Identifier>($1);}
  | T_IDENTIFIER "[" Expression "]" { $$ = ast::action::GenericExpression<ast::OperationExpr>({std::make_shared<ast::Identifier>($1), $3}, @2, ast::OperationType::kBrack); }
  ;
Immutable
  : "(" Expression ")" { $$ = $2;}
  | Call     { $$ = $1; }
  | Constant { $$ = ast::action::ImmuteConstant($1); }
  ;
Call
  : T_IDENTIFIER "(" Arguments ")" { $$ = ast::action::CallExpr($1, $3); }
  ;
Arguments 
  : %empty {$$ = ast::node_pointer(); }
  | ArgumentList { $$ = $1; }
  ;
ArgumentList
  : ArgumentList "," Expression { $$ = ast::action::AddToTail($1, $3); }
  | Expression { $$ = $1; }
  ;
Constant
  : T_NUMCONST { $$ = $1; }
  | T_CHARCONST { $$ = $1; }
  | T_STRINGCONST {$$ = $1; }
  | T_BOOLCONST { $$ = $1; }
  ;
%%

void parser::CMinParser::error(const location_type &l, const std::string & error_message)
{
  out << "ERROR(" << l.begin.line << "): " << error_message << '\n';
}
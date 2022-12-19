/****************************************************/
/* File: tiny.y                                     */
/* The TINY Yacc/Bison specification file           */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/
%{
#define YYPARSER /* distinguishes Yacc output from other code files */

#include "globals.h"
#include "util.h"
#include "scan.h"
#include "parse.h"

#define YYSTYPE TreeNode *
static char * savedName; /* for use in assignments */
static int savedLineNo;  /* ditto */
static TreeNode * savedTree; /* stores syntax tree for later return */

static int yyerror(char * message);
static int yylex(void);

%}

/*
%token IF THEN ELSE END REPEAT UNTIL READ WRITE
%token ID NUM 
%token ASSIGN EQ LT PLUS MINUS TIMES OVER LPAREN RPAREN SEMI
%token ERROR 
*/
/* reserved words */
%token IF ELSE INT RETURN VOID WHILE
/* multicharacter tokens */
%token ID NUM 
/* special symbols */
%token PLUS MINUS TIMES OVER 
%token LT LE GT GE EQ NE
%token ASSIGN 
%token SEMI COMMA 
%token LPAREN RPAREN LCURLY RCURLY LBRACKET RBRACKET  

%token ERROR
%token COMMENT COMMENTERROR

/* for resolving shift-reduce conflict */
%nonassoc RPAREN 
%nonassoc ELSE

%start program


%% /* Grammar for TINY */

/*
program     : stmt_seq
                 { savedTree = $1;} 
            ;
stmt_seq    : stmt_seq SEMI stmt
                 { YYSTYPE t = $1;
                   if (t != NULL)
                   { while (t->sibling != NULL)
                        t = t->sibling;
                     t->sibling = $3;
                     $$ = $1; }
                     else $$ = $3;
                 }
            | stmt  { $$ = $1; }
            ;
stmt        : if_stmt { $$ = $1; }
            | repeat_stmt { $$ = $1; }
            | assign_stmt { $$ = $1; }
            | read_stmt { $$ = $1; }
            | write_stmt { $$ = $1; }
            | error  { $$ = NULL; }
            ;
if_stmt     : IF exp THEN stmt_seq END
                 { $$ = newStmtNode(IfK);
                   $$->child[0] = $2;
                   $$->child[1] = $4;
                 }
            | IF exp THEN stmt_seq ELSE stmt_seq END
                 { $$ = newStmtNode(IfK);
                   $$->child[0] = $2;
                   $$->child[1] = $4;
                   $$->child[2] = $6;
                 }
            ;
repeat_stmt : REPEAT stmt_seq UNTIL exp
                 { $$ = newStmtNode(RepeatK);
                   $$->child[0] = $2;
                   $$->child[1] = $4;
                 }
            ;
assign_stmt : ID { savedName = copyString(tokenString);
                   savedLineNo = lineno; }
              ASSIGN exp
                 { $$ = newStmtNode(AssignK);
                   $$->child[0] = $4;
                   $$->attr.name = savedName;
                   $$->lineno = savedLineNo;
                 }
            ;
read_stmt   : READ ID
                 { $$ = newStmtNode(ReadK);
                   $$->attr.name =
                     copyString(tokenString);
                 }
            ;
write_stmt  : WRITE exp
                 { $$ = newStmtNode(WriteK);
                   $$->child[0] = $2;
                 }
            ;
exp         : simple_exp LT simple_exp 
                 { $$ = newExpNode(OpK);
                   $$->child[0] = $1;
                   $$->child[1] = $3;
                   $$->attr.op = LT;
                 }
            | simple_exp EQ simple_exp
                 { $$ = newExpNode(OpK);
                   $$->child[0] = $1;
                   $$->child[1] = $3;
                   $$->attr.op = EQ;
                 }
            | simple_exp { $$ = $1; }
            ;
simple_exp  : simple_exp PLUS term 
                 { $$ = newExpNode(OpK);
                   $$->child[0] = $1;
                   $$->child[1] = $3;
                   $$->attr.op = PLUS;
                 }
            | simple_exp MINUS term
                 { $$ = newExpNode(OpK);
                   $$->child[0] = $1;
                   $$->child[1] = $3;
                   $$->attr.op = MINUS;
                 } 
            | term { $$ = $1; }
            ;
term        : term TIMES factor 
                 { $$ = newExpNode(OpK);
                   $$->child[0] = $1;
                   $$->child[1] = $3;
                   $$->attr.op = TIMES;
                 }
            | term OVER factor
                 { $$ = newExpNode(OpK);
                   $$->child[0] = $1;
                   $$->child[1] = $3;
                   $$->attr.op = OVER;
                 }
            | factor { $$ = $1; }
            ;
factor      : LPAREN exp RPAREN
                 { $$ = $2; }
            | NUM
                 { $$ = newExpNode(ConstK);
                   $$->attr.val = atoi(tokenString);
                 }
            | ID { $$ = newExpNode(IdK);
                   $$->attr.name =
                         copyString(tokenString);
                 }
            | error { $$ = NULL; }
            ;
*/


/* 1 */
program     : decl_list { savedTree = $1; }
            ;
identifier  : ID { 
		savedName = copyString(tokenString); 
		savedLineNo = lineno;		
		}
            ;

/* 2 */
decl_list   : decl_list decl
                { YYSTYPE t = $1;
                  if (t != NULL)
                    {
                      while (t->sibling) t = t->sibling;
                      t->sibling = $2;
                      $$ = $1;
                    }
                  else
                    $$ = $2;
                }
            | decl
                { $$ = $1; }
            ;

/* 3 */
decl        : var_decl { $$ = $1; }
            | func_decl { $$ = $1; }
            ;

/* 4 */
var_decl    : type_spec identifier SEMI
                { $$ = newDeclNode(VarK);
                  $$->attr.name = savedName;
                  $$->child[0] = $1;
                }
            | type_spec identifier
                { $$ = newDeclNode(VarArrK);
                  $$->attr.arrAttr.name = savedName;
                  $$->child[0] = $1;
                }
              LBRACKET NUM 
                { $$ = $3;
                  $$->attr.arrAttr.len = atoi(tokenString); 
                }
              RBRACKET SEMI
                { $$ = $6; }
            ;

/* 5 */
type_spec   : INT 
                { $$ = newTypeNode(IntK);
                  $$->attr.val = INT;
                }
            | VOID 
                { $$ = newTypeNode(VoidK);
                  $$->attr.val = VOID;
                }
            ;

/* 6 */
func_decl   : type_spec identifier
                { $$ = newDeclNode(FuncK);
                  $$->attr.name = savedName;
                }
              LPAREN params RPAREN comp_stmt
                { $$ = $3;
                  $$->child[0] = $1;
                  $$->child[1] = $5;
                  $$->child[2] = $7;
                }
            ;

/* 7 */
params      : param_list
                { $$ = $1; }
            | VOID
		{ $$=NULL; }
            ;

/* 8 */
param_list  : param_list COMMA param
                { YYSTYPE t = $1;
                  if (t != NULL)
                    {
                      while (t->sibling)
                        t = t->sibling;
                      t->sibling = $3;
                      $$ = $1;
                    }
                  else
                    $$ = $3;
                }
            | param
                { $$ = $1; }
            ;

/* 9 */
param       : type_spec identifier
                { $$ = newDeclNode(ParamK);
                  $$->attr.name = savedName;
                  $$->child[0] = $1;
                }
            | type_spec identifier LBRACKET RBRACKET
                { $$ = newDeclNode(ParamArrK);
                  $$->attr.arrAttr.name = savedName;
                  $$->attr.arrAttr.len = -1;
                }
            ;

/* 10 */
comp_stmt   : LCURLY local_decls stmt_list RCURLY
                { $$ = newStmtNode(CompK);
                  $$->child[0] = $2;
                  $$->child[1] = $3;
                }
            ;


/* 11 */
local_decls : local_decls var_decl
                { YYSTYPE t = $1;
                  if (t != NULL)
                    {
                      while (t->sibling)
                        t = t->sibling;
                      t->sibling = $2;
                      $$ = $1;
                    }
                  else
                    $$ = $2;
                }
            | empty
                { $$ = $1; }
            ;

/* 12 */
stmt_list   : stmt_list stmt
                { YYSTYPE t = $1;
                  if (t != NULL)
                    {
                      while (t->sibling)
                        t = t->sibling;
                      t->sibling = $2;
                      $$ = $1;
                    }
                  else
                    $$ = $2;
                }
            | empty
                { $$ = $1; }
            ;

/* 13 */
stmt        : expr_stmt   
		{ $$ = $1; }
            | comp_stmt   
		{ $$ = $1; }
            | select_stmt 
		{ $$ = $1; }
            | iter_stmt   
		{ $$ = $1; }
            | ret_stmt    
		{ $$ = $1; }
            ;

/* 14 */
expr_stmt   : expr SEMI { $$ = $1; }
            | SEMI      { $$ = NULL; }
            ;

/* 15 */
select_stmt : IF LPAREN expr RPAREN stmt
		{
		  $$ = newStmtNode(SelectK);
		  $$->child[0] = $3;
		  $$->child[1] = $5;
		}
            | IF LPAREN expr RPAREN stmt ELSE stmt
                { $$ = newStmtNode(SelectK);
                  $$->child[0] = $3;
                  $$->child[1] = $5;
                  $$->child[2] = $7;
                }
            ;

/* 16 */
iter_stmt   : WHILE LPAREN expr RPAREN stmt
                { $$ = newStmtNode(IterK);
                  $$->child[0] = $3;
                  $$->child[1] = $5;
                }
            ;

/* 17 */
ret_stmt    : RETURN SEMI
                { $$ = newStmtNode(RetK); }
            | RETURN expr SEMI
                { $$ = newStmtNode(RetK);
                  $$->child[0] = $2;
                }
            ;

/* 18 */
expr        : var ASSIGN expr
                { $$ = newExpNode(AssignK);
                  $$->child[0] = $1;
                  $$->child[1] = $3;
                }
            | simple_expr
                { $$ = $1; }
            ;

/* 19 */
var         : identifier
                { $$ = newExpNode(IdK);
                  $$->attr.name = savedName;
                }
            | identifier
                { $$ = newExpNode(IdArrK);
                  $$->attr.name = savedName;
                }
              LBRACKET expr RBRACKET
                { $$ = $2;
                  $$->child[0] = $4; 
                }
            ;

/* 20 */
simple_expr : add_expr relop add_expr
                { 
		$$ = newExpNode(SimpK);
		$$->child[0] = $1;
		$$->child[1] = $2;
		$$->child[2] = $3;
                }
            | add_expr
                { $$ = $1; }
            ;


/* 21 */
relop       : LE
                { $$ = newExpNode(OpK);
                  $$->attr.op = LE;
                }
            | LT
                { $$ = newExpNode(OpK);
                  $$->attr.op = LT;
                }
            | GT
                { $$ = newExpNode(OpK);
                  $$->attr.op = GT;
                }
            | GE
                { $$ = newExpNode(OpK);
                  $$->attr.op = GE;
                }
            | EQ
                { $$ = newExpNode(OpK);
                  $$->attr.op = EQ;
                }
            | NE
                { $$ = newExpNode(OpK);
                  $$->attr.op = NE;
                }
            ;

/* 22 */
add_expr    : add_expr addop term
                { 
		  $$ = newExpNode(AddK);
                  $$->child[0] = $1;
                  $$->child[1] = $2;
		  $$->child[2] = $3;
                }
            | term
                { $$ = $1; }
            ;

/* 23 */
addop       : PLUS
                { $$ = newExpNode(OpK);
                  $$->attr.op = PLUS;
                }
            | MINUS
                { $$ = newExpNode(OpK);
                  $$->attr.op = MINUS;
                }
            ;

/* 24 */
term        : term mulop factor
                { $$ = $2;
                  $$->child[0] = $1;
                  $$->child[1] = $3;
                }
            | factor
                { $$ = $1; }
            ;

/* 25 */
mulop       : TIMES
                { $$ = newExpNode(OpK);
                  $$->attr.op = TIMES;
                }
            | OVER
                { $$ = newExpNode(OpK);
                  $$->attr.op = OVER;
                }
            ;

/* 26 */
factor      : LPAREN expr RPAREN
                { $$ = $2; }
            | var
                { $$ = $1; }
            | call
                { $$ = $1; }
            | NUM
                { $$ = newExpNode(ConstK);
                  $$->attr.val = atoi(tokenString);
                }
            ;

/* 27 */
call        : identifier
                { $$ = newExpNode(CallK);
                  $$->attr.name = savedName;
                }
              LPAREN args RPAREN
                { $$ = $2;
                  $$->child[0] = $4; 
                }
            ;

/* 28 */
args        : arg_list  { $$ = $1; }
            | empty     { $$ = $1; }
            ;

/* 29 */
arg_list    : arg_list COMMA expr
                { YYSTYPE t = $1;
                  if (t != NULL)
                    {
                      while (t->sibling)
                        t = t->sibling;
                      t->sibling = $3;
                      $$ = $1;
                    }
                  else
                    $$ = $3;
                }
            | expr
                { $$ = $1; }
            ;

empty       : { $$ = NULL; }
            ;

%%

int yyerror(char * message)
{ fprintf(listing,"Syntax error at line %d: %s\n",lineno,message);
  fprintf(listing,"Current token: ");
  printToken(yychar,tokenString);
  Error = TRUE;
  return 0;
}

/* yylex calls getToken to make Yacc/Bison output
 * compatible with ealier versions of the TINY scanner
 */
/*
static int yylex(void)
{ return getToken(); }
*/

static int yylex(void)
{
  int token = getToken();
  while (token == COMMENT)
    token = getToken();
  return token;
}

TreeNode * parse(void)
{ yyparse();
  return savedTree;
}


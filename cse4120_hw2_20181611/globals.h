/****************************************************/
/* File: globals.h                                  */
/* Global types and vars for TINY compiler          */
/* must come before other include files             */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/

#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif


#define YYDEBUG 1

#ifndef YYPARSER
#include "tiny.tab.h"
#define ENDFILE 0
#endif

typedef int TokenType;


/* MAXRESERVED = the number of reserved words */
#define MAXRESERVED 6

//typedef enum 
//    /* book-keeping tokens */
//   {ENDFILE,ERROR,COMMENTERROR,
//    /* reserved words */
//    //IF,THEN,ELSE,END,REPEAT,UNTIL,READ,WRITE,
//    ELSE,IF,INT,RETURN,VOID,WHILE,
//    /* multicharacter tokens */
//    ID,NUM,
//    /* special symbols */
//    //ASSIGN,EQ,LT,PLUS,MINUS,TIMES,OVER,LPAREN,RPAREN,SEMI
//    PLUS,MINUS,TIMES,OVER,LT,LE,GT,GE,EQ,NE,ASSIGN,SEMI,COMMA,LPAREN,RPAREN,LBRACKET,RBRACKET,LCURLY,RCURLY   
//} TokenType;

extern FILE* source; /* source code text file */
extern FILE* listing; /* listing output text file */
extern FILE* code; /* code text file for TM simulator */

extern int lineno; /* source line number for listing */

/**************************************************/
/***********   Syntax tree for parsing ************/
/**************************************************/

//typedef enum {StmtK,ExpK} NodeKind;
//typedef enum {IfK,RepeatK,AssignK,ReadK,WriteK} StmtKind;
//typedef enum {OpK,ConstK,IdK} ExpKind;
typedef enum {StmtK, ExpK, DeclK, TypeK} NodeKind;
typedef enum {CompK, ExprK, SelectK, IterK, RetK} StmtKind;
typedef enum {AssignK, OpK, ConstK, IdK, IdArrK, CallK, SimpK, AddK} ExpKind;
typedef enum {FuncK, VarK, ParamK, VarArrK, ParamArrK} DeclKind;
typedef enum {VoidK, IntK} TypeKind;


/* ExpType is used for type checking */
//typedef enum {Void,Integer,Boolean} ExpType;
typedef enum {Void, Integer} ExpType;


#define MAXCHILDREN 3


//typedef struct treeNode
//   { struct treeNode * child[MAXCHILDREN];
//     struct treeNode * sibling;
//     int lineno;
//     NodeKind nodekind;
//    union { StmtKind stmt; ExpKind exp;} kind;
//    union { TokenType op;
//             int val;
//             char * name; } attr;
//     ExpType type; /* for type checking of exps */
//   } TreeNode;


typedef struct arrayAttr
  {
    char *name;
    int len;
  } ArrayAttr;

typedef struct treeNode
   { struct treeNode * child[MAXCHILDREN];
     struct treeNode * sibling;
     int lineno;
     NodeKind nodekind;
     union { StmtKind stmt;
             ExpKind exp; 
             DeclKind decl; 
             TypeKind type; } kind;
     union { TokenType op;
             int val;
             char * name;
             ArrayAttr arrAttr; } attr;
     ExpType type; /* for type checking of exps */
   } TreeNode;


/**************************************************/
/***********   Flags for tracing       ************/
/**************************************************/

/* EchoSource = TRUE causes the source program to
 * be echoed to the listing file with line numbers
 * during parsing
 */
extern int EchoSource;

/* TraceScan = TRUE causes token information to be
 * printed to the listing file as each token is
 * recognized by the scanner
 */
extern int TraceScan;

/* TraceParse = TRUE causes the syntax tree to be
 * printed to the listing file in linearized form
 * (using indents for children)
 */
extern int TraceParse;

/* TraceAnalyze = TRUE causes symbol table inserts
 * and lookups to be reported to the listing file
 */
extern int TraceAnalyze;

/* TraceCode = TRUE causes comments to be written
 * to the TM code file as code is generated
 */
extern int TraceCode;

/* Error = TRUE prevents further passes if an error occurs */
extern int Error; 
#endif

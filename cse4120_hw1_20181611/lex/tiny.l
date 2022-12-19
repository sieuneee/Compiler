/****************************************************/
/* File: tiny.l                                     */
/* Lex specification for TINY                       */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/

%{
#include "globals.h"
#include "util.h"
#include "scan.h"
/* lexeme of identifier or reserved word */
char tokenString[MAXTOKENLEN+1];
%}

digit       [0-9]
number      {digit}+
letter      [a-zA-Z]
identifier  {letter}+
newline     \n
whitespace  [ \t]+
nonidnum    ({letter}+{digit}|{digit}+{letter})({letter}|{digit})*
%%

"else"		{return ELSE;}
"if"            {return IF;}
"int"		{return INT;}
"return"	{return RETURN;}
"void"		{return VOID;}
"while"		{return WHILE;}

"+"             {return PLUS;}
"-"             {return MINUS;}
"*"             {return TIMES;}
"/"             {return OVER;}
"<"             {return LT;}
"<="            {return LE;}
">"             {return GT;}
">="            {return GE;}
"=="		{return EQ;}
"!="		{return NE;}
"="		{return ASSIGN;}
";"             {return SEMI;}
","             {return COMMA;}
"("		{return LPAREN;}
")"		{return RPAREN;}
"["		{return LBRACKET;}
"]"		{return RBRACKET;}
"{"		{return LCURLY;}
"}"		{return RCURLY;}

{identifier}    {return ID;}
{number}	{return NUM;}
{newline}	{lineno++;}
{whitespace}	{/*skip whitespace */}
.		{return ERROR;}
{nonidnum}      {return ERROR;}
"/*" 		{
		    char b, c;
		    int err = TRUE;
   		    while((c=input())!=EOF){
        		if(c == '\n'){
	            		lineno++;
	        	} else if (c == '/'){
	            		if(b == '*') { err = FALSE; break; }
	        	}
	        	b = c;
	    	    }
		    if(err==TRUE) {
			return COMMENTERROR;
		    }
		}
"*/"		{ return COMMENTERROR; }
<<EOF>>		{ return ENDFILE; }
%%

TokenType getToken(void)
{ static int firstTime = TRUE;
  TokenType currentToken;
  if (firstTime)
  { firstTime = FALSE;
    lineno++;
    yyin = source;
    yyout = listing; 
  }
  currentToken = yylex();
  strncpy(tokenString,yytext,MAXTOKENLEN);
  if (TraceScan) {
    fprintf(listing,"\t%d\t\t\t",lineno);
    printToken(currentToken,tokenString);
  }
  return currentToken;
}


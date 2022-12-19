/****************************************************/
/* File: util.c                                     */
/* Utility function implementation                  */
/* for the TINY compiler                            */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/

#include "globals.h"
#include "util.h"

/* Procedure printToken prints a token 
 * and its lexeme to the listing file
 */
void printToken( TokenType token, const char* tokenString )
{
switch (token) {
    case ELSE: 
	fprintf(listing, "%s\t\t\t%s\n", "ELSE", tokenString); 
	break;
    case IF: 
	fprintf(listing, "%s\t\t\t%s\n", "IF", tokenString); 
	break;
    case INT: 
	fprintf(listing, "%s\t\t\t%s\n", "INT", tokenString); 
	break;
    case RETURN: 
	fprintf(listing, "%s\t\t\t%s\n", "RETURN", tokenString); 
	break;
    case VOID: 
	fprintf(listing, "%s\t\t\t%s\n", "VOID", tokenString); 
	break;
    case WHILE: 
	fprintf(listing, "%s\t\t\t%s\n", "WHILE", tokenString); 
	break;
    case PLUS: 
	fprintf(listing,"+\t\t\t+\n"); 
	break;
    case MINUS: 
	fprintf(listing,"-\t\t\t-\n"); 
	break;
    case TIMES: 
	fprintf(listing,"*\t\t\t*\n"); 
	break;
    case OVER: 
	fprintf(listing,"/\t\t\t/\n"); 
	break;
    case LT: 
	fprintf(listing,"<\t\t\t<\n"); 
	break;
    case LE: 
	fprintf(listing,"<=\t\t\t<=\n"); 
	break;  
    case GT: 
	fprintf(listing,">\t\t\t>\n"); 
	break;
    case GE: 
	fprintf(listing,">=\t\t\t>=\n"); 
	break;
    case EQ: 
	fprintf(listing,"==\t\t\t==\n"); 
	break;
    case NE: 
	fprintf(listing,"!=\t\t\t!=\n"); 
	break;
    case ASSIGN: 
	fprintf(listing,"=\t\t\t=\n"); 
	break;
    case SEMI: 
	fprintf(listing,";\t\t\t;\n"); 
	break;
    case COMMA: 
	fprintf(listing,",\t\t\t,\n"); 
	break;
    case LPAREN: 
	fprintf(listing,"(\t\t\t(\n"); 
	break;
    case RPAREN: 
	fprintf(listing,")\t\t\t)\n"); 
	break;
    case LBRACKET: 
	fprintf(listing,"[\t\t\t[\n"); 
	break;
    case RBRACKET: 
	fprintf(listing,"]\t\t\t]\n"); 
	break;
    case LCURLY: 
	fprintf(listing,"{\t\t\t{\n"); 
	break;
    case RCURLY: 
	fprintf(listing,"}\t\t\t}\n"); 
	break;
    case ID:
        fprintf(listing,"ID\t\t\t%s\n",tokenString);
        break;
    case NUM:
        fprintf(listing,"NUM\t\t\t%s\n",tokenString);
        break;
    case ENDFILE:
        fprintf(listing,"EOF\n");
        break;
    case ERROR:
        fprintf(listing,"ERROR\t\t\t%s\n",tokenString);
        break;
    case COMMENTERROR: 
	fprintf(listing,"ERROR\t\t\tComment Error\n");
	break;
    default: 
	fprintf(listing,"Unknown token: %d\n",token);
  }

  /*{ case IF:
    case THEN:
    case ELSE:
    case END:
    case REPEAT:
    case UNTIL:
    case READ:
    case WRITE:
      fprintf(listing,
         "reserved word: %s\n",tokenString);
      break;
    case ASSIGN: fprintf(listing,":=\n"); break;
    case LT: fprintf(listing,"<\n"); break;
    case EQ: fprintf(listing,"=\n"); break;
    case LPAREN: fprintf(listing,"(\n"); break;
    case RPAREN: fprintf(listing,")\n"); break;
    case SEMI: fprintf(listing,";\n"); break;
    case PLUS: fprintf(listing,"+\n"); break;
    case MINUS: fprintf(listing,"-\n"); break;
    case TIMES: fprintf(listing,"*\n"); break;
    case OVER: fprintf(listing,"/\n"); break;
    case ENDFILE: fprintf(listing,"EOF\n"); break;
    case NUM:
      fprintf(listing,
          "NUM, val= %s\n",tokenString);
      break;
    case ID:
      fprintf(listing,
          "ID, name= %s\n",tokenString);
      break;
    case ERROR:
      fprintf(listing,
          "ERROR: %s\n",tokenString);
      break;
    default:
      fprintf(listing,"Unknown token: %d\n",token);
  }*/
}

/* Function newStmtNode creates a new statement
 * node for syntax tree construction
 */
TreeNode * newStmtNode(StmtKind kind)
{ TreeNode * t = (TreeNode *) malloc(sizeof(TreeNode));
  int i;
  if (t==NULL)
    fprintf(listing,"Out of memory error at line %d\n",lineno);
  else {
    for (i=0;i<MAXCHILDREN;i++) t->child[i] = NULL;
    t->sibling = NULL;
    t->nodekind = StmtK;
    t->kind.stmt = kind;
    t->lineno = lineno;
  }
  return t;
}

/* Function newExpNode creates a new expression 
 * node for syntax tree construction
 */
TreeNode * newExpNode(ExpKind kind)
{ TreeNode * t = (TreeNode *) malloc(sizeof(TreeNode));
  int i;
  if (t==NULL)
    fprintf(listing,"Out of memory error at line %d\n",lineno);
  else {
    for (i=0;i<MAXCHILDREN;i++) t->child[i] = NULL;
    t->sibling = NULL;
    t->nodekind = ExpK;
    t->kind.exp = kind;
    t->lineno = lineno;
  }
  return t;
}



TreeNode * newDeclNode(DeclKind kind)
{ TreeNode * t = (TreeNode *) malloc(sizeof(TreeNode));
  int i;
  if (t==NULL)
    fprintf(listing,"Out of memory error at line %d\n",lineno);
  else {
    for (i=0;i<MAXCHILDREN;i++) t->child[i] = NULL;
    t->sibling = NULL;
    t->nodekind = DeclK;
    t->kind.decl = kind;
    t->lineno = lineno;
  }
  return t;
}


TreeNode * newTypeNode(TypeKind kind)
{ TreeNode * t = (TreeNode *) malloc(sizeof(TreeNode));
  int i;
  if (t==NULL)
    fprintf(listing,"Out of memory error at line %d\n",lineno);
  else {
    for (i=0;i<MAXCHILDREN;i++) t->child[i] = NULL;
    t->sibling = NULL;
    t->nodekind = TypeK;
    t->kind.type = kind;
    t->lineno = lineno;
  }
  return t;
}



/* Function copyString allocates and makes a new
 * copy of an existing string
 */
char * copyString(char * s)
{ int n;
  char * t;
  if (s==NULL) return NULL;
  n = strlen(s)+1;
  t = malloc(n);
  if (t==NULL)
    fprintf(listing,"Out of memory error at line %d\n",lineno);
  else strcpy(t,s);
  return t;
}

/* Variable indentno is used by printTree to
 * store current number of spaces to indent
 */
static int indentno = 0;

/* macros to increase/decrease indentation */
#define INDENT indentno+=2
#define UNINDENT indentno-=2

/* printSpaces indents by printing spaces */
static void printSpaces(void)
{ int i;
  for (i=0;i<indentno;i++)
    fprintf(listing," ");
}

/* procedure printTree prints a syntax tree to the 
 * listing file using indentation to indicate subtrees
 */

/*
void printTree( TreeNode * tree )
{ int i;
  INDENT;
  while (tree != NULL) {
    printSpaces();
    if (tree->nodekind==StmtK)
    { switch (tree->kind.stmt) {
        case IfK:
          fprintf(listing,"If\n");
          break;
        case RepeatK:
          fprintf(listing,"Repeat\n");
          break;
        case AssignK:
          fprintf(listing,"Assign to: %s\n",tree->attr.name);
          break;
        case ReadK:
          fprintf(listing,"Read: %s\n",tree->attr.name);
          break;
        case WriteK:
          fprintf(listing,"Write\n");
          break;
        default:
          fprintf(listing,"Unknown ExpNode kind\n");
          break;
      }
    }
    else if (tree->nodekind==ExpK)
    { switch (tree->kind.exp) {
        case OpK:
          fprintf(listing,"Op: ");
          printToken(tree->attr.op,"\0");
          break;
        case ConstK:
          fprintf(listing,"Const: %d\n",tree->attr.val);
          break;
        case IdK:
          fprintf(listing,"Id: %s\n",tree->attr.name);
          break;
        default:
          fprintf(listing,"Unknown ExpNode kind\n");
          break;
      }
    }
    else fprintf(listing,"Unknown node kind\n");
    for (i=0;i<MAXCHILDREN;i++)
         printTree(tree->child[i]);
    tree = tree->sibling;
  }
  UNINDENT;
}

*/
static void printOp(TokenType op)
{ switch (op)
    { 
    case PLUS: 
	fprintf(listing,"+\n"); break;
    case MINUS: 
	fprintf(listing,"-\n"); break;
    case TIMES: 
	fprintf(listing,"*\n"); break;
    case OVER: 
	fprintf(listing,"/\n"); break;
    case LT: 
	fprintf(listing,"<\n"); break;
    case LE: 
	fprintf(listing,"<=\n"); break;
    case GT: 
	fprintf(listing,">\n"); break;
    case GE: 
	fprintf(listing,">=\n"); break;
    case EQ: 
	fprintf(listing,"==\n"); break;
    case NE: 
	fprintf(listing,"!=\n"); break;
    default: 
	fprintf(listing,"Unknown op: %d\n", op);
    }
}


void printTree( TreeNode * tree )
{ int i;
  INDENT;
  while (tree != NULL) {
    printSpaces();
    if (tree->nodekind==StmtK)
    { switch (tree->kind.stmt) {
        case CompK:
          fprintf(listing,"Compound Statement\n");
          break;
        case SelectK:
          fprintf(listing,"If\n");
          break;
        case IterK:
          fprintf(listing,"Iteration Statement\n");
          break;
        case RetK:
          fprintf(listing,"Return Statement\n");
          break;
        default:
          fprintf(listing,"Unknown StmtNode kind\n");
          break;
      }
    }
    else if (tree->nodekind==ExpK)
    { switch (tree->kind.exp) {
        case AssignK:
          fprintf(listing,"Assign: =\n");
          break;
        case OpK:
          fprintf(listing,"Operator: "); printOp(tree->attr.op);
          break;
        case ConstK:
          fprintf(listing,"Constant: %d\n", tree->attr.val);
          break;
        case IdK:
          fprintf(listing,"Variable: %s\n", tree->attr.name);
          break;
        case IdArrK:
          fprintf(listing,"Id Of Array: %s\n", tree->attr.name);
          break;
        case CallK:
          fprintf(listing,"Call Function: %s\n", tree->attr.name);
          break;
	case SimpK:
	  fprintf(listing, "Simple Expression\n");
	  break;
	case AddK:
	  fprintf(listing, "Additive Expression\n");
	  break;
        default:
          fprintf(listing,"Unknown ExpNode kind\n");
          break;
      }
    }
    else if (tree->nodekind==DeclK)
    { switch (tree->kind.decl) {
        case FuncK:
          fprintf(listing,"Function Declare: %s\n", tree->attr.name);
          break;
        case VarK:
          fprintf(listing,"Variable Declare: %s\n", tree->attr.name);
          break;
	case ParamK:
	  fprintf(listing, "Parameter: %s\n", tree->attr.name);        
	  break;
	case VarArrK:
            fprintf(listing, "Array Declare: name = %s, size=%d\n", tree->attr.arrAttr.name, tree->attr.arrAttr.len);
          break;
	case ParamArrK:
            fprintf(listing, "Array Parameter: name = %s\n", tree->attr.arrAttr.name);
          break;
        default:
          fprintf(listing,"Unknown DeclNode kind\n");
          break;
      }
    }
    else if (tree->nodekind==TypeK)
    { 
      switch (tree->kind.type)
        {
        case IntK:
          fprintf(listing, "Type: int\n");
          break;
        case VoidK:
          fprintf(listing, "Type: void\n");
          break;
        }
    }
    else fprintf(listing,"Unknown node kind\n");
    for (i=0;i<MAXCHILDREN;i++)
         printTree(tree->child[i]);
    tree = tree->sibling;
  }
  UNINDENT;
}



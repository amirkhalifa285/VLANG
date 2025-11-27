
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     INT = 258,
     ID = 259,
     STRING = 260,
     SCL = 261,
     VEC = 262,
     LOOP = 263,
     IF = 264,
     PRINT = 265,
     LBRACE = 266,
     RBRACE = 267,
     LPAREN = 268,
     RPAREN = 269,
     LBRACK = 270,
     RBRACK = 271,
     COLON = 272,
     SEMICOLON = 273,
     COMMA = 274,
     ASSIGN = 275,
     PLUS = 276,
     MINUS = 277,
     TIMES = 278,
     DIVIDE = 279,
     DOTPROD = 280,
     UNKNOWN = 281,
     EQ = 282,
     NE = 283,
     LT = 284,
     LE = 285,
     GT = 286,
     GE = 287
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 1676 of yacc.c  */
#line 74 "parser.y"

    int    ival;
    char  *sval;
    struct{
        char *setup;          /* C stmts that must run first */
        char *code;           /* the C expression itself    */
        char *left,*right;    /* raw operands (analysis)    */
        char  op;             /* '+','-','*','/','@',0      */
    } expr;
    struct{
        char *setup;          /* setup for print list */
        char *code;           /* comma‑separated args */
        int   count;          /* number of args       */
    } plist;
    char *blockcode;          /* generated C for stmt/block */



/* Line 1676 of yacc.c  */
#line 103 "parser.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;



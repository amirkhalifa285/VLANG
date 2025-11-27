
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 1 "vlang.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symTab.h"

extern int yylex();
void yyerror(const char *s);

// Code generation functions
void generate_code(ast_node *node);
void generate_declaration(ast_node *node);
void generate_assignment(ast_node *node);
void generate_expression(ast_node *node);
void generate_print(ast_node *node);
void generate_if(ast_node *node);
void generate_loop(ast_node *node);
void generate_vec_literal(ast_node *node);
void generate_vec_assignment(char *var_name, ast_node *vec_node, int size);
void generate_vec_assignment_with_declaration(char *var_name, ast_node *vec_node, int size);
void generate_scalar_assignment_with_declaration(char *var_name, ast_node *expr_node);
void generate_code_with_declarations(ast_node *node);
void declare_variable_if_needed(char *var_name);
void collect_int_list_values(ast_node *node, char **values, int *count, int max_size);
void generate_dot_product(ast_node *node);
void generate_print_expressions(ast_node *node);

static int temp_var_count = 0;
static int label_count = 0;
static int declared_vars[100] = {0}; // Track which variables have been declared
static FILE *output_file = NULL; // Global file pointer for code generation

#define YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{
    int ival;
    char *sval;
    ast_node *node;
} YYSTYPE;



/* Line 189 of yacc.c  */
#line 116 "y.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     SCL = 258,
     VEC = 259,
     IF = 260,
     LOOP = 261,
     PRINT = 262,
     ID = 263,
     STRING_LITERAL = 264,
     INT_LITERAL = 265,
     AT = 266,
     ADD = 267,
     SUB = 268,
     MUL = 269,
     DIV = 270,
     ASSIGN = 271,
     LBRACE = 272,
     RBRACE = 273,
     LPAREN = 274,
     RPAREN = 275,
     LBRACK = 276,
     RBRACK = 277,
     COLON = 278,
     SEMI = 279,
     COMMA = 280
   };
#endif
/* Tokens.  */
#define SCL 258
#define VEC 259
#define IF 260
#define LOOP 261
#define PRINT 262
#define ID 263
#define STRING_LITERAL 264
#define INT_LITERAL 265
#define AT 266
#define ADD 267
#define SUB 268
#define MUL 269
#define DIV 270
#define ASSIGN 271
#define LBRACE 272
#define RBRACE 273
#define LPAREN 274
#define RPAREN 275
#define LBRACK 276
#define RBRACK 277
#define COLON 278
#define SEMI 279
#define COMMA 280




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 43 "vlang.y"

    int ival;
    char *sval;
    ast_node *node;



/* Line 214 of yacc.c  */
#line 210 "y.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 222 "y.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  18
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   75

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  26
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  16
/* YYNRULES -- Number of rules.  */
#define YYNRULES  36
/* YYNRULES -- Number of states.  */
#define YYNSTATES  76

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   280

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     5,     9,    12,    14,    17,    19,    21,
      23,    25,    27,    31,    38,    43,    50,    54,    58,    64,
      66,    70,    72,    76,    80,    82,    86,    90,    94,    96,
      98,   100,   104,   108,   112,   118,   120
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      27,     0,    -1,    28,    -1,    17,    29,    18,    -1,    17,
      18,    -1,    30,    -1,    29,    30,    -1,    31,    -1,    32,
      -1,    33,    -1,    34,    -1,    35,    -1,     3,     8,    24,
      -1,     4,     8,    17,    10,    18,    24,    -1,     8,    16,
      37,    24,    -1,     8,    23,    39,    16,    37,    24,    -1,
       5,    37,    28,    -1,     6,    37,    28,    -1,     7,     9,
      23,    36,    24,    -1,    37,    -1,    36,    25,    37,    -1,
      38,    -1,    37,    12,    38,    -1,    37,    13,    38,    -1,
      39,    -1,    38,    14,    39,    -1,    38,    15,    39,    -1,
      38,    11,    39,    -1,    10,    -1,    40,    -1,     8,    -1,
       8,    23,    39,    -1,    19,    37,    20,    -1,    21,    10,
      22,    -1,    21,    10,    25,    41,    22,    -1,    10,    -1,
      41,    25,    10,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    66,    66,    70,    71,    75,    76,    80,    81,    82,
      83,    84,    88,    89,    93,    94,    98,   102,   106,   112,
     113,   117,   118,   119,   123,   124,   125,   126,   130,   131,
     132,   133,   134,   140,   141,   145,   146
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "SCL", "VEC", "IF", "LOOP", "PRINT",
  "ID", "STRING_LITERAL", "INT_LITERAL", "AT", "ADD", "SUB", "MUL", "DIV",
  "ASSIGN", "LBRACE", "RBRACE", "LPAREN", "RPAREN", "LBRACK", "RBRACK",
  "COLON", "SEMI", "COMMA", "$accept", "program", "block",
  "statement_list", "statement", "declaration", "assignment",
  "conditional_statement", "loop_statement", "print_statement",
  "expression_list", "expression", "term", "factor", "vec_literal",
  "int_list", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    26,    27,    28,    28,    29,    29,    30,    30,    30,
      30,    30,    31,    31,    32,    32,    33,    34,    35,    36,
      36,    37,    37,    37,    38,    38,    38,    38,    39,    39,
      39,    39,    39,    40,    40,    41,    41
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     3,     2,     1,     2,     1,     1,     1,
       1,     1,     3,     6,     4,     6,     3,     3,     5,     1,
       3,     1,     3,     3,     1,     3,     3,     3,     1,     1,
       1,     3,     3,     3,     5,     1,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     2,     0,     0,     0,     0,     0,     0,
       4,     0,     5,     7,     8,     9,    10,    11,     1,     0,
       0,    30,    28,     0,     0,     0,    21,    24,    29,     0,
       0,     0,     0,     3,     6,    12,     0,     0,     0,     0,
       0,     0,    16,     0,     0,     0,    17,     0,     0,     0,
       0,    31,    32,    33,     0,    22,    23,    27,    25,    26,
       0,    19,    14,     0,     0,    35,     0,    18,     0,     0,
      13,    34,     0,    20,    15,    36
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     2,     3,    11,    12,    13,    14,    15,    16,    17,
      60,    25,    26,    27,    28,    66
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -19
static const yytype_int8 yypact[] =
{
     -16,    -1,    15,   -19,    20,    45,    10,    10,    21,    16,
     -19,     5,   -19,   -19,   -19,   -19,   -19,   -19,   -19,    14,
      42,    18,   -19,    10,    54,    30,    34,   -19,   -19,    30,
      46,    10,    10,   -19,   -19,   -19,    55,    10,    24,    33,
      10,    10,   -19,    10,    10,    10,   -19,    10,     9,    52,
      53,   -19,   -19,   -19,    60,    34,    34,   -19,   -19,   -19,
      27,    50,   -19,    10,    48,   -19,    35,   -19,    10,    22,
     -19,   -19,    63,    50,   -19,   -19
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -19,   -19,    25,   -19,    64,   -19,   -19,   -19,   -19,   -19,
     -19,    -7,    26,   -18,   -19,   -19
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      29,     1,     4,     5,     6,     7,     8,     9,     4,     5,
       6,     7,     8,     9,    49,    18,    38,    10,    21,    51,
      22,    40,    41,    33,    48,    57,    58,    59,    19,    23,
      30,    24,    31,    62,    40,    41,    40,    41,    35,    32,
      61,    37,    40,    41,    52,    43,    74,     1,    44,    45,
      42,    67,    68,    20,    46,    53,    69,    71,    54,    36,
      72,    73,    40,    41,    39,    50,    55,    56,    63,    47,
      65,    64,    70,    75,     0,    34
};

static const yytype_int8 yycheck[] =
{
       7,    17,     3,     4,     5,     6,     7,     8,     3,     4,
       5,     6,     7,     8,    32,     0,    23,    18,     8,    37,
      10,    12,    13,    18,    31,    43,    44,    45,     8,    19,
       9,    21,    16,    24,    12,    13,    12,    13,    24,    23,
      47,    23,    12,    13,    20,    11,    24,    17,    14,    15,
      25,    24,    25,     8,    29,    22,    63,    22,    25,    17,
      25,    68,    12,    13,    10,    10,    40,    41,    16,    23,
      10,    18,    24,    10,    -1,    11
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    17,    27,    28,     3,     4,     5,     6,     7,     8,
      18,    29,    30,    31,    32,    33,    34,    35,     0,     8,
       8,     8,    10,    19,    21,    37,    38,    39,    40,    37,
       9,    16,    23,    18,    30,    24,    17,    23,    37,    10,
      12,    13,    28,    11,    14,    15,    28,    23,    37,    39,
      10,    39,    20,    22,    25,    38,    38,    39,    39,    39,
      36,    37,    24,    16,    18,    10,    41,    24,    25,    37,
      24,    22,    25,    37,    24,    10
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1455 of yacc.c  */
#line 66 "vlang.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); root_node = (yyvsp[(1) - (1)].node); }
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 70 "vlang.y"
    { (yyval.node) = (yyvsp[(2) - (3)].node); }
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 71 "vlang.y"
    { (yyval.node) = NULL; }
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 75 "vlang.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 76 "vlang.y"
    { (yyval.node) = new_node(SEMI_NODE, (yyvsp[(1) - (2)].node), (yyvsp[(2) - (2)].node)); }
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 80 "vlang.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 81 "vlang.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 82 "vlang.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 83 "vlang.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 84 "vlang.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 88 "vlang.y"
    { add_symbol((yyvsp[(2) - (3)].sval), SCL_TYPE, 0); (yyval.node) = NULL; }
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 89 "vlang.y"
    { add_symbol((yyvsp[(2) - (6)].sval), VEC_TYPE, (yyvsp[(4) - (6)].ival)); (yyval.node) = NULL; }
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 93 "vlang.y"
    { (yyval.node) = new_node(ASSIGN_NODE, new_leaf(ID_NODE, (yyvsp[(1) - (4)].sval)), (yyvsp[(3) - (4)].node)); }
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 94 "vlang.y"
    { (yyval.node) = new_node(ASSIGN_NODE, new_node(COLON_NODE, new_leaf(ID_NODE, (yyvsp[(1) - (6)].sval)), (yyvsp[(3) - (6)].node)), (yyvsp[(5) - (6)].node)); }
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 98 "vlang.y"
    { (yyval.node) = new_node(IF_NODE, (yyvsp[(2) - (3)].node), (yyvsp[(3) - (3)].node)); }
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 102 "vlang.y"
    { (yyval.node) = new_node(LOOP_NODE, (yyvsp[(2) - (3)].node), (yyvsp[(3) - (3)].node)); }
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 106 "vlang.y"
    { 
        (yyval.node) = new_node(PRINT_NODE, new_leaf(STRING_LITERAL_NODE, (yyvsp[(2) - (5)].sval)), (yyvsp[(4) - (5)].node)); 
    }
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 112 "vlang.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 113 "vlang.y"
    { (yyval.node) = new_node(COMMA_NODE, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); }
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 117 "vlang.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 118 "vlang.y"
    { (yyval.node) = new_node(ADD_NODE, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); }
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 119 "vlang.y"
    { (yyval.node) = new_node(SUB_NODE, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); }
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 123 "vlang.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 124 "vlang.y"
    { (yyval.node) = new_node(MUL_NODE, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); }
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 125 "vlang.y"
    { (yyval.node) = new_node(DIV_NODE, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); }
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 126 "vlang.y"
    { (yyval.node) = new_node(AT_NODE, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); }
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 130 "vlang.y"
    { (yyval.node) = new_leaf(INT_LITERAL_NODE, (char *)malloc(sizeof(char)*10)); sprintf((yyval.node)->name, "%d", (yyvsp[(1) - (1)].ival)); }
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 131 "vlang.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 132 "vlang.y"
    { (yyval.node) = new_leaf(ID_NODE, (yyvsp[(1) - (1)].sval)); }
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 133 "vlang.y"
    { (yyval.node) = new_node(COLON_NODE, new_leaf(ID_NODE, (yyvsp[(1) - (3)].sval)), (yyvsp[(3) - (3)].node)); }
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 134 "vlang.y"
    { (yyval.node) = (yyvsp[(2) - (3)].node); }
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 140 "vlang.y"
    { char *s = (char *)malloc(sizeof(char)*10); sprintf(s, "%d", (yyvsp[(2) - (3)].ival)); (yyval.node) = new_node(VEC_LITERAL_NODE, new_leaf(INT_LITERAL_NODE, s), NULL); }
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 141 "vlang.y"
    { char *s = (char *)malloc(sizeof(char)*10); sprintf(s, "%d", (yyvsp[(2) - (5)].ival)); (yyval.node) = new_node(VEC_LITERAL_NODE, new_leaf(INT_LITERAL_NODE, s), (yyvsp[(4) - (5)].node)); }
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 145 "vlang.y"
    { char *s = (char *)malloc(sizeof(char)*10); sprintf(s, "%d", (yyvsp[(1) - (1)].ival)); (yyval.node) = new_leaf(INT_LITERAL_NODE, s); }
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 146 "vlang.y"
    { char *s = (char *)malloc(sizeof(char)*10); sprintf(s, "%d", (yyvsp[(3) - (3)].ival)); (yyval.node) = new_node(COMMA_NODE, (yyvsp[(1) - (3)].node), new_leaf(INT_LITERAL_NODE, s)); }
    break;



/* Line 1455 of yacc.c  */
#line 1718 "y.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 1675 of yacc.c  */
#line 151 "vlang.y"


void yyerror(const char *s) {
    fprintf(stderr, "error: %s\n", s);
}

int main(int argc, char *argv[]) {
    extern FILE *yyin;
    if (argc > 1) {
        FILE *file = fopen(argv[1], "r");
        if (!file) {
            fprintf(stderr, "Cannot open file: %s\n", argv[1]);
            return 1;
        }
        yyin = file;
    }
    
    int result = yyparse();
    if (result == 0) {
        // Generate C code to a temporary file
        FILE *c_file = fopen("temp_output.c", "w");
        if (!c_file) {
            fprintf(stderr, "Cannot create temporary C file\n");
            return 1;
        }
        
        // Write C code to file
        fprintf(c_file, "#include <stdio.h>\n");
        fprintf(c_file, "#include <stdlib.h>\n");
        fprintf(c_file, "#include <string.h>\n\n");
        
        fprintf(c_file, "int main() {\n");
        
        // Generate code from AST with smart declaration handling
        if (root_node) {
            // Set global file pointer for code generation
            output_file = c_file;
            generate_code_with_declarations(root_node);
        }
        
        fprintf(c_file, "    return 0;\n");
        fprintf(c_file, "}\n");
        
        fclose(c_file);
        
        // Compile the C code
        fprintf(stderr, "Compiling generated C code...\n");
        int compile_result = system("gcc temp_output.c -o temp_program.exe");
        if (compile_result != 0) {
            fprintf(stderr, "Compilation failed!\n");
            return 1;
        }
        
        // Run the executable
        fprintf(stderr, "Running compiled program:\n");
        fprintf(stderr, "------------------------\n");
        int run_result = system("temp_program.exe");
        
        // Clean up temporary files
        remove("temp_output.c");
        remove("temp_program.exe");
        
        return run_result;
    }
    return result;
}

// Code generation functions implementation
void generate_code(ast_node *node) {
    if (!node) return;
    
    switch (node->type) {
        case SEMI_NODE:
            generate_code(node->left);
            generate_code(node->right);
            break;
        case ASSIGN_NODE:
            generate_assignment(node);
            break;
        case IF_NODE:
            generate_if(node);
            break;
        case LOOP_NODE:
            generate_loop(node);
            break;
        case PRINT_NODE:
            generate_print(node);
            break;
        default:
            break;
    }
}

void generate_assignment(ast_node *node) {
    if (node->left->type == ID_NODE) {
        // Check if it's a vector assignment
        symbol *sym = get_symbol(node->left->name);
        if (sym && sym->type == VEC_TYPE && node->right->type == VEC_LITERAL_NODE) {
            // Vector literal assignment: v = [1,2,3,4,5]
            generate_vec_assignment_with_declaration(node->left->name, node->right, sym->size);
        } else if (sym && sym->type == VEC_TYPE && node->right->type == INT_LITERAL_NODE) {
            // Scalar to vector assignment: v = 5 (assigns 5 to all elements)
            declare_variable_if_needed(node->left->name);
            fprintf(output_file, "    for(int i = 0; i < %d; i++) %s[i] = ", sym->size, node->left->name);
            generate_expression(node->right);
            fprintf(output_file, ";\n");
        } else if (sym && sym->type == VEC_TYPE && node->right->type == ADD_NODE) {
            // Vector addition assignment: v3 = v1+v2
            if (node->right->left->type == ID_NODE && node->right->right->type == ID_NODE) {
                symbol *left_sym = get_symbol(node->right->left->name);
                symbol *right_sym = get_symbol(node->right->right->name);
                if (left_sym && right_sym && left_sym->type == VEC_TYPE && right_sym->type == VEC_TYPE) {
                    declare_variable_if_needed(node->left->name);
                    fprintf(output_file, "    for(int i = 0; i < %d; i++) %s[i] = %s[i] + %s[i];\n", 
                            sym->size, node->left->name, node->right->left->name, node->right->right->name);
                    return;
                }
            }
            // Fall through to regular vector assignment
            declare_variable_if_needed(node->left->name);
            fprintf(output_file, "    for(int i = 0; i < %d; i++) %s[i] = ", sym->size, node->left->name);
            generate_expression(node->right);
            fprintf(output_file, ";\n");
        } else if (sym && sym->type == VEC_TYPE) {
            // Vector assignment with expression (like v1 = 2*x)
            declare_variable_if_needed(node->left->name);
            fprintf(output_file, "    for(int i = 0; i < %d; i++) %s[i] = ", sym->size, node->left->name);
            generate_expression(node->right);
            fprintf(output_file, ";\n");
        } else {
            // Simple scalar assignment: x = expression
            generate_scalar_assignment_with_declaration(node->left->name, node->right);
        }
    } else if (node->left->type == COLON_NODE) {
        // Vector indexing assignment: v:i = expression
        fprintf(output_file, "    %s[", node->left->left->name);
        generate_expression(node->left->right);
        fprintf(output_file, "] = ");
        generate_expression(node->right);
        fprintf(output_file, ";\n");
    }
}

void generate_expression(ast_node *node) {
    if (!node) return;
    
    switch (node->type) {
        case INT_LITERAL_NODE:
            fprintf(output_file, "%s", node->name);
            break;
        case ID_NODE:
            fprintf(output_file, "%s", node->name);
            break;
        case ADD_NODE:
            // Check if this is vector addition
            if (node->left->type == ID_NODE && node->right->type == ID_NODE) {
                symbol *left_sym = get_symbol(node->left->name);
                symbol *right_sym = get_symbol(node->right->name);
                if (left_sym && right_sym && left_sym->type == VEC_TYPE && right_sym->type == VEC_TYPE) {
                    // This is vector addition - should be handled at assignment level
                    fprintf(output_file, "/* vector addition: %s + %s */", node->left->name, node->right->name);
                    return;
                }
            }
            fprintf(output_file, "(");
            generate_expression(node->left);
            fprintf(output_file, " + ");
            generate_expression(node->right);
            fprintf(output_file, ")");
            break;
        case SUB_NODE:
            fprintf(output_file, "(");
            generate_expression(node->left);
            fprintf(output_file, " - ");
            generate_expression(node->right);
            fprintf(output_file, ")");
            break;
        case MUL_NODE:
            fprintf(output_file, "(");
            generate_expression(node->left);
            fprintf(output_file, " * ");
            generate_expression(node->right);
            fprintf(output_file, ")");
            break;
        case DIV_NODE:
            fprintf(output_file, "(");
            generate_expression(node->left);
            fprintf(output_file, " / ");
            generate_expression(node->right);
            fprintf(output_file, ")");
            break;
        case VEC_LITERAL_NODE:
            generate_vec_literal(node);
            break;
        case COLON_NODE:
            // Vector indexing: v:i
            fprintf(output_file, "%s[", node->left->name);
            generate_expression(node->right);
            fprintf(output_file, "]");
            break;
        case AT_NODE:
            // Dot product - generate inline calculation
            generate_dot_product(node);
            break;
        default:
            break;
    }
}

void generate_vec_literal(ast_node *node) {
    // For vector literals like [1,2,3], we need to assign each element
    // This is a simplified version - in practice you'd need to handle the target variable
    fprintf(output_file, "/* vector literal */");
}

void generate_print(ast_node *node) {
    fprintf(output_file, "    printf(\"%s: ", node->left->name);
    
    // Handle expression list - check for comma-separated expressions
    ast_node *expr = node->right;
    
    if (expr->type == COMMA_NODE) {
        // Multiple expressions to print
        generate_print_expressions(expr);
    } else if (expr->type == ID_NODE) {
        symbol *sym = get_symbol(expr->name);
        if (sym && sym->type == VEC_TYPE) {
            // Print vector
            fprintf(output_file, "[");
            for (int i = 0; i < sym->size; i++) {
                if (i > 0) fprintf(output_file, ", ");
                fprintf(output_file, "%%d");
            }
            fprintf(output_file, "]\\n\"");
            for (int i = 0; i < sym->size; i++) {
                fprintf(output_file, ", %s[%d]", expr->name, i);
            }
            fprintf(output_file, ");\n");
        } else {
            // Print scalar
            fprintf(output_file, "%%d\\n\", ");
            generate_expression(expr);
            fprintf(output_file, ");\n");
        }
    } else {
        // Print expression result
        fprintf(output_file, "%%d\\n\", ");
        generate_expression(expr);
        fprintf(output_file, ");\n");
    }
}

void generate_if(ast_node *node) {
    fprintf(output_file, "    if (");
    generate_expression(node->left);
    fprintf(output_file, ") {\n");
    generate_code_with_declarations(node->right);
    fprintf(output_file, "    }\n");
}

void generate_loop(ast_node *node) {
    int loop_label = label_count++;
    fprintf(output_file, "    for (int loop_var_%d = 0; loop_var_%d < ", loop_label, loop_label);
    generate_expression(node->left);
    fprintf(output_file, "; loop_var_%d++) {\n", loop_label);
    generate_code_with_declarations(node->right);
    fprintf(output_file, "    }\n");
}

void generate_vec_assignment(char *var_name, ast_node *vec_node, int size) {
    // Generate assignment for vector literal like v = [1,2,3,4,5]
    int index = 0;
    ast_node *current = vec_node->left; // First element
    
    // Assign first element
    fprintf(output_file, "    %s[%d] = %s;\n", var_name, index++, current->name);
    
    // Assign remaining elements from the list
    current = vec_node->right; // The int_list part
    while (current && index < size) {
        if (current->type == COMMA_NODE) {
            fprintf(output_file, "    %s[%d] = %s;\n", var_name, index++, current->right->name);
            current = current->left;
        } else {
            fprintf(output_file, "    %s[%d] = %s;\n", var_name, index++, current->name);
            break;
        }
    }
}

void declare_variable_if_needed(char *var_name) {
    symbol *sym = get_symbol(var_name);
    if (!sym) return;
    
    // Find symbol index
    int sym_index = -1;
    for (int i = 0; i < symbol_count; i++) {
        if (strcmp(symbol_table[i].name, var_name) == 0) {
            sym_index = i;
            break;
        }
    }
    
    if (sym_index >= 0 && !declared_vars[sym_index]) {
        if (sym->type == SCL_TYPE) {
            fprintf(output_file, "    int %s;\n", var_name);
        } else if (sym->type == VEC_TYPE) {
            fprintf(output_file, "    int %s[%d];\n", var_name, sym->size);
        }
        declared_vars[sym_index] = 1;
    }
}

void generate_code_with_declarations(ast_node *node) {
    if (!node) return;
    
    switch (node->type) {
        case SEMI_NODE:
            generate_code_with_declarations(node->left);
            generate_code_with_declarations(node->right);
            break;
        case ASSIGN_NODE:
            generate_assignment(node);
            break;
        case IF_NODE:
            generate_if(node);
            break;
        case LOOP_NODE:
            generate_loop(node);
            break;
        case PRINT_NODE:
            generate_print(node);
            break;
        default:
            break;
    }
}

void generate_scalar_assignment_with_declaration(char *var_name, ast_node *expr_node) {
    symbol *sym = get_symbol(var_name);
    if (!sym) return;
    
    // Find symbol index
    int sym_index = -1;
    for (int i = 0; i < symbol_count; i++) {
        if (strcmp(symbol_table[i].name, var_name) == 0) {
            sym_index = i;
            break;
        }
    }
    
    if (sym_index >= 0 && !declared_vars[sym_index]) {
        // Combine declaration and initialization
        fprintf(output_file, "    int %s = ", var_name);
        generate_expression(expr_node);
        fprintf(output_file, ";\n");
        declared_vars[sym_index] = 1;
    } else {
        // Variable already declared, just assign
        fprintf(output_file, "    %s = ", var_name);
        generate_expression(expr_node);
        fprintf(output_file, ";\n");
    }
}

void generate_vec_assignment_with_declaration(char *var_name, ast_node *vec_node, int size) {
    symbol *sym = get_symbol(var_name);
    if (!sym) return;
    
    // Find symbol index
    int sym_index = -1;
    for (int i = 0; i < symbol_count; i++) {
        if (strcmp(symbol_table[i].name, var_name) == 0) {
            sym_index = i;
            break;
        }
    }
    
    if (sym_index >= 0 && !declared_vars[sym_index]) {
        // Generate vector declaration with initialization
        fprintf(output_file, "    int %s[%d] = {", var_name, size);
        
        // Extract values from AST - need to collect all values first to print in correct order
        char *values[size];
        int value_count = 0;
        
        // Get first element
        ast_node *current = vec_node->left;
        values[value_count++] = current->name;
        
        // Get remaining elements from the int_list
        current = vec_node->right;
        collect_int_list_values(current, values, &value_count, size);
        
        // Print all values in correct order
        for (int i = 0; i < value_count && i < size; i++) {
            if (i > 0) fprintf(output_file, ", ");
            fprintf(output_file, "%s", values[i]);
        }
        
        fprintf(output_file, "};\n");
        declared_vars[sym_index] = 1;
    } else {
        // Variable already declared, use individual assignments
        generate_vec_assignment(var_name, vec_node, size);
    }
}

void collect_int_list_values(ast_node *node, char **values, int *count, int max_size) {
    if (!node || *count >= max_size) return;
    
    if (node->type == COMMA_NODE) {
        // Recursively collect from left side first (this maintains order)
        collect_int_list_values(node->left, values, count, max_size);
        // Then add the right side value
        if (node->right && *count < max_size) {
            values[(*count)++] = node->right->name;
        }
    } else {
        // Single value node
        values[(*count)++] = node->name;
    }
}

void generate_dot_product(ast_node *node) {
    // Generate dot product calculation: left @ right
    // This creates a temporary variable and calculates the sum
    int temp_id = temp_var_count++;
    
    // Get vector sizes - assume both vectors have same size for now
    symbol *left_sym = NULL, *right_sym = NULL;
    int vec_size = 0;
    
    if (node->left->type == ID_NODE) {
        left_sym = get_symbol(node->left->name);
        if (left_sym && left_sym->type == VEC_TYPE) {
            vec_size = left_sym->size;
        }
    }
    
    if (node->right->type == ID_NODE) {
        right_sym = get_symbol(node->right->name);
    }
    
    // Generate inline dot product calculation
    fprintf(output_file, "({int dot_sum_%d = 0; for(int dot_i_%d = 0; dot_i_%d < %d; dot_i_%d++) { dot_sum_%d += ", 
            temp_id, temp_id, temp_id, vec_size, temp_id, temp_id);
    
    generate_expression(node->left);
    fprintf(output_file, "[dot_i_%d] * ", temp_id);
    generate_expression(node->right);
    fprintf(output_file, "[dot_i_%d]; } dot_sum_%d; })", temp_id, temp_id);
}

void generate_print_expressions(ast_node *node) {
    // Handle comma-separated expressions in print statements
    // For now, let's simplify and just print the first expression
    if (node->type == COMMA_NODE) {
        // Print first expression
        if (node->left->type == ID_NODE) {
            symbol *sym = get_symbol(node->left->name);
            if (sym && sym->type == VEC_TYPE) {
                // Print vector
                fprintf(output_file, "[");
                for (int i = 0; i < sym->size; i++) {
                    if (i > 0) fprintf(output_file, ", ");
                    fprintf(output_file, "%%d");
                }
                fprintf(output_file, "]\\n\"");
                for (int i = 0; i < sym->size; i++) {
                    fprintf(output_file, ", %s[%d]", node->left->name, i);
                }
                fprintf(output_file, ");\n");
            } else {
                // Print scalar
                fprintf(output_file, "%%d\\n\", ");
                generate_expression(node->left);
                fprintf(output_file, ");\n");
            }
        } else {
            // Print expression result
            fprintf(output_file, "%%d\\n\", ");
            generate_expression(node->left);
            fprintf(output_file, ");\n");
        }
    }
}

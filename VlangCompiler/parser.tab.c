
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
#line 1 "parser.y"

/* -------------------------------------------------------------------------- */
/*  Prologue – headers, helpers & symbol table                                */
/* -------------------------------------------------------------------------- */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

FILE *out;
void yyerror(const char *s);
int  yylex();

/* ---------------- symbol table ---------------- */
char current_vec_name[64] = "";
int  current_vec_size     = 0;
int temp_id_counter = 0;
struct {
    char name[64];
    int  is_vector;
    int  size;
} symbols[100];
int symbol_count = 0;

int  is_vector_var(const char *n){
    for(int i=0;i<symbol_count;++i)
        if(strcmp(symbols[i].name,n)==0) return symbols[i].is_vector;
    return 0;
}
bool is_temp_vector_expr(const char *n){
    return strncmp(n,"temp_vec_expr_",14)==0 ||
           strncmp(n,"temp_index_",11)   ==0;
}

static const char *strip_parens(const char *s) {
    size_t len = strlen(s);
    if (len >= 2 && s[0] == '(' && s[len - 1] == ')') {
        char *tmp = strdup(s + 1);          /* copy without first '(' */
        tmp[len - 2] = '\0';                /* kill last ')'          */
        return tmp;                         /* caller frees if needed */
    }
    return s;
}

int is_vector_expr(const char *s) {
    const char *t = strip_parens(s);     /* NEW */
    int res = is_vector_var(t) || is_temp_vector_expr(t);
    if (t != s) free((char *)t);         /* only free if we duped */
    return res;
}

void register_var(const char *n,int vec,int sz){
    strcpy(symbols[symbol_count].name,n);
    symbols[symbol_count].is_vector = vec;
    symbols[symbol_count].size      = sz;
    ++symbol_count;
    if(vec){ strcpy(current_vec_name,n); current_vec_size=sz; }
}
int  get_vector_size(const char *n){
    for(int i=0;i<symbol_count;++i)
        if(strcmp(symbols[i].name,n)==0) return symbols[i].size;
    return current_vec_size;
}
/*  concat two C snippets  */
static char *cat2(const char *a,const char *b){
    char *r = (char*)malloc(strlen(a)+strlen(b)+1);
    strcpy(r,a); strcat(r,b); return r;
}


/* Line 189 of yacc.c  */
#line 144 "parser.tab.c"

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

/* Line 214 of yacc.c  */
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



/* Line 214 of yacc.c  */
#line 231 "parser.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 243 "parser.tab.c"

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
#define YYFINAL  17
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   164

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  33
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  14
/* YYNRULES -- Number of rules.  */
#define YYNRULES  38
/* YYNRULES -- Number of states.  */
#define YYNSTATES  85

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   287

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
      25,    26,    27,    28,    29,    30,    31,    32
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     5,     9,    12,    14,    16,    18,    20,
      22,    24,    28,    35,    42,    47,    54,    61,    63,    67,
      69,    71,    75,    79,    83,    87,    91,    93,    97,   101,
     105,   109,   113,   117,   121,   125,   129,   131,   135
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      34,     0,    -1,    35,    -1,    11,    36,    12,    -1,    36,
      37,    -1,    37,    -1,    38,    -1,    39,    -1,    43,    -1,
      44,    -1,    46,    -1,     6,     4,    18,    -1,     7,     4,
      11,     3,    12,    18,    -1,     4,    20,    15,    40,    16,
      18,    -1,     4,    20,    41,    18,    -1,     4,    17,     3,
      20,    41,    18,    -1,     4,    17,    41,    20,    41,    18,
      -1,     3,    -1,    40,    19,     3,    -1,     3,    -1,     4,
      -1,    41,    21,    41,    -1,    41,    22,    41,    -1,    41,
      23,    41,    -1,    41,    24,    41,    -1,    13,    41,    14,
      -1,    42,    -1,    41,    17,    41,    -1,    41,    25,    41,
      -1,    15,    40,    16,    -1,    41,    27,    41,    -1,    41,
      28,    41,    -1,     4,    17,     3,    -1,     4,    17,    41,
      -1,     9,    41,    35,    -1,     8,    41,    35,    -1,    41,
      -1,    45,    19,    41,    -1,    10,     5,    17,    45,    18,
      -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   115,   115,   119,   123,   124,   128,   129,   130,   131,
     132,   137,   139,   145,   157,   247,   256,   269,   270,   276,
     282,   287,   322,   364,   398,   437,   445,   447,   478,   497,
     506,   515,   528,   536,   559,   570,   582,   588,   604
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INT", "ID", "STRING", "SCL", "VEC",
  "LOOP", "IF", "PRINT", "LBRACE", "RBRACE", "LPAREN", "RPAREN", "LBRACK",
  "RBRACK", "COLON", "SEMICOLON", "COMMA", "ASSIGN", "PLUS", "MINUS",
  "TIMES", "DIVIDE", "DOTPROD", "UNKNOWN", "EQ", "NE", "LT", "LE", "GT",
  "GE", "$accept", "program", "block", "statement_list", "statement",
  "declaration", "assignment", "int_list", "expression", "indexed_expr",
  "if_statement", "loop_statement", "print_list", "print_statement", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    33,    34,    35,    36,    36,    37,    37,    37,    37,
      37,    38,    38,    39,    39,    39,    39,    40,    40,    41,
      41,    41,    41,    41,    41,    41,    41,    41,    41,    41,
      41,    41,    42,    42,    43,    44,    45,    45,    46
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     3,     2,     1,     1,     1,     1,     1,
       1,     3,     6,     6,     4,     6,     6,     1,     3,     1,
       1,     3,     3,     3,     3,     3,     1,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     1,     3,     5
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     2,     0,     0,     0,     0,     0,     0,
       0,     5,     6,     7,     8,     9,    10,     1,     0,     0,
       0,     0,    19,    20,     0,     0,     0,    26,     0,     0,
       3,     4,    19,     0,     0,     0,    11,     0,     0,     0,
      17,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      35,    34,     0,     0,     0,     0,    14,     0,    19,    33,
      25,    29,     0,    27,    21,    22,    23,    24,    28,    30,
      31,    36,     0,     0,     0,    29,     0,    18,    38,     0,
      15,    16,    13,    12,    37
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     2,     3,    10,    11,    12,    13,    41,    26,    27,
      14,    15,    72,    16
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -17
static const yytype_int16 yypact[] =
{
      11,   154,    28,   -17,   -16,    29,    38,    -1,    -1,    43,
     147,   -17,   -17,   -17,   -17,   -17,   -17,   -17,    49,    62,
      25,    40,   -17,    32,    -1,    56,    -4,   -17,    -4,    46,
     -17,   -17,    47,    64,    56,    76,   -17,    67,    65,    33,
     -17,   -11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     -17,   -17,    -1,    -1,    -1,   -10,   -17,    60,   -17,   109,
     -17,   -17,    70,   109,   118,   118,   122,   122,    -2,   109,
     109,   109,    13,    88,   100,    58,    61,   -17,   -17,    -1,
     -17,   -17,   -17,   -17,   109
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -17,   -17,     1,   -17,    72,   -17,   -17,    68,    -8,   -17,
     -17,   -17,   -17,   -17
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      28,    18,    22,    23,    19,    61,    75,     1,    62,    62,
      33,    35,    24,    42,    25,    42,    39,    43,    44,    45,
      46,    47,     1,    48,    49,    48,    49,    50,    17,    51,
      59,    78,    79,    20,    63,    64,    65,    66,    67,    68,
      69,    70,    21,    36,    71,    73,    74,    60,    29,    38,
      42,    37,    32,    23,    43,    44,    45,    46,    47,    40,
      48,    49,    24,    52,    25,    22,    23,    53,    58,    23,
      57,    84,    76,    77,     0,    24,    82,    34,    24,    83,
      25,    42,    31,     0,    54,    43,    44,    45,    46,    47,
       0,    48,    49,    42,    56,     0,     0,    43,    44,    45,
      46,    47,    55,    48,    49,    42,    80,     0,     0,    43,
      44,    45,    46,    47,     0,    48,    49,    42,    81,     0,
       0,    43,    44,    45,    46,    47,    42,    48,    49,     0,
      43,    44,    45,    46,    47,    42,    48,    49,     0,    42,
       0,    45,    46,    47,     0,    48,    49,    47,     0,    48,
      49,     4,     0,     5,     6,     7,     8,     9,     4,    30,
       5,     6,     7,     8,     9
};

static const yytype_int8 yycheck[] =
{
       8,    17,     3,     4,    20,    16,    16,    11,    19,    19,
      18,    19,    13,    17,    15,    17,    24,    21,    22,    23,
      24,    25,    11,    27,    28,    27,    28,    26,     0,    28,
      38,    18,    19,     4,    42,    43,    44,    45,    46,    47,
      48,    49,     4,    18,    52,    53,    54,    14,     5,    17,
      17,    11,     3,     4,    21,    22,    23,    24,    25,     3,
      27,    28,    13,    17,    15,     3,     4,    20,     3,     4,
       3,    79,    12,     3,    -1,    13,    18,    15,    13,    18,
      15,    17,    10,    -1,    20,    21,    22,    23,    24,    25,
      -1,    27,    28,    17,    18,    -1,    -1,    21,    22,    23,
      24,    25,    34,    27,    28,    17,    18,    -1,    -1,    21,
      22,    23,    24,    25,    -1,    27,    28,    17,    18,    -1,
      -1,    21,    22,    23,    24,    25,    17,    27,    28,    -1,
      21,    22,    23,    24,    25,    17,    27,    28,    -1,    17,
      -1,    23,    24,    25,    -1,    27,    28,    25,    -1,    27,
      28,     4,    -1,     6,     7,     8,     9,    10,     4,    12,
       6,     7,     8,     9,    10
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    11,    34,    35,     4,     6,     7,     8,     9,    10,
      36,    37,    38,    39,    43,    44,    46,     0,    17,    20,
       4,     4,     3,     4,    13,    15,    41,    42,    41,     5,
      12,    37,     3,    41,    15,    41,    18,    11,    17,    41,
       3,    40,    17,    21,    22,    23,    24,    25,    27,    28,
      35,    35,    17,    20,    20,    40,    18,     3,     3,    41,
      14,    16,    19,    41,    41,    41,    41,    41,    41,    41,
      41,    41,    45,    41,    41,    16,    12,     3,    18,    19,
      18,    18,    18,    18,    41
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
#line 115 "parser.y"
    { fprintf(out,"%s",(yyvsp[(1) - (1)].blockcode)); free((yyvsp[(1) - (1)].blockcode)); ;}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 119 "parser.y"
    { (yyval.blockcode) = (yyvsp[(2) - (3)].blockcode); ;}
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 123 "parser.y"
    { (yyval.blockcode) = cat2((yyvsp[(1) - (2)].blockcode),(yyvsp[(2) - (2)].blockcode)); free((yyvsp[(1) - (2)].blockcode)); free((yyvsp[(2) - (2)].blockcode)); ;}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 124 "parser.y"
    { (yyval.blockcode) = (yyvsp[(1) - (1)].blockcode); ;}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 128 "parser.y"
    { (yyval.blockcode) = strdup(""); ;}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 129 "parser.y"
    { (yyval.blockcode) = (yyvsp[(1) - (1)].blockcode); ;}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 130 "parser.y"
    { (yyval.blockcode) = (yyvsp[(1) - (1)].blockcode); ;}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 131 "parser.y"
    { (yyval.blockcode) = (yyvsp[(1) - (1)].blockcode); ;}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 132 "parser.y"
    { (yyval.blockcode) = (yyvsp[(1) - (1)].blockcode); ;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 138 "parser.y"
    { fprintf(out,"int %s = 0;\n",(yyvsp[(2) - (3)].sval)); register_var((yyvsp[(2) - (3)].sval),0,1); ;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 140 "parser.y"
    { fprintf(out,"int %s[%d] = {0};\n",(yyvsp[(2) - (6)].sval),(yyvsp[(4) - (6)].ival)); register_var((yyvsp[(2) - (6)].sval),1,(yyvsp[(4) - (6)].ival)); ;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 146 "parser.y"
    {
            static int t=0; char tmp[64]; sprintf(tmp,"temp_vec_%d",t++);
            char buf[256+strlen((yyvsp[(4) - (6)].sval))];
            sprintf(buf,
                "int %s[] = {%s};\n"
                "memcpy(%s,%s,sizeof(int)*%d);\n",
                tmp,(yyvsp[(4) - (6)].sval),(yyvsp[(1) - (6)].sval),tmp,current_vec_size);
            (yyval.blockcode) = strdup(buf); free((yyvsp[(4) - (6)].sval));
        ;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 158 "parser.y"
    {
            /*  run any setup statements produced while parsing the RHS  */
            char *buf = cat2((yyvsp[(3) - (4)].expr).setup, "");

            /* 1. RHS is a **temporary** vector we built earlier */
            if (is_temp_vector_expr((yyvsp[(3) - (4)].expr).code)) {
                char rhs[128];
                sprintf(rhs,
                        "memcpy(%s, %s, sizeof(int)*%d);\n",
                        (yyvsp[(1) - (4)].sval), (yyvsp[(3) - (4)].expr).code, current_vec_size);
                buf = cat2(buf, rhs);
            }

            /* 2. destination is **scalar** → simple scalar assignment   */
            else if (!is_vector_var((yyvsp[(1) - (4)].sval))) {
                char rhs[128];
                sprintf(rhs, "%s = %s;\n", (yyvsp[(1) - (4)].sval), (yyvsp[(3) - (4)].expr).code);
                buf = cat2(buf, rhs);
            }

            /* 3. pattern  v = v2 : v1   (vector‑by‑vector indexing)     */
            else if ((yyvsp[(3) - (4)].expr).left && (yyvsp[(3) - (4)].expr).right &&
                     is_vector_expr((yyvsp[(3) - (4)].expr).left) &&
                     is_vector_expr((yyvsp[(3) - (4)].expr).right) &&
                     (yyvsp[(3) - (4)].expr).op == 0)
            {
                char rhs[160];
                sprintf(rhs,
                        "vector_index_by_vector(%s, %s, %s, %d);\n",
                        (yyvsp[(1) - (4)].sval), (yyvsp[(3) - (4)].expr).left, (yyvsp[(3) - (4)].expr).right, current_vec_size);
                buf = cat2(buf, rhs);
            }

            /* 4. **new branch**  simple vector‑to‑vector copy: y = x;   */
            else if (is_vector_expr((yyvsp[(3) - (4)].expr).code) &&     /* RHS is a vector  */
                     (yyvsp[(3) - (4)].expr).right == NULL &&            /* not an op result */
                     (yyvsp[(3) - (4)].expr).op == 0)
            {
                char rhs[128];
                sprintf(rhs,
                        "memcpy(%s, %s, sizeof(int)*%d);\n",
                        (yyvsp[(1) - (4)].sval), (yyvsp[(3) - (4)].expr).code, current_vec_size);
                buf = cat2(buf, rhs);
            }

            /* 5. broadcast of scalar / literal into vector             */
            else if ((yyvsp[(3) - (4)].expr).op == 0) {
                char rhs[160];
                sprintf(rhs,
                        "for(int i=0; i<%d; ++i) %s[i] = %s;\n",
                        current_vec_size, (yyvsp[(1) - (4)].sval), (yyvsp[(3) - (4)].expr).code);
                buf = cat2(buf, rhs);
            }

            /* 6. vector‑scalar & vector‑vector arithmetic               */
            else {
                int l = is_vector_expr((yyvsp[(3) - (4)].expr).left);
                int r = is_vector_expr((yyvsp[(3) - (4)].expr).right);
                char rhs[192];

                if (!l && !r)                                   /* s op s */
                    sprintf(rhs,
                        "for(int i=0; i<%d; ++i) %s[i] = %s;\n",
                        current_vec_size, (yyvsp[(1) - (4)].sval), (yyvsp[(3) - (4)].expr).code);
                else if (l && !r)                               /* v op s */
                    sprintf(rhs,
                        "vector_scalar_op(%s, %s, %s, %d, '%c');\n",
                        (yyvsp[(1) - (4)].sval), (yyvsp[(3) - (4)].expr).left,  (yyvsp[(3) - (4)].expr).right,
                        current_vec_size, (yyvsp[(3) - (4)].expr).op);
                else if (!l && r)                               /* s op v */
                    sprintf(rhs,
                        "vector_scalar_op(%s, %s, %s, %d, '%c');\n",
                        (yyvsp[(1) - (4)].sval), (yyvsp[(3) - (4)].expr).right, (yyvsp[(3) - (4)].expr).left,
                        current_vec_size, (yyvsp[(3) - (4)].expr).op);
                else                                            /* v op v */
                    sprintf(rhs,
                        "vector_vector_op(%s, %s, %s, %d, '%c');\n",
                        (yyvsp[(1) - (4)].sval), (yyvsp[(3) - (4)].expr).left, (yyvsp[(3) - (4)].expr).right,
                        current_vec_size, (yyvsp[(3) - (4)].expr).op);

                buf = cat2(buf, rhs);
            }

            (yyval.blockcode) = buf;
            free((yyvsp[(3) - (4)].expr).code);
            free((yyvsp[(3) - (4)].expr).setup);
        ;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 248 "parser.y"
    {
            char *buf = cat2((yyvsp[(5) - (6)].expr).setup,"");
            char rhs[160];
            sprintf(rhs,"%s[%d] = %s;\n",(yyvsp[(1) - (6)].sval),(yyvsp[(3) - (6)].ival),(yyvsp[(5) - (6)].expr).code);
            buf = cat2(buf,rhs); (yyval.blockcode) = buf;
            free((yyvsp[(5) - (6)].expr).code); free((yyvsp[(5) - (6)].expr).setup);
        ;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 257 "parser.y"
    {
            char *buf = cat2((yyvsp[(3) - (6)].expr).setup,(yyvsp[(5) - (6)].expr).setup);
            char rhs[192];
            sprintf(rhs,"%s[(int)(%s)] = %s;\n",(yyvsp[(1) - (6)].sval),(yyvsp[(3) - (6)].expr).code,(yyvsp[(5) - (6)].expr).code);
            buf = cat2(buf,rhs); (yyval.blockcode) = buf;
            free((yyvsp[(3) - (6)].expr).code); free((yyvsp[(3) - (6)].expr).setup);
            free((yyvsp[(5) - (6)].expr).code); free((yyvsp[(5) - (6)].expr).setup);
        ;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 269 "parser.y"
    { char tmp[32]; sprintf(tmp,"%d",(yyvsp[(1) - (1)].ival)); (yyval.sval)=strdup(tmp); ;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 271 "parser.y"
    { char *b=(char*)malloc(strlen((yyvsp[(1) - (3)].sval))+32); sprintf(b,"%s,%d",(yyvsp[(1) - (3)].sval),(yyvsp[(3) - (3)].ival)); free((yyvsp[(1) - (3)].sval)); (yyval.sval)=b; ;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 277 "parser.y"
    {
            char tmp[32]; sprintf(tmp,"%d",(yyvsp[(1) - (1)].ival));
            (yyval.expr).setup=strdup(""); (yyval.expr).code=strdup(tmp);
            (yyval.expr).left=(yyval.expr).code; (yyval.expr).right=NULL; (yyval.expr).op=0;
        ;}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 283 "parser.y"
    { (yyval.expr).setup=strdup(""); (yyval.expr).code=strdup((yyvsp[(1) - (1)].sval));
          (yyval.expr).left=(yyval.expr).code; (yyval.expr).right=NULL; (yyval.expr).op=0; ;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 288 "parser.y"
    {
            (yyval.expr).setup = cat2((yyvsp[(1) - (3)].expr).setup, (yyvsp[(3) - (3)].expr).setup);
            int l = is_vector_expr((yyvsp[(1) - (3)].expr).code);
            int r = is_vector_expr((yyvsp[(3) - (3)].expr).code);

            if (l && r) {                                   /* v + v */
                char tmp[64]; sprintf(tmp,"temp_vec_expr_%d", temp_id_counter++);
                char buf[256];
                sprintf(buf,
                    "int %s[%d];\n"
                    "vector_vector_op(%s, %s, %s, %d, '+');\n",
                    tmp, current_vec_size, tmp, (yyvsp[(1) - (3)].expr).code, (yyvsp[(3) - (3)].expr).code, current_vec_size);
                (yyval.expr).setup = cat2((yyval.expr).setup, buf);
                (yyval.expr).code  = strdup(tmp);
            } else if (l || r) {                            /* v + s | s + v */
                char tmp[64]; sprintf(tmp,"temp_vec_expr_%d", temp_id_counter++);
                char buf[256];
                const char *vec = l ? (yyvsp[(1) - (3)].expr).code : (yyvsp[(3) - (3)].expr).code;
                const char *scl = l ? (yyvsp[(3) - (3)].expr).code : (yyvsp[(1) - (3)].expr).code;
                sprintf(buf,
                    "int %s[%d];\n"
                    "vector_scalar_op(%s, %s, %s, %d, '+');\n",
                    tmp, current_vec_size, tmp, vec, scl, current_vec_size);
                (yyval.expr).setup = cat2((yyval.expr).setup, buf);
                (yyval.expr).code  = strdup(tmp);
            } else {                                        /* s + s */
                char *code = (char*)malloc(strlen((yyvsp[(1) - (3)].expr).code)+strlen((yyvsp[(3) - (3)].expr).code)+4);
                sprintf(code,"%s + %s",(yyvsp[(1) - (3)].expr).code,(yyvsp[(3) - (3)].expr).code);
                (yyval.expr).code = code;
            }
            (yyval.expr).left = (yyvsp[(1) - (3)].expr).code; (yyval.expr).right = (yyvsp[(3) - (3)].expr).code; (yyval.expr).op = '+';
        ;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 323 "parser.y"
    {
            (yyval.expr).setup = cat2((yyvsp[(1) - (3)].expr).setup, (yyvsp[(3) - (3)].expr).setup);
            int l = is_vector_expr((yyvsp[(1) - (3)].expr).code);
            int r = is_vector_expr((yyvsp[(3) - (3)].expr).code);

            if (l && r) {                                   /* v - v */
                char tmp[64]; sprintf(tmp,"temp_vec_expr_%d", temp_id_counter++);
                char buf[256];
                sprintf(buf,
                    "int %s[%d];\n"
                    "vector_vector_op(%s, %s, %s, %d, '-');\n",
                    tmp, current_vec_size, tmp, (yyvsp[(1) - (3)].expr).code, (yyvsp[(3) - (3)].expr).code, current_vec_size);
                (yyval.expr).setup = cat2((yyval.expr).setup, buf);
                (yyval.expr).code  = strdup(tmp);
            } else if (l || r) {                            /* v - s | s - v */
                char tmp[64]; sprintf(tmp,"temp_vec_expr_%d", temp_id_counter++);
                char buf[256];
                const char *vec = l ? (yyvsp[(1) - (3)].expr).code : (yyvsp[(3) - (3)].expr).code;
                const char *scl = l ? (yyvsp[(3) - (3)].expr).code : (yyvsp[(1) - (3)].expr).code;
                /* order matters for scalar‑vector vs vector‑scalar */
                if (l) /* v - s */
                    sprintf(buf,
                        "int %s[%d];\n"
                        "vector_scalar_op(%s, %s, %s, %d, '-');\n",
                        tmp, current_vec_size, tmp, vec, scl, current_vec_size);
                else   /* s - v */
                    sprintf(buf,
                        "int %s[%d];\n"
                        "vector_scalar_op(%s, %s, %s, %d, '-');\n",
                        tmp, current_vec_size, tmp, scl, vec, current_vec_size);
                (yyval.expr).setup = cat2((yyval.expr).setup, buf);
                (yyval.expr).code  = strdup(tmp);
            } else {                                        /* s - s */
                char *code = (char*)malloc(strlen((yyvsp[(1) - (3)].expr).code)+strlen((yyvsp[(3) - (3)].expr).code)+4);
                sprintf(code,"%s - %s",(yyvsp[(1) - (3)].expr).code,(yyvsp[(3) - (3)].expr).code);
                (yyval.expr).code = code;
            }
            (yyval.expr).left = (yyvsp[(1) - (3)].expr).code; (yyval.expr).right = (yyvsp[(3) - (3)].expr).code; (yyval.expr).op = '-';
        ;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 365 "parser.y"
    {
            (yyval.expr).setup = cat2((yyvsp[(1) - (3)].expr).setup, (yyvsp[(3) - (3)].expr).setup);
            int l = is_vector_expr((yyvsp[(1) - (3)].expr).code);
            int r = is_vector_expr((yyvsp[(3) - (3)].expr).code);

            if (l && r) {                                   /* v * v */
                char tmp[64]; sprintf(tmp,"temp_vec_expr_%d", temp_id_counter++);
                char buf[256];
                sprintf(buf,
                    "int %s[%d];\n"
                    "vector_vector_op(%s, %s, %s, %d, '*');\n",
                    tmp, current_vec_size, tmp, (yyvsp[(1) - (3)].expr).code, (yyvsp[(3) - (3)].expr).code, current_vec_size);
                (yyval.expr).setup = cat2((yyval.expr).setup, buf);
                (yyval.expr).code  = strdup(tmp);
            } else if (l || r) {                            /* v * s | s * v */
                char tmp[64]; sprintf(tmp,"temp_vec_expr_%d", temp_id_counter++);
                char buf[256];
                const char *vec = l ? (yyvsp[(1) - (3)].expr).code : (yyvsp[(3) - (3)].expr).code;
                const char *scl = l ? (yyvsp[(3) - (3)].expr).code : (yyvsp[(1) - (3)].expr).code;
                sprintf(buf,
                    "int %s[%d];\n"
                    "vector_scalar_op(%s, %s, %s, %d, '*');\n",
                    tmp, current_vec_size, tmp, vec, scl, current_vec_size);
                (yyval.expr).setup = cat2((yyval.expr).setup, buf);
                (yyval.expr).code  = strdup(tmp);
            } else {                                        /* s * s */
                char *code = (char*)malloc(strlen((yyvsp[(1) - (3)].expr).code)+strlen((yyvsp[(3) - (3)].expr).code)+4);
                sprintf(code,"%s * %s",(yyvsp[(1) - (3)].expr).code,(yyvsp[(3) - (3)].expr).code);
                (yyval.expr).code = code;
            }
            (yyval.expr).left = (yyvsp[(1) - (3)].expr).code; (yyval.expr).right = (yyvsp[(3) - (3)].expr).code; (yyval.expr).op = '*';
        ;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 399 "parser.y"
    {
    (yyval.expr).setup = cat2((yyvsp[(1) - (3)].expr).setup, (yyvsp[(3) - (3)].expr).setup);
    int l = is_vector_expr((yyvsp[(1) - (3)].expr).code);
    int r = is_vector_expr((yyvsp[(3) - (3)].expr).code);

    if (l && r) {
        char tmp[64]; sprintf(tmp,"temp_vec_expr_%d", temp_id_counter++);
        char buf[256];
        sprintf(buf,
            "int %s[%d];\n"
            "vector_vector_op(%s, %s, %s, %d, '/');\n",
            tmp, current_vec_size, tmp, (yyvsp[(1) - (3)].expr).code, (yyvsp[(3) - (3)].expr).code, current_vec_size);
        (yyval.expr).setup = cat2((yyval.expr).setup, buf);
        (yyval.expr).code = strdup(tmp);
    } else if (l || r) {
        char tmp[64]; sprintf(tmp,"temp_vec_expr_%d", temp_id_counter++);
        char buf[256];
        const char *vec = l ? (yyvsp[(1) - (3)].expr).code : (yyvsp[(3) - (3)].expr).code;
        const char *scl = l ? (yyvsp[(3) - (3)].expr).code : (yyvsp[(1) - (3)].expr).code;
        sprintf(buf,
            "int %s[%d];\n"
            "vector_scalar_op(%s, %s, %s, %d, '/');\n",
            tmp, current_vec_size, tmp, vec, scl, current_vec_size);
        (yyval.expr).setup = cat2((yyval.expr).setup, buf);
        (yyval.expr).code = strdup(tmp);
    } else {
        char *code = (char*)malloc(strlen((yyvsp[(1) - (3)].expr).code)+strlen((yyvsp[(3) - (3)].expr).code)+4);
        sprintf(code,"%s / %s",(yyvsp[(1) - (3)].expr).code,(yyvsp[(3) - (3)].expr).code);
        (yyval.expr).code = code;
    }

    (yyval.expr).left = (yyvsp[(1) - (3)].expr).code;
    (yyval.expr).right = (yyvsp[(3) - (3)].expr).code;
    (yyval.expr).op = '/';
;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 438 "parser.y"
    {
            char *code = (char*)malloc(strlen((yyvsp[(2) - (3)].expr).code)+3);
            sprintf(code,"(%s)",(yyvsp[(2) - (3)].expr).code);
            (yyval.expr).setup=(yyvsp[(2) - (3)].expr).setup; (yyval.expr).code=code;
            (yyval.expr).left=(yyvsp[(2) - (3)].expr).left; (yyval.expr).right=(yyvsp[(2) - (3)].expr).right; (yyval.expr).op=(yyvsp[(2) - (3)].expr).op;
        ;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 445 "parser.y"
    { (yyval.expr)=(yyvsp[(1) - (1)].expr); ;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 448 "parser.y"
    {
    char *setup = cat2((yyvsp[(1) - (3)].expr).setup, (yyvsp[(3) - (3)].expr).setup);

    if (!is_vector_expr((yyvsp[(3) - (3)].expr).code)) {
        // scalar index
        char buf[512];
        sprintf(buf, "%s[(int)(%s)]", (yyvsp[(1) - (3)].expr).code, (yyvsp[(3) - (3)].expr).code);
        (yyval.expr).setup = setup;
        (yyval.expr).code = strdup(buf);
        (yyval.expr).left = strdup((yyvsp[(1) - (3)].expr).code);
        (yyval.expr).right = strdup((yyvsp[(3) - (3)].expr).code);
        (yyval.expr).op = 0;
    } else {
        // vector index
       char tmp[64]; sprintf(tmp,"temp_index_%d",temp_id_counter++);
        char prep[256];
        sprintf(prep,
            "int %s[%d];\n"
            "vector_index_by_vector(%s,%s,%s,%d);\n",
            tmp, current_vec_size, tmp, (yyvsp[(1) - (3)].expr).code, (yyvsp[(3) - (3)].expr).code, current_vec_size);
        setup = cat2(setup, prep);
        (yyval.expr).setup = setup;
        (yyval.expr).code = strdup(tmp);
        (yyval.expr).left = strdup((yyvsp[(1) - (3)].expr).code);
        (yyval.expr).right = strdup((yyvsp[(3) - (3)].expr).code);
        (yyval.expr).op = 0;
    }
;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 479 "parser.y"
    {
    if (!is_vector_expr((yyvsp[(1) - (3)].expr).code) || !is_vector_expr((yyvsp[(3) - (3)].expr).code)) {
        yyerror("dot product '@' requires both operands to be vectors");
        YYABORT;
    }

    char *setup = cat2((yyvsp[(1) - (3)].expr).setup,(yyvsp[(3) - (3)].expr).setup);
    int sz = current_vec_size;
    if ((yyvsp[(1) - (3)].expr).left) sz = get_vector_size((yyvsp[(1) - (3)].expr).left);

    char *code = (char*)malloc(strlen((yyvsp[(1) - (3)].expr).code)+strlen((yyvsp[(3) - (3)].expr).code)+32);
    sprintf(code,"dot_product(%s,%s,%d)",(yyvsp[(1) - (3)].expr).code,(yyvsp[(3) - (3)].expr).code,sz);

    (yyval.expr).setup = setup; (yyval.expr).code = code;
    (yyval.expr).left = (yyvsp[(1) - (3)].expr).code; (yyval.expr).right = (yyvsp[(3) - (3)].expr).code; (yyval.expr).op = '@';
;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 498 "parser.y"
    {
        char tmp[64]; sprintf(tmp,"temp_vec_expr_%d",temp_id_counter++);

            char prep[256+strlen((yyvsp[(2) - (3)].sval))];
            sprintf(prep,"int %s[] = {%s};\n",tmp,(yyvsp[(2) - (3)].sval));
            (yyval.expr).setup=strdup(prep); (yyval.expr).code=strdup(tmp);
            (yyval.expr).left=(yyval.expr).code; (yyval.expr).right=NULL; (yyval.expr).op=0; free((yyvsp[(2) - (3)].sval));
        ;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 507 "parser.y"
    {
        (yyval.expr).setup = cat2((yyvsp[(1) - (3)].expr).setup, (yyvsp[(3) - (3)].expr).setup);
        char *code = (char*)malloc(strlen((yyvsp[(1) - (3)].expr).code)+strlen((yyvsp[(3) - (3)].expr).code)+6);
        sprintf(code, "%s == %s", (yyvsp[(1) - (3)].expr).code, (yyvsp[(3) - (3)].expr).code);
        (yyval.expr).code = code;
        (yyval.expr).left = (yyvsp[(1) - (3)].expr).code; (yyval.expr).right = (yyvsp[(3) - (3)].expr).code; (yyval.expr).op = 0;
    ;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 516 "parser.y"
    {
        (yyval.expr).setup = cat2((yyvsp[(1) - (3)].expr).setup, (yyvsp[(3) - (3)].expr).setup);
        char *code = (char*)malloc(strlen((yyvsp[(1) - (3)].expr).code)+strlen((yyvsp[(3) - (3)].expr).code)+6);
        sprintf(code, "%s != %s", (yyvsp[(1) - (3)].expr).code, (yyvsp[(3) - (3)].expr).code);
        (yyval.expr).code = code;
        (yyval.expr).left = (yyvsp[(1) - (3)].expr).code; (yyval.expr).right = (yyvsp[(3) - (3)].expr).code; (yyval.expr).op = 0;
    ;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 529 "parser.y"
    {
            char buf[256]; sprintf(buf,"%s[%d]",(yyvsp[(1) - (3)].sval),(yyvsp[(3) - (3)].ival));
            (yyval.expr).setup=strdup(""); (yyval.expr).code=strdup(buf);
            (yyval.expr).left=strdup((yyvsp[(1) - (3)].sval));
            char idx[32]; sprintf(idx,"%d",(yyvsp[(3) - (3)].ival));
            (yyval.expr).right=strdup(idx); (yyval.expr).op=0;
        ;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 537 "parser.y"
    {
            char *setup = (yyvsp[(3) - (3)].expr).setup;
            if(is_vector_expr((yyvsp[(3) - (3)].expr).code)){
                static int t=0; char tmp[64]; sprintf(tmp,"temp_index_%d",t++);
                char prep[256];
                sprintf(prep,
                    "int %s[%d];\n"
                    "vector_index_by_vector(%s,%s,%s,%d);\n",
                    tmp,current_vec_size,tmp,(yyvsp[(1) - (3)].sval),(yyvsp[(3) - (3)].expr).code,current_vec_size);
                setup = cat2(setup,prep);
                (yyval.expr).code=strdup(tmp);
            }else{
                char buf[512]; sprintf(buf,"%s[(int)(%s)]",(yyvsp[(1) - (3)].sval),(yyvsp[(3) - (3)].expr).code);
                (yyval.expr).code=strdup(buf);
            }
            (yyval.expr).setup=setup; (yyval.expr).left=strdup((yyvsp[(1) - (3)].sval)); (yyval.expr).right=strdup((yyvsp[(3) - (3)].expr).code); (yyval.expr).op=0;
            free((yyvsp[(3) - (3)].expr).code);
        ;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 560 "parser.y"
    {
            char *buf = cat2((yyvsp[(2) - (3)].expr).setup,"");
            char head[64+strlen((yyvsp[(2) - (3)].expr).code)];
            sprintf(head,"if(%s){\n",(yyvsp[(2) - (3)].expr).code);
            buf = cat2(buf,head); buf = cat2(buf,(yyvsp[(3) - (3)].blockcode)); buf = cat2(buf,"}\n");
            (yyval.blockcode) = buf; free((yyvsp[(2) - (3)].expr).code); free((yyvsp[(2) - (3)].expr).setup); free((yyvsp[(3) - (3)].blockcode));
        ;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 571 "parser.y"
    {
            char *buf = cat2((yyvsp[(2) - (3)].expr).setup,"");
            char head[80+strlen((yyvsp[(2) - (3)].expr).code)];
            sprintf(head,"for(int __i=0;__i<%s;++__i){\n",(yyvsp[(2) - (3)].expr).code);
            buf = cat2(buf,head); buf = cat2(buf,(yyvsp[(3) - (3)].blockcode)); buf = cat2(buf,"}\n");
            (yyval.blockcode) = buf; free((yyvsp[(2) - (3)].expr).code); free((yyvsp[(2) - (3)].expr).setup); free((yyvsp[(3) - (3)].blockcode));
        ;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 583 "parser.y"
    {                       /* first item                          */
            (yyval.plist).setup = (yyvsp[(1) - (1)].expr).setup;
            (yyval.plist).code  = strdup((yyvsp[(1) - (1)].expr).code);     /* no separator yet         */
            (yyval.plist).count = 1;
        ;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 589 "parser.y"
    {                       /* append item, join with ‘|’          */
            (yyval.plist).setup = cat2((yyvsp[(1) - (3)].plist).setup, (yyvsp[(3) - (3)].expr).setup);

            size_t len = strlen((yyvsp[(1) - (3)].plist).code) + strlen((yyvsp[(3) - (3)].expr).code) + 2; /* '|' + NUL */
            char *code = (char*)malloc(len);
            sprintf(code, "%s|%s", (yyvsp[(1) - (3)].plist).code, (yyvsp[(3) - (3)].expr).code);

            free((yyvsp[(1) - (3)].plist).code);
            (yyval.plist).code  = code;
            (yyval.plist).count = (yyvsp[(1) - (3)].plist).count + 1;
        ;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 605 "parser.y"
    {
        /* 1. emit all setup code from sub‑expressions */
        char *buf  = cat2((yyvsp[(4) - (5)].plist).setup, "");
        char *line = (char*)malloc(1024);

        /* 2. heading — prints the label and a colon (no newline) */
        sprintf(line, "std::cout << \"%s: \";\n", (yyvsp[(2) - (5)].sval));
        buf = cat2(buf, line);

        /* 3. iterate over the saved expressions, split on ‘|’          */
        /*    we know how many there are from $4.count                   */
        char *list_copy = strdup((yyvsp[(4) - (5)].plist).code);          /* strtok mutates    */
        char *token     = strtok(list_copy, "|");
        int   idx       = 0;                        /* 1‑based position  */

        while (token) {
            ++idx;
            /* trim leading blanks the user may have typed after ','     */
            while (*token == ' ') ++token;

            bool last = (idx == (yyvsp[(4) - (5)].plist).count);          /* last expression?  */

            if (is_vector_expr(token)) {
                /* vector: we want newline at the end no matter what     */
                sprintf(line,
                        "print_vector(\"\", %s, %d);\n",
                        token, current_vec_size);
            } else {
                /* scalar: newline only if this is the last item         */
                if (last)
                    sprintf(line, "std::cout << %s << std::endl;\n", token);
                else
                    sprintf(line, "std::cout << %s << \" \";\n",  token);
            }
            buf = cat2(buf, line);
            token = strtok(NULL, "|");
        }

        (yyval.blockcode) = buf;

        free(list_copy);
        free((yyvsp[(4) - (5)].plist).code);
        free((yyvsp[(4) - (5)].plist).setup);
    ;}
    break;



/* Line 1455 of yacc.c  */
#line 2178 "parser.tab.c"
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
#line 652 "parser.y"
 /* ============================  driver  ============================ */

void yyerror(const char *s){ fprintf(stderr,"Parse error: %s\n",s); }

int main(){
    out=fopen("output.cpp","w");
    if(!out){ perror("output.cpp"); return 1; }
    fprintf(out,
        "#include <iostream>\n"
        "#include <cstring>\n"
        "#include \"runtime.hpp\"\n"
        "int main(){\n");
    yyparse();
    fprintf(out,"return 0;\n}\n");
    fclose(out);
    return 0;
}


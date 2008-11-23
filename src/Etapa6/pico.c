/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     IDF = 258,
     VAZIO = 259,
     OPEN_PAR = 260,
     CLOSE_PAR = 261,
     MUL = 262,
     ADD = 263,
     SUB = 264,
     DIV = 265,
     FMUL = 266,
     FADD = 267,
     FSUB = 268,
     FDIV = 269,
     F_LIT = 270,
     INT_LIT = 271,
     DIG = 272,
     OPCMP = 273,
     INT = 274,
     DOUBLE = 275,
     FLOAT = 276,
     CHAR = 277,
     QUOTE = 278,
     DQUOTE = 279,
     LE = 280,
     GE = 281,
     EQ = 282,
     NE = 283,
     AND = 284,
     OR = 285,
     NOT = 286,
     IF = 287,
     THEN = 288,
     ELSE = 289,
     WHILE = 290,
     BRANCO = 291,
     END = 292,
     TRUE = 293,
     FALSE = 294,
     PRINT = 295,
     FPRINT = 296,
     RDEF = 297,
     LDEF = 298,
     GOTO = 299,
     LABEL = 300
   };
#endif
/* Tokens.  */
#define IDF 258
#define VAZIO 259
#define OPEN_PAR 260
#define CLOSE_PAR 261
#define MUL 262
#define ADD 263
#define SUB 264
#define DIV 265
#define FMUL 266
#define FADD 267
#define FSUB 268
#define FDIV 269
#define F_LIT 270
#define INT_LIT 271
#define DIG 272
#define OPCMP 273
#define INT 274
#define DOUBLE 275
#define FLOAT 276
#define CHAR 277
#define QUOTE 278
#define DQUOTE 279
#define LE 280
#define GE 281
#define EQ 282
#define NE 283
#define AND 284
#define OR 285
#define NOT 286
#define IF 287
#define THEN 288
#define ELSE 289
#define WHILE 290
#define BRANCO 291
#define END 292
#define TRUE 293
#define FALSE 294
#define PRINT 295
#define FPRINT 296
#define RDEF 297
#define LDEF 298
#define GOTO 299
#define LABEL 300




/* Copy the first part of user declarations.  */
#line 1 "pico.y"

    /* Aqui, pode-se inserir qualquer codigo C necessario ah compilacao
     * final do parser. Sera copiado tal como esta no inicio do y.tab.c
     * gerado por Yacc.
     */
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>

	/* este include eh importante... */
	#include "tokens.h"
	#include "symbol_table.h"
	#include "tac_list.h"
	#include "array_data.h"
	
	/* Definicao de constantes de erros */
	#define UNDEFINED_SYMBOL_ERROR -21
	#define TYPE_MISMATCH_ERROR -20

	/* Definicao de macro com erro de type mismatch */
	#define DISPARA_TYPE_MISMATCH() printf("ERRO DE COMPATIBILIDADE DE TIPO. Quem te ensinou a programar?\n"); return TYPE_MISMATCH_ERROR;
	#define DISPARA_UNDEFINED_SYMBOL(varref) printf("UNDEFINED SYMBOL. A variavel %s nao foi declarada.\n", varref); return UNDEFINED_SYMBOL_ERROR;

	/* Globais para valores de literais encontradas */
	int VAL_INT;
	double VAL_DOUBLE;
	symbol_t stable = NULL;
	stack idents = NULL;
	/*
	Comeamos a contar o deslocamento a partir de 1 para SP
	e a partir de -1 para Rx
	0 eh reservado para indicar que o argumento nao foi passado
	na impressao subtraimos um do endereco para obter zero
	*/
	int deslocamento = 1;
	int desloc_temp = -1;
	int proximo_rotulo = 0;
	tac_list codigo_tac = NULL;

	char* gera_rotulo()
	{
		char* rotulo = malloc(10 * sizeof(char));
		sprintf(rotulo, "Label%03i", proximo_rotulo++);
		return rotulo;
	}

	tac_list gera_if( int op, int arg1, int arg2, char* literal1, char* literal2, char* literal3)
	{
		tac_list new;
		tac_instruction* taci;
		init_list(&new);
		taci = malloc(sizeof(tac_instruction));
		taci->op = op;
		taci->arg1 = arg1;
		taci->arg2 = arg2;
		taci->res = 0;
		taci->literal1 = literal1;
		taci->literal2 = literal2;
		taci->literal3 = literal3;
		append(new, taci);
		return new;
	}
	
	tac_list gera_codigo( int op, int arg1, int arg2, int res, char* literal1, char* literal2)
	{
		tac_list new;
		tac_instruction* taci;
		init_list(&new);
		taci = malloc(sizeof(tac_instruction));
		taci->op = op;
		taci->arg1 = arg1;
		taci->arg2 = arg2;
		taci->res = res;
		taci->literal1 = literal1;
		taci->literal2 = literal2;
		append(new, taci);
//		printf("APPEND: %i %i %i %i %s %s\n", taci->op, taci->arg1, taci->arg2, taci->res, taci->literal1, taci->literal2);
		return new;
	}

	int gera_codigo_aritmetico( int op, struct einfo* arg1, struct einfo* arg2, struct einfo* res)
	{
		tac_list cod_gerado;
		int fop;

		if(arg1->type == CHAR || arg2->type == CHAR)
			return -1;

		switch(op)
		{
			case ADD:
				fop = FADD;
				break;
			case SUB:
				fop = FSUB;
				break;
			case MUL:
				fop = FMUL;
				break;
			case DIV:
				fop = FDIV;
				break;
			// Nunca deve chegar no default (soh em caso de erro)
			default:
				fop = op;
		}

		if(arg1->type == INT && arg2->type == INT)
		{
			res->type = INT;
			res->desloc = gera_temp(INT);
			cod_gerado = gera_codigo(op, arg1->desloc, arg2->desloc, res->desloc, arg1->literal, arg2->literal);
		}
		else if(arg1->type == arg2->type)
		{
			res->type = (arg1->type == FLOAT ? FLOAT : DOUBLE);
			res->desloc = gera_temp(res->type);
			cod_gerado = gera_codigo(fop, arg1->desloc, arg2->desloc, res->desloc, arg1->literal, arg2->literal);
		}
		else
		{
			struct einfo* arg_upcast;
			struct einfo* arg;
			int upcast_tmp;
			
			/*
			Escolhemos o maior tipo envolvido para o tipo do resultado
			*/
			if(arg1->type == DOUBLE || arg2->type == DOUBLE)
				res->type = DOUBLE;
			else
				res->type = FLOAT;

			upcast_tmp = gera_temp(res->type);
			res->desloc = gera_temp(res->type);

			if((arg1->type == FLOAT && arg2->type == INT) || (arg1->type == DOUBLE))
			{
				arg = arg1;
				arg_upcast = arg2;
			}
			else
			{
				arg = arg2;
				arg_upcast = arg1;
			}
			cod_gerado = gera_codigo(0, arg_upcast->desloc, 0, upcast_tmp, arg_upcast->literal, NULL);
			cod_gerado = concat_tac(cod_gerado, gera_codigo(fop, arg->desloc, upcast_tmp, res->desloc, arg->literal, NULL));
		}
		res->codigo = (void*) concat_tac(concat_tac((tac_list) arg1->codigo, (tac_list) arg2->codigo), cod_gerado);
		return 0;
	}

	int gera_temp(int type)
	{
		int tmp = desloc_temp;
		desloc_temp -= get_size(type);
		return tmp;
	}

	int get_size(int type)
	{
		switch(type)
		{
			case INT:
				return 4;
				break;
			case DOUBLE:
				return 8;
				break;
			case FLOAT:
				return 4;
				break;
			case CHAR:
				return 1;
				break;
		}
		return -1;
	}



/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
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

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 238 "pico.y"
{
	char* name;
	struct tinfo{ 
		int type;
		int size;
		void* extra;
	} tinfo;
	struct linfo {
		char* text;
		int int_val;
		double double_val;
	} linfo;
	struct einfo {
		int type;
		int desloc;
		char* literal;
		void* codigo;
		int ndim;
		void* stable_e;
		char* labelt;
		char* labelf;
	} einfo;
	char* double_val;
}
/* Line 187 of yacc.c.  */
#line 393 "y.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 406 "y.tab.c"

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
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
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
  yytype_int16 yyss;
  YYSTYPE yyvs;
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
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  31
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   168

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  56
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  22
/* YYNRULES -- Number of rules.  */
#define YYNRULES  58
/* YYNRULES -- Number of states.  */
#define YYNSTATES  113

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   300

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    47,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    48,    46,
      54,    51,    55,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    49,     2,    50,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    52,     2,    53,     2,     2,     2,     2,
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
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     6,     8,    10,    14,    17,    21,    24,
      26,    30,    32,    34,    36,    38,    44,    49,    51,    55,
      58,    60,    62,    66,    68,    71,    75,    79,    83,    87,
      91,    95,    99,   101,   103,   105,   107,   111,   115,   118,
     120,   122,   124,   126,   134,   138,   140,   148,   150,   152,
     156,   160,   164,   168,   172,   176,   180,   184,   188
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      57,     0,    -1,    58,    64,    -1,    64,    -1,    59,    -1,
      58,    46,    59,    -1,    60,    61,    -1,     3,    47,    60,
      -1,     3,    48,    -1,    62,    -1,    62,    49,    63,    -1,
      19,    -1,    20,    -1,    21,    -1,    22,    -1,    16,    48,
      16,    47,    63,    -1,    16,    48,    16,    50,    -1,    65,
      -1,    65,    46,    64,    -1,    72,    64,    -1,    66,    -1,
      72,    -1,    67,    51,    69,    -1,     3,    -1,    68,    50,
      -1,    68,    47,    69,    -1,     3,    49,    69,    -1,    69,
       8,    69,    -1,    69,     9,    69,    -1,    69,     7,    69,
      -1,    69,    10,    69,    -1,     5,    69,     6,    -1,    16,
      -1,    15,    -1,    67,    -1,    70,    -1,     3,     5,    71,
      -1,    69,    47,    71,    -1,    69,     6,    -1,    69,    -1,
      73,    -1,    74,    -1,    76,    -1,    32,     5,    77,     6,
      33,    64,    75,    -1,    34,    64,    37,    -1,    37,    -1,
      35,     5,    77,     6,    52,    64,    53,    -1,    38,    -1,
      39,    -1,     5,    77,     6,    -1,    77,    29,    77,    -1,
      77,    30,    77,    -1,    69,    54,    69,    -1,    69,    55,
      69,    -1,    69,    25,    69,    -1,    69,    26,    69,    -1,
      69,    27,    69,    -1,    69,    28,    69,    -1,    31,    77,
      -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   280,   280,   281,   284,   285,   291,   321,   325,   331,
     336,   343,   344,   345,   346,   349,   354,   367,   368,   369,
     372,   373,   376,   387,   399,   415,   434,   457,   464,   471,
     478,   485,   492,   499,   506,   518,   521,   547,   553,   561,
     562,   565,   566,   569,   575,   576,   579,   582,   586,   590,
     594,   595,   596,   597,   598,   599,   600,   601,   602
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "IDF", "VAZIO", "OPEN_PAR", "CLOSE_PAR",
  "MUL", "ADD", "SUB", "DIV", "FMUL", "FADD", "FSUB", "FDIV", "F_LIT",
  "INT_LIT", "DIG", "OPCMP", "INT", "DOUBLE", "FLOAT", "CHAR", "QUOTE",
  "DQUOTE", "LE", "GE", "EQ", "NE", "AND", "OR", "NOT", "IF", "THEN",
  "ELSE", "WHILE", "BRANCO", "END", "TRUE", "FALSE", "PRINT", "FPRINT",
  "RDEF", "LDEF", "GOTO", "LABEL", "';'", "','", "':'", "'['", "']'",
  "'='", "'{'", "'}'", "'<'", "'>'", "$accept", "code", "decls", "decl",
  "ident", "types", "type", "type_array", "action", "command", "attr",
  "lvalue", "expr_list", "expr", "proc_call", "expr_list2", "simple_enun",
  "control_instr", "if_expr", "if_end", "while_expr", "bool_expr", 0
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
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,    59,    44,    58,    91,
      93,    61,   123,   125,    60,    62
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    56,    57,    57,    58,    58,    59,    60,    60,    61,
      61,    62,    62,    62,    62,    63,    63,    64,    64,    64,
      65,    65,    66,    67,    67,    68,    68,    69,    69,    69,
      69,    69,    69,    69,    69,    69,    70,    71,    71,    72,
      72,    73,    73,    74,    75,    75,    76,    77,    77,    77,
      77,    77,    77,    77,    77,    77,    77,    77,    77
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     1,     1,     3,     2,     3,     2,     1,
       3,     1,     1,     1,     1,     5,     4,     1,     3,     2,
       1,     1,     3,     1,     2,     3,     3,     3,     3,     3,
       3,     3,     1,     1,     1,     1,     3,     3,     2,     1,
       1,     1,     1,     7,     3,     1,     7,     1,     1,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     2
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    23,     0,    33,    32,     0,     0,     0,     0,     4,
       0,     3,    17,    20,    34,     0,    39,    35,    21,    40,
      41,    42,     0,     0,     8,     0,    23,    34,     0,     0,
       0,     1,     0,     2,    11,    12,    13,    14,     6,     9,
       0,     0,     0,    24,     0,     0,     0,     0,    19,     0,
      36,     0,     7,    26,    31,     0,     0,    47,    48,     0,
       0,     0,     5,     0,    18,    22,    25,    29,    27,    28,
      30,    38,     0,     0,     0,    58,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    10,    37,    49,
      54,    55,    56,    57,    52,    53,     0,    50,    51,     0,
       0,     0,     0,     0,     0,    45,    43,    46,     0,    16,
       0,    15,    44
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     7,     8,     9,    10,    38,    39,    87,    11,    12,
      13,    27,    15,    16,    17,    50,    18,    19,    20,   106,
      21,    60
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -46
static const yytype_int16 yypact[] =
{
     125,     2,   134,   -46,   -46,    27,    33,     6,     9,   -46,
     146,   -46,   -29,   -46,   -12,   -45,    12,   -46,   129,   -46,
     -46,   -46,   134,    56,   -46,   134,     5,   -46,    58,    55,
      55,   -46,    56,   -46,   -46,   -46,   -46,   -46,   -46,    25,
     129,   134,   134,   -46,   134,   134,   134,   134,   -46,   104,
     -46,   -32,   -46,    12,   -46,    55,    55,   -46,   -46,    93,
      -2,     7,   -46,    45,   -46,    12,    12,   -46,    62,    62,
     -46,   -46,   134,    99,    23,   -46,   134,   134,   134,   134,
     134,   134,    42,    55,    55,    24,    35,   -46,   -46,   -46,
      12,    12,    12,    12,    12,    12,   129,   -46,    66,   129,
      82,    53,    63,    41,   129,   -46,   -46,   -46,    45,   -46,
      78,   -46,   -46
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -46,   -46,   -46,    85,   100,   -46,   -46,    14,    -7,   -46,
     -46,     0,   -46,     1,   -46,    57,   -46,   -46,   -46,   -46,
     -46,   -21
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      14,    33,    42,    28,    82,    43,    31,    22,    14,    61,
      22,    48,    26,    85,     2,    23,    24,    40,    14,    44,
      45,    46,    47,    49,     3,     4,    53,    83,    84,    89,
      59,    59,    29,    64,    74,    75,    83,    84,    30,    41,
      14,     5,    65,    66,     6,    67,    68,    69,    70,    23,
      24,    25,    83,    84,    25,    32,    73,    59,    26,    51,
      55,    86,    97,    98,    54,    44,    45,    46,    47,    44,
       3,     4,    47,    49,    63,    96,    99,    90,    91,    92,
      93,    94,    95,   100,    59,    59,    56,   104,   108,   101,
     105,   109,   102,    57,    58,    83,    14,   110,   103,    14,
      44,    45,    46,    47,    14,    54,    44,    45,    46,    47,
      71,    44,    45,    46,    47,   112,   107,    62,    76,    77,
      78,    79,   111,    52,    76,    77,    78,    79,     1,    88,
       2,     0,    26,     0,     2,     0,     0,    26,     0,     2,
       3,     4,     0,     0,     3,     4,     0,    80,    81,     3,
       4,    72,     0,    80,    81,     0,     0,     5,     0,     0,
       6,     5,     0,     0,     6,    34,    35,    36,    37
};

static const yytype_int8 yycheck[] =
{
       0,     8,    47,     2,     6,    50,     0,     5,     8,    30,
       5,    18,     3,     6,     5,    47,    48,    46,    18,     7,
       8,     9,    10,    22,    15,    16,    25,    29,    30,     6,
      29,    30,     5,    40,    55,    56,    29,    30,     5,    51,
      40,    32,    41,    42,    35,    44,    45,    46,    47,    47,
      48,    49,    29,    30,    49,    46,    55,    56,     3,     3,
       5,    16,    83,    84,     6,     7,     8,     9,    10,     7,
      15,    16,    10,    72,    49,    33,    52,    76,    77,    78,
      79,    80,    81,    48,    83,    84,    31,    34,    47,    96,
      37,    50,    99,    38,    39,    29,    96,   104,    16,    99,
       7,     8,     9,    10,   104,     6,     7,     8,     9,    10,
       6,     7,     8,     9,    10,    37,    53,    32,    25,    26,
      27,    28,   108,    23,    25,    26,    27,    28,     3,    72,
       5,    -1,     3,    -1,     5,    -1,    -1,     3,    -1,     5,
      15,    16,    -1,    -1,    15,    16,    -1,    54,    55,    15,
      16,    47,    -1,    54,    55,    -1,    -1,    32,    -1,    -1,
      35,    32,    -1,    -1,    35,    19,    20,    21,    22
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     5,    15,    16,    32,    35,    57,    58,    59,
      60,    64,    65,    66,    67,    68,    69,    70,    72,    73,
      74,    76,     5,    47,    48,    49,     3,    67,    69,     5,
       5,     0,    46,    64,    19,    20,    21,    22,    61,    62,
      46,    51,    47,    50,     7,     8,     9,    10,    64,    69,
      71,     3,    60,    69,     6,     5,    31,    38,    39,    69,
      77,    77,    59,    49,    64,    69,    69,    69,    69,    69,
      69,     6,    47,    69,    77,    77,    25,    26,    27,    28,
      54,    55,     6,    29,    30,     6,    16,    63,    71,     6,
      69,    69,    69,    69,    69,    69,    33,    77,    77,    52,
      48,    64,    64,    16,    34,    37,    75,    53,    47,    50,
      64,    63,    37
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
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
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
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
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



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

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
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

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
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

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

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
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

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
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
        case 6:
#line 291 "pico.y"
    {
								entry_t *idf;
								char* id;								
								while(1)
								{
									id = (char*) pop(&idents);
									if(id == NULL)
										break;
									idf = malloc(sizeof(entry_t));
									idf->name = malloc(sizeof(char) * (strlen(id) + 1));
									strcpy(idf->name, id);
									idf->type = (yyvsp[(2) - (2)].tinfo).type;
									idf->size = get_size((yyvsp[(2) - (2)].tinfo).type) * ((yyvsp[(2) - (2)].tinfo).size ? (yyvsp[(2) - (2)].tinfo).size : 1);
									idf->desloc = deslocamento;
									deslocamento += idf->size;
								
									if((yyvsp[(2) - (2)].tinfo).extra != NULL)
									{
	/*
										printf("==== Inicio de decl de array. Dimensoes: %03i =====\n", count_dim((stack) $2.extra));
										print_array_data((stack) $2.extra);
										printf("=================== Fim de array ==================\n");
	*/
										idf->extra = (yyvsp[(2) - (2)].tinfo).extra;
									}
									insert(&stable, idf);
//									printf("Decl da var %s tipo: %i tamanho: %i desloc: %i el: %i\n", id, $2.type, idf->size, idf->desloc, $2.size);
								}
							}
    break;

  case 7:
#line 322 "pico.y"
    {
					push(&idents, (yyvsp[(1) - (3)].name));
				}
    break;

  case 8:
#line 326 "pico.y"
    {
					push(&idents, (yyvsp[(1) - (2)].name));
				}
    break;

  case 9:
#line 332 "pico.y"
    { 
					(yyval.tinfo).size = 0;
					(yyval.tinfo).extra = NULL;
				}
    break;

  case 10:
#line 337 "pico.y"
    {
					(yyval.tinfo).size = (yyvsp[(3) - (3)].tinfo).size; 
					(yyval.tinfo).extra = (yyvsp[(3) - (3)].tinfo).extra;
				}
    break;

  case 15:
#line 350 "pico.y"
    {
							(yyval.tinfo).size = ((yyvsp[(3) - (5)].linfo).int_val - (yyvsp[(1) - (5)].linfo).int_val) + 1 + (yyvsp[(5) - (5)].tinfo).size;
							(yyval.tinfo).extra = (void*) append_dim((stack*) &((yyvsp[(5) - (5)].tinfo).extra), ((yyval.tinfo).size - (yyvsp[(5) - (5)].tinfo).size));
						}
    break;

  case 16:
#line 355 "pico.y"
    {
							(yyval.tinfo).size = ((yyvsp[(3) - (4)].linfo).int_val - (yyvsp[(1) - (4)].linfo).int_val) + 1;
							stack adata = NULL;
							append_dim(&adata, (yyval.tinfo).size);
							(yyval.tinfo).extra = (void*) adata;
							adata = NULL;
						}
    break;

  case 22:
#line 377 "pico.y"
    {
					tac_list cod_gerado;
					if((yyvsp[(1) - (3)].einfo).stable_e == NULL && (yyvsp[(3) - (3)].einfo).stable_e == NULL)
						cod_gerado = gera_codigo(0, (yyvsp[(3) - (3)].einfo).desloc, 0, (yyvsp[(1) - (3)].einfo).desloc, (yyvsp[(3) - (3)].einfo).literal, NULL);
					else
						cod_gerado = gera_codigo(LDEF, (yyvsp[(1) - (3)].einfo).desloc, (yyvsp[(3) - (3)].einfo).desloc, ((entry_t*) (yyvsp[(1) - (3)].einfo).stable_e)->desloc, NULL, (yyvsp[(3) - (3)].einfo).literal);
					codigo_tac = concat_tac(codigo_tac, concat_tac((yyvsp[(3) - (3)].einfo).codigo, cod_gerado));
				}
    break;

  case 23:
#line 388 "pico.y"
    {
					entry_t *idf = NULL;
					idf = lookup(stable, (yyvsp[(1) - (1)].name));
					if( idf == NULL )
					{
						DISPARA_UNDEFINED_SYMBOL((yyvsp[(1) - (1)].name))
					}
					(yyval.einfo).type = idf->type;
					(yyval.einfo).desloc = idf->desloc;
					(yyval.einfo).stable_e = NULL;
				}
    break;

  case 24:
#line 400 "pico.y"
    {
					int tmp = gera_temp(INT);
					char* num_w = (char*) malloc(sizeof(char) * 6);

					(yyval.einfo).desloc = gera_temp(INT);
					(yyval.einfo).type = (yyvsp[(1) - (2)].einfo).type;
					(yyval.einfo).stable_e = (yyvsp[(1) - (2)].einfo).stable_e;
					sprintf(num_w, "%i", get_size(((entry_t*) (yyvsp[(1) - (2)].einfo).stable_e)->type));
//					printf("Tipo do expr_list: %i tamanho: %s desloc: %i desloc do ar:%i\n", $1.type, num_w, $1.desloc, ((entry_t*) $1.stable_e)->desloc);
					codigo_tac = concat_tac(codigo_tac,                                               
															concat_tac(gera_codigo(MUL, (yyvsp[(1) - (2)].einfo).desloc, 0, tmp, (yyvsp[(1) - (2)].einfo).literal, num_w), 
																				gera_codigo(ADD, ((entry_t*) (yyvsp[(1) - (2)].einfo).stable_e)->desloc, tmp, (yyval.einfo).desloc, (yyvsp[(1) - (2)].einfo).literal, NULL)));
				}
    break;

  case 25:
#line 416 "pico.y"
    {
						int tmp = gera_temp(INT);
						int dim = (yyvsp[(1) - (3)].einfo).ndim + 1;
						char* num = (char*) malloc(sizeof(char) * 6);
						sprintf(num, "%i", len_dim((stack) ((entry_t*) (yyvsp[(1) - (3)].einfo).stable_e)->extra, dim));
//						printf("lendim: %s dim: %i desloc: %i lit:%s\n", num, dim, $1.desloc, $1.literal);
						codigo_tac = concat_tac(codigo_tac, 
											concat_tac((yyvsp[(3) - (3)].einfo).codigo,
											concat_tac(gera_codigo(MUL, (yyvsp[(1) - (3)].einfo).desloc, 0, tmp, (yyvsp[(1) - (3)].einfo).literal, num),
																	gera_codigo(ADD, tmp, (yyvsp[(3) - (3)].einfo).desloc, tmp, NULL, (yyvsp[(3) - (3)].einfo).literal))));
						(yyval.einfo).stable_e = (yyvsp[(1) - (3)].einfo).stable_e;
						(yyval.einfo).desloc = tmp;
						(yyval.einfo).ndim = dim;
						if((yyvsp[(3) - (3)].einfo).type != INT)
						{
							DISPARA_TYPE_MISMATCH()
						}
					}
    break;

  case 26:
#line 435 "pico.y"
    {
						tac_list cod_gerado = NULL;
						entry_t *idf = NULL;
						idf = lookup(stable, (yyvsp[(1) - (3)].name));
						if( idf == NULL )
						{
							DISPARA_UNDEFINED_SYMBOL((yyvsp[(1) - (3)].name))
						}
//						printf("ARRAY: %s\n", $1);
						(yyval.einfo).stable_e = (void*) idf;
						(yyval.einfo).desloc = (yyvsp[(3) - (3)].einfo).desloc;
						(yyval.einfo).literal = (yyvsp[(3) - (3)].einfo).literal;
						(yyval.einfo).ndim = 1;
						(yyval.einfo).type = idf->type;
						if((yyvsp[(3) - (3)].einfo).type != INT)
						{
							DISPARA_TYPE_MISMATCH()
						}
						codigo_tac = concat_tac(codigo_tac, (yyvsp[(3) - (3)].einfo).codigo);
					}
    break;

  case 27:
#line 458 "pico.y"
    {
					if(gera_codigo_aritmetico(ADD, &(yyvsp[(1) - (3)].einfo), &(yyvsp[(3) - (3)].einfo), &(yyval.einfo)) < 0)
					{
						DISPARA_TYPE_MISMATCH()
					}
				}
    break;

  case 28:
#line 465 "pico.y"
    {
					if(gera_codigo_aritmetico(SUB, &(yyvsp[(1) - (3)].einfo), &(yyvsp[(3) - (3)].einfo), &(yyval.einfo)) < 0)
					{
						DISPARA_TYPE_MISMATCH()
					}
				}
    break;

  case 29:
#line 472 "pico.y"
    {
					if(gera_codigo_aritmetico(MUL, &(yyvsp[(1) - (3)].einfo), &(yyvsp[(3) - (3)].einfo), &(yyval.einfo)) < 0)
					{
						DISPARA_TYPE_MISMATCH()
					}
				}
    break;

  case 30:
#line 479 "pico.y"
    {
					if(gera_codigo_aritmetico(DIV, &(yyvsp[(1) - (3)].einfo), &(yyvsp[(3) - (3)].einfo), &(yyval.einfo)) < 0)
					{
						DISPARA_TYPE_MISMATCH()
					}
				}
    break;

  case 31:
#line 486 "pico.y"
    {
					(yyval.einfo).type = (yyvsp[(2) - (3)].einfo).type;
					(yyval.einfo).desloc = (yyvsp[(2) - (3)].einfo).desloc;
					(yyval.einfo).codigo = (yyvsp[(2) - (3)].einfo).codigo;
					(yyval.einfo).literal = (yyvsp[(2) - (3)].einfo).literal;
				}
    break;

  case 32:
#line 493 "pico.y"
    {
					(yyval.einfo).type = INT;
					(yyval.einfo).codigo = NULL;
					(yyval.einfo).literal = (yyvsp[(1) - (1)].linfo).text;
					(yyval.einfo).desloc = 0;
				}
    break;

  case 33:
#line 500 "pico.y"
    {
					(yyval.einfo).type = FLOAT;
					(yyval.einfo).codigo = NULL;
					(yyval.einfo).literal = (yyvsp[(1) - (1)].linfo).text;
					(yyval.einfo).desloc = 0;
				}
    break;

  case 34:
#line 507 "pico.y"
    {
					tac_list cod_gerado = NULL;
					(yyval.einfo).type = (yyvsp[(1) - (1)].einfo).type;
					(yyval.einfo).desloc = (yyvsp[(1) - (1)].einfo).desloc;
					if((yyvsp[(1) - (1)].einfo).stable_e != NULL)
					{
						cod_gerado = gera_codigo(RDEF, (yyvsp[(1) - (1)].einfo).desloc, ((entry_t*) (yyvsp[(1) - (1)].einfo).stable_e)->desloc, (yyvsp[(1) - (1)].einfo).desloc, NULL, NULL);
						codigo_tac = concat_tac(codigo_tac, cod_gerado);
					}
					(yyval.einfo).stable_e = NULL;
				}
    break;

  case 36:
#line 522 "pico.y"
    {
						if(!strcmp((yyvsp[(1) - (3)].name), "print"))
						{
							int var_print = (yyvsp[(3) - (3)].einfo).desloc;
							if((yyvsp[(3) - (3)].einfo).stable_e != NULL)
							{
								var_print = gera_temp((yyvsp[(3) - (3)].einfo).type);
								(yyval.einfo).codigo = gera_codigo(RDEF, (yyvsp[(3) - (3)].einfo).desloc, ((entry_t*) (yyvsp[(3) - (3)].einfo).stable_e)->desloc, var_print, NULL, NULL);
							}
							if((yyvsp[(3) - (3)].einfo).type == FLOAT || (yyvsp[(3) - (3)].einfo).type == DOUBLE)
							{
								(yyval.einfo).codigo = gera_codigo(FPRINT, var_print, 0, 0, NULL, NULL);
							}
							else if((yyvsp[(3) - (3)].einfo).type == INT)
							{
								(yyval.einfo).codigo = gera_codigo(PRINT, var_print, 0, 0, NULL, NULL);
							}
							else
							{
								DISPARA_TYPE_MISMATCH()
							}
						}
					}
    break;

  case 37:
#line 548 "pico.y"
    { 
					(yyval.einfo).type = (yyvsp[(1) - (3)].einfo).type;
					(yyval.einfo).desloc = (yyvsp[(1) - (3)].einfo).desloc;
					(yyval.einfo).stable_e = (yyvsp[(1) - (3)].einfo).stable_e;
				}
    break;

  case 38:
#line 554 "pico.y"
    { 
					(yyval.einfo).type = (yyvsp[(1) - (2)].einfo).type;
					(yyval.einfo).desloc = (yyvsp[(1) - (2)].einfo).desloc;
					(yyval.einfo).stable_e = (yyvsp[(1) - (2)].einfo).stable_e;
				}
    break;

  case 43:
#line 570 "pico.y"
    {
						(yyvsp[(3) - (7)].einfo).labelt = gera_rotulo();
						codigo_tac = concat_tac(codigo_tac, concat_tac((yyvsp[(3) - (7)].einfo).codigo, gera_codigo(LABEL, 0, 0, 0, (yyvsp[(3) - (7)].einfo).labelt, NULL)));
					}
    break;

  case 47:
#line 583 "pico.y"
    {
						(yyval.einfo).codigo = gera_codigo(GOTO, 0, 0, 0, (yyval.einfo).labelt, NULL);
					}
    break;

  case 48:
#line 587 "pico.y"
    {
						(yyval.einfo).codigo = gera_codigo(GOTO, 0, 0, 0, (yyval.einfo).labelf, NULL);
					}
    break;

  case 49:
#line 591 "pico.y"
    {
						(yyval.einfo).codigo = (yyvsp[(2) - (3)].einfo).codigo;
					}
    break;


/* Line 1267 of yacc.c.  */
#line 2042 "y.tab.c"
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
      /* If just tried and failed to reuse look-ahead token after an
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

  /* Else will try to reuse look-ahead token after shifting the error
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

  if (yyn == YYFINAL)
    YYACCEPT;

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

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
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


#line 607 "pico.y"

 /* A partir daqui, insere-se qlqer codigo C necessario.
  */
#include "lex.yy.c"   /* Para poder usar o scanner */

char* progname;
int lineno;
int yydebug=0;

int main(int argc, char* argv[]) {
	progname = argv[0];

	init_table(&stable);
	init_list(&codigo_tac);
	init_stack(&idents);

	if (!yyparse())
	{
		/*
		Subtraimos 1 do deslocamento pois ele deve comecar no endereco 0
		No delocamento dos temporarios subtraimos 1 do valor absoluto, pois estavamos contando numeros negativos
		*/

		printf("%i\n", deslocamento - 1);
		printf("%i\n", abs(desloc_temp) - 1);
		print_tac(codigo_tac);
//		debug_tac(codigo_tac);
	}
	return(0);

}

yyerror(char* s) {
  fprintf(stderr, "%s: %s", progname, s);
  fprintf(stderr, "line %d\n", lineno);
}



/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

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
     DEF = 297
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
#define DEF 297




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 207 "pico.y"
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
	} einfo;
	char* double_val;
}
/* Line 1489 of yacc.c.  */
#line 156 "y.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;


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
     F_LIT = 266,
     INT_LIT = 267,
     DIG = 268,
     OPCMP = 269,
     INT = 270,
     DOUBLE = 271,
     FLOAT = 272,
     CHAR = 273,
     QUOTE = 274,
     DQUOTE = 275,
     LE = 276,
     GE = 277,
     EQ = 278,
     NE = 279,
     AND = 280,
     OR = 281,
     NOT = 282,
     IF = 283,
     THEN = 284,
     ELSE = 285,
     WHILE = 286,
     BRANCO = 287,
     END = 288,
     TRUE = 289,
     FALSE = 290
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
#define F_LIT 266
#define INT_LIT 267
#define DIG 268
#define OPCMP 269
#define INT 270
#define DOUBLE 271
#define FLOAT 272
#define CHAR 273
#define QUOTE 274
#define DQUOTE 275
#define LE 276
#define GE 277
#define EQ 278
#define NE 279
#define AND 280
#define OR 281
#define NOT 282
#define IF 283
#define THEN 284
#define ELSE 285
#define WHILE 286
#define BRANCO 287
#define END 288
#define TRUE 289
#define FALSE 290




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 79 "pico.y"
{
	char* name;
	struct tinfo{ 
		int type;
		int size;
	} tinfo;
	int nelements;
	int int_val;
	double double_val;
}
/* Line 1489 of yacc.c.  */
#line 130 "y.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;


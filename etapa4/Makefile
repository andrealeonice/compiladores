#
# UFRGS - Compiladores B - Marcelo Johann - 2020/2 - Etapa 4
#
# Makefile for single compiler call
# All source files must be included from code embedded in scanner.l
# In our case, you probably need #include "hash.c" at the beginning
# and #include "main.c" in the last part of the scanner.l
#

etapa3: main.o lex.yy.o y.tab.o hash.o ast.o semantic.o
	gcc main.o lex.yy.o y.tab.o hash.o ast.o semantic.o -o etapa4

main.o: main.c
	gcc -c main.c

semantic.o: semantic.c
	gcc -c semantic.c

lex.yy.o: lex.yy.c
	gcc -c lex.yy.c

y.tab.o: y.tab.c
	gcc -c y.tab.c
	
hash.o: hash.c
	gcc -c hash.c

ast.o: ast.c
	gcc -c ast.c

y.tab.c: parser.y
	yacc -d parser.y

lex.yy.c: scanner.l
	lex scanner.l

clean:
	rm lex.yy.c y.tab.c *.o etapa4 

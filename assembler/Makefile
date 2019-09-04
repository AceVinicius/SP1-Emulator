all: sp1.tab.c sp1.tab.h lex.yy.c
	gcc sp1.tab.c lex.yy.c -Ofast -o sp1_assembler
tab: sp1.y sp1.l
	bison -dv sp1.y
	flex sp1.l

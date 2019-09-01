a.out: lex.yy.o y.tab.o asgn4_17CS10061.o
	gcc lex.yy.o y.tab.o asgn4_17CS10061.o -lfl

asgn4_17CS10061.o: asgn4_17CS10061.c
	gcc -c asgn4_17CS10061.c

lex.yy.o: lex.yy.c
	gcc -c lex.yy.c -lfl

y.tab.o: y.tab.c
	gcc -c y.tab.c

lex.yy.c: asgn4_17CS10061.l y.tab.h
	flex asgn4_17CS10061.l

y.tab.c: asgn4_17CS10061.y
	yacc -dtv asgn4_17CS10061.y -W

y.tab.h: asgn4_17CS10061.y
	yacc -dtv asgn4_17CS10061.y -W

clean:
	rm lex.yy.c y.tab.c y.tab.h lex.yy.o y.tab.o asgn4_17CS10061.o y.output a.out asgn4_17CS10061_output

test: 
	./a.out < asgn4_17CS10061_test.c > asgn4_17CS10061_output

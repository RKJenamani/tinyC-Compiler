Test.txt: a.out ass3_17CS10061_test.c
	./a.out < ass3_17CS10061_test.c > Test.txt

a.out: lex.yy.o
		gcc lex.yy.o -lfl
		
lex.yy.o: lex.yy.c
		gcc -c lex.yy.c -lfl
		
lex.yy.c: ass3_17CS10061.l ass3_17CS10061.c
	flex ass3_17CS10061.l ass3_17CS10061.c

clean:
	rm  a.out lex.yy.c lex.yy.o Test.txt





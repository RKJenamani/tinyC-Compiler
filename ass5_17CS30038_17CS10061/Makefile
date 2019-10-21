all: a.out
	
	./a.out < ass5_17CS30038_17CS10061_test1.c > ass5_17CS30038_17CS10061_quads1.out
	@echo "Test File 1 Successfully Translated !\n"
	./a.out < ass5_17CS30038_17CS10061_test2.c > ass5_17CS30038_17CS10061_quads2.out
	@echo "Test File 2 Successfully Translated !\n"
	./a.out < ass5_17CS30038_17CS10061_test3.c > ass5_17CS30038_17CS10061_quads3.out
	@echo "Test File 3 Successfully Translated !\n"
	./a.out < ass5_17CS30038_17CS10061_test4.c > ass5_17CS30038_17CS10061_quads4.out
	@echo "Test File 4 Successfully Translated !\n"
	./a.out < ass5_17CS30038_17CS10061_test5.c > ass5_17CS30038_17CS10061_quads5.out
	@echo "Test File 5 Successfully Translated !\n"
	./a.out < ass5_17CS30038_17CS10061_test6.c > ass5_17CS30038_17CS10061_quads6.out
	@echo "Test File 6 Successfully Translated !\n"
	./a.out < ass5_17CS30038_17CS10061_test7.c > ass5_17CS30038_17CS10061_quads7.out
	@echo "Test File 7 Successfully Translated !\n"

	@echo "\nALL TEST FILES SUCCESSFULLY TRANSLATED !!\n"

a.out: lex.yy.o y.tab.o ass5_17CS30038_17CS10061_translator.o
	g++ lex.yy.o y.tab.o ass5_17CS30038_17CS10061_translator.o -lfl

ass5_17CS30038_17CS10061_translator.o: ass5_17CS30038_17CS10061_translator.cxx ass5_17CS30038_17CS10061_translator.h
	g++ -c ass5_17CS30038_17CS10061_translator.h
	g++ -c ass5_17CS30038_17CS10061_translator.cxx

lex.yy.o: lex.yy.c
	g++ -c lex.yy.c

y.tab.o: y.tab.c
	g++ -c y.tab.c

lex.yy.c: ass5_17CS30038_17CS10061.l y.tab.h ass5_17CS30038_17CS10061_translator.h
	flex ass5_17CS30038_17CS10061.l

y.tab.c: ass5_17CS30038_17CS10061.y
	yacc -dtv ass5_17CS30038_17CS10061.y -W

y.tab.h: ass5_17CS30038_17CS10061.y
	yacc -dtv ass5_17CS30038_17CS10061.y -W

clean:
	rm lex.yy.c y.tab.c y.tab.h lex.yy.o y.tab.o ass5_17CS30038_17CS10061_translator.o y.output a.out ass5_17CS30038_17CS10061_translator.h.gch

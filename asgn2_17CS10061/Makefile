a.out: main.o libass2_17CS10061.a 
	c++ main.o -L. -lass2_17CS10061

main.o: main.c myl.h
	c++ -Wall -c main.c 

libass2_17CS10061.a: ass2_17CS10061.o
	ar -rcs libass2_17CS10061.a ass2_17CS10061.o

ass2_17CS10061.o: ass2_17CS10061.c myl.h
	c++ -Wall -c ass2_17CS10061.c

clean:
	rm a.out main.o libass2_17CS10061.a ass2_17CS10061.o
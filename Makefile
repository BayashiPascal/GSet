OPTIONS_DEBUG=-ggdb -g3 -Wall
OPTIONS_RELEASE=-O3
OPTIONS=$(OPTIONS_RELEASE)

all : gset

clean:
	rm *.o gset
	
gset : gset_main.o gset.o Makefile
	gcc gset_main.o gset.o $(OPTIONS) -o gset -lm 

gset_main.o : gset.h gset_main.c Makefile
	gcc -c gset_main.c $(OPTIONS)

gset.o : gset.c gset.h Makefile
	gcc -c gset.c $(OPTIONS)

install: 
	cp gset.h ../Include; cp gset.o ../Include
	
valgrind :
	valgrind -v --track-origins=yes --leak-check=full --gen-suppressions=yes --show-leak-kinds=all ./gset

# Compiler
COMPILER=gcc

# Build mode 0:dev, 1:prod
BUILD_MODE=0

# Compiler arguments depending on BUILD_MODE
ifeq ($(BUILD_MODE), 0)
	BUILD_ARG=-I./ -Wall -Wextra -Og -ggdb -g3 -DBUILDMODE=$(BUILD_MODE)
	LINK_ARG=-lm -ltrycatchc
else ifeq ($(BUILD_MODE), 1)
	BUILD_ARG=-I./ -Wall -Wextra -Werror -Wfatal-errors -Wno-clobbered -O3 -DBUILDMODE=$(BUILD_MODE)
	LINK_ARG=-lm -ltrycatchc
endif

# Rules

all: main

main: /usr/local/lib/libtrycatchc.a gset.o main.o Makefile
	$(COMPILER) main.o gset.o $(LINK_ARG) -o main 

main.o: main.c gset.h Makefile
	$(COMPILER) $(BUILD_ARG) -c main.c 

gset.o: gset.c gset.h Makefile
	$(COMPILER) $(BUILD_ARG) -c gset.c

/usr/local/lib/libtrycatchc.a:
	wget https://github.com/BayashiPascal/TryCatchC/archive/main.zip
	unzip main.zip
	rm -rf TryCatchC
	mv TryCatchC-main TryCatchC
	rm main.zip
	cd TryCatchC && make && sudo make install
	rm -rf TryCatchC

clean:
	rm -f *.o main

valgrind : main
	valgrind -v --track-origins=yes --leak-check=full \
	--gen-suppressions=yes --show-leak-kinds=all ./main

install: gset.o
	rm -rf /usr/local/include/GSet
	mkdir /usr/local/include/GSet
	cp gset.h /usr/local/include/GSet/gset.h
	ar -r /usr/local/lib/libgset.a gset.o
	cp gset /usr/local/bin/gset

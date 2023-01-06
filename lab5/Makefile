GCC=gcc

all: main2

library1.o:
	$(GCC) -fPIC -c ./src/functions1.c -lm -o library1.o

library2.o:
	$(GCC) -fPIC -c ./src/functions2.c -lm -o library2.o

library1.so: library1.o
	$(GCC) -shared -o library1.so library1.o -lm

library2.so: library2.o
	$(GCC) -shared -o library2.so library2.o -lm

main2: main2.c library1.so library2.so
	$(GCC) -o main2 main2.c -lm -ldl

GCC=gcc

all: main1 main2

library1.o:
	$(GCC) -fPIC -c ./src/functions1.c -lm -o library1.o

library2.o:
	$(GCC) -fPIC -c ./src/functions2.c -lm -o library2.o

library1.so: library1.o
	$(GCC) -shared -o library1.so library1.o -lm

library2.so: library2.o
	$(GCC) -shared -o library2.so library2.o -lm

main1: library1.so
	$(GCC) -o static main1.c -lm ./src/functions1.c

main2: main2.c library1.so library2.so
	$(GCC) -o dynamic main2.c -lm -ldl

clean:
	rm -rf *.o 
	rm -rf *.so
	rm -rf static
	rm -rf dynamic
all: metodos.o principal.o
	gcc metodos.o principal.o -o exe -lm

principal: principal.c
	gcc -c principal.c -o principal.o -lm

metodos: metodos.c
	gcc -c metodos.c -o metodos.o -lm

clear:
	rm *.o

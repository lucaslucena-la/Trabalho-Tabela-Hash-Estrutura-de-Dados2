all:  tab_hash.o gera_arquivo.o main.o
	gcc tab_hash.o gera_arquivo.o main.o -o prog
	./prog

tab_hash.c:
	gcc -c tab_hash.c

gera_arquivo.c:
	gcc -c gera_arquivo.c

main.o: main.c
	gcc -c main.c
	
run: prog
	./prog

clean:
	rm *.o prog
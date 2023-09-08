all: final
 
final: main.o functions.o
	gcc -m32 functions.o main.o -lm -o final
 
main.o: main.c
	gcc -m32 -c main.c -o main.o
 
functions.o: functions.asm
	nasm -f elf32 -o functions.o functions.asm
 
clean:
	rm -rf *.o final
main: main.o
	ld -o main main.o \
	-dynamic-linker /usr/lib64/ld-linux-x86-64.so.2 \
	-lc -g -L./raylib/ -lglfw -lraylib -lm -lX11

main.o: main.asm create_cards.inc
	fasm main.asm

test:
	gcc -O3 -g -o test test.c -L./raylib/ -lglfw -lraylib -lm -lX11
	objdump -M intel --disassemble=main test

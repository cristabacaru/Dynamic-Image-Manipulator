CFLAGS=-Wall -Werror

.PHONY: clean run-main run-interactive

run-main: main
	./main

run-interactive: interactive
	./interactive

interactive: interactive.c imageprocessing.c bmp.c
	gcc interactive.c imageprocessing.c bmp.c $(CFLAGS) -o interactive -ggdb3

main: main.c imageprocessing.c bmp.c
	gcc main.c imageprocessing.c bmp.c $(CFLAGS) -o main

clean:
	rm -f main interactive

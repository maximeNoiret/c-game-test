COMPILER = gcc
CFLAGS = -Wall -Werror -g -fsanitize=address,undefined
COMPILE_OBJECT = $(COMPILER) $(CFLAGS) -c $< -o $@

game: main.o
	$(COMPILER) $(CFLAGS) -o $@ $^

main.o: main.c
	$(COMPILE_OBJECT)

clean:
	rm -f *.o game

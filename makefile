COMPILER = gcc
CFLAGS = -Wall -Werror -g -fsanitize=address,undefined
COMPILE_OBJECT = $(COMPILER) $(CFLAGS) -c $< -o $@

game: main.o term.o
	$(COMPILER) $(CFLAGS) -o $@ $^

main.o: main.c term.h
	$(COMPILE_OBJECT)

term.o: term.c term.h
	$(COMPILE_OBJECT)

clean:
	rm -f *.o game

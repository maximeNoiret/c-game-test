COMPILER = gcc
CFLAGS = -Wall -Werror -g -fsanitize=address,undefined
COMPILE_OBJECT = $(COMPILER) $(CFLAGS) -c $< -o $@

game: main.o term.o m_game.o
	$(COMPILER) $(CFLAGS) -o $@ $^

main.o: main.c term.h m_game.h
	$(COMPILE_OBJECT)

term.o: term.c term.h m_game.h
	$(COMPILE_OBJECT)

m_game.o: m_game.c m_game.h term.h
	$(COMPILE_OBJECT)

clean:
	rm -f *.o game

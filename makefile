COMPILER = gcc
CFLAGS = -Wall -Werror -g -fsanitize=address,undefined
COMPILE_OBJECT = $(COMPILER) $(CFLAGS) -c $< -o $@

game: main.o termiosManagement.o
	$(COMPILER) $(CFLAGS) -o $@ $^

main.o: main.c termiosManagement.h
	$(COMPILE_OBJECT)

termiosManagement.o: termiosManagement.c termiosManagement.h
	$(COMPILE_OBJECT)

clean:
	rm -f *.o game

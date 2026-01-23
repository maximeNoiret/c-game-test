#define CLEAR "\033[2J"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "termiosManagement.h"

const unsigned TERMINAL_HEIGHT = 24;
const unsigned TERMINAL_WIDTH  = 80;

char *setPos(char *buf, unsigned x, unsigned y) {
	snprintf(buf, 11, "\033[%d;%dH", y, x);
	return buf;
}

int main() {

	char c;
	set_input_mode ();

	char buf[15];
	char *text = "This is a test.";
	unsigned l = strlen(text);
	unsigned x = (TERMINAL_WIDTH >> 1) - (l >> 1);
	unsigned y = (TERMINAL_HEIGHT >> 1) - 1;
	printf(CLEAR"%s%s\n", setPos(buf, x, y), text);
	fflush(stdout);

	for(;;) {
		read(STDIN_FILENO, &c, 1);
		if (c == '\004') break;
		else {
			putchar(c);
			fflush(stdout);
		}
	}
	return 0;
}
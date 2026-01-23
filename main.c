#define CLEAR "\033[2J"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

const unsigned TERMINAL_HEIGHT = 24;
const unsigned TERMINAL_WIDTH  = 80;

char *setPos(char *buf, unsigned x, unsigned y) {
	snprintf(buf, 11, "\033[%d;%dH", y, x);
	return buf;
}

int main() {
	char buf[15];
	char *text = "This is a test.";
	unsigned l = strlen(text);
	unsigned c = (TERMINAL_WIDTH >> 1) - (l >> 1);
	unsigned h = (TERMINAL_HEIGHT >> 1) - 1;
	printf(CLEAR"%s%s\n", setPos(buf, c, h), text);
	return 0;
}
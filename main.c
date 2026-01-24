#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "term.h"

const unsigned TERMINAL_HEIGHT = 24;
const unsigned TERMINAL_WIDTH  = 80;

char *setPos(char *buf, unsigned x, unsigned y) {
	snprintf(buf, 11, "\033[%d;%dH", y, x);
	return buf;
}

int main() {

	char c;
	set_input_mode ();


	printf(CLEAR CRS_HIDE "Make sure to use Ctrl+D to quit or your terminal will hate you.\n");
	for(;;) {
		fflush(stdout);
		read(STDIN_FILENO, &c, 1);
		switch(c) {
		    case 'z': case 'Z':
		        printf(LEFT " " LEFT UP FG_GREEN "@" RST);
		        break;
		    case 's': case 'S':
		    	printf(LEFT " " LEFT DOWN FG_GREEN "@" RST);
		        break;
		    case 'q': case 'Q':
		    	printf(LEFT " " LEFT LEFT FG_GREEN "@" RST);
		        break;
		    case 'd': case 'D':
		    	printf(LEFT " " FG_GREEN "@" RST);
		        break;
		    case '\004': goto fuckyouimusingalabel;
		}
	}
fuckyouimusingalabel:
	printf("\n" CRS_SHOW "Exiting...\n");
	return 0;
}
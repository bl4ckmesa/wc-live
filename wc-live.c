#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

// This code adapted from Stack Overflow question http://stackoverflow.com/questions/3495092/read-from-file-or-stdin-c

long getSizeOfInput(FILE *input){
	long retvalue = 0;
	int c;
	// only print n lines
	int maxn = 5;
	int tn = 0;

	if (input != stdin) {
		if (-1 == fseek(input, 0L, SEEK_END)) {
			fprintf(stderr, "Error seek end: %s\n", strerror(errno));
			exit(EXIT_FAILURE);
		}
		if (-1 == (retvalue = ftell(input))) {
			fprintf(stderr, "ftell failed: %s\n", strerror(errno));
			exit(EXIT_FAILURE);
		}
		if (-1 == fseek(input, 0L, SEEK_SET)) {
			fprintf(stderr, "Error seek start: %s\n", strerror(errno));
			exit(EXIT_FAILURE);
		}
	} else {
		/* for stdin, we need to read in the entire stream until EOF */
		while (EOF != (c = fgetc(input))) {
			if ( c == '\n' ) {
				retvalue++;
				if ( tn >= maxn ) {
					fprintf(stdout, "\rFound %d lines so far.", retvalue);
					tn = 0;
				} else {
					tn++;
				}
			}
		}
	}

	return retvalue;
}

int main(int argc, char **argv) {
	FILE *input;

	if (argc > 1) {
		if(!strcmp(argv[1],"-")) {
			input = stdin;
		} else {
			input = fopen(argv[1],"r");
			if (NULL == input) {
				fprintf(stderr, "Unable to open '%s': %s\n",
						argv[1], strerror(errno));
				exit(EXIT_FAILURE);
			}
		}
	} else {
		input = stdin;
	}

	printf("\rTotal lines: %ld                   \n", getSizeOfInput(input));

	return EXIT_SUCCESS;
}

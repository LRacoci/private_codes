#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "auxTypes.h"
#include "Error.h"
#include "Line.h"
#include "genericDefs.h"

void build(FILE * src, FILE * out) {
	Exception e = NULL;
	Line l = NULL;
	unsigned int i = 0;
	for (
			l = read_first_line(src), i = 0;
			l != NULL;
			free_line(l), l = read_next_line(src, e), i++
		)
	{
		if(l != NULL) l->lnumber = i;
		if(e) {
			set_line_exception(e, i);
			stderror(e);
		}
		fprintLine(l, out);
	}
}
int main(int argc, char *argv[]) {
	FILE *src, *out;
	String out_name;

	switch (argc){
		case 2:
			src = fopen(argv[1], "r");
			out_name = strcat(argv[1], ".hex");
			out = fopen(out_name, "w");
			break;
		case 3:
			src = fopen(argv[1], "r");
			out = fopen(argv[2], "w");
			break;
	}

	if( src == NULL ){
		stderror(
			new_error_exception(
				"Error while opening the source file.\n", -1
			)
		);
		exit(EXIT_FAIL);
	}

	if( out == NULL ){
		stderror(
			new_error_exception(
				"Error while opening the output file.\n", -1
			)
		);
		exit(EXIT_FAIL);
	}
	build(src, out);

	fclose(src);
	fclose(out);
   	return EXIT_SUCESS;
}

#include <stdio.h>
#include <string.h>
#include "auxTypes.h"
#include "Builder.h"

int main(int argc, char *argv[]) {
	FILE *src = NULL, *out = NULL;
	String out_name;
	bool ok;
	switch (argc){
		case 2:
			src = fopen(argv[1], "r");
			out_name = strcat(argv[1], ".aux");
			out = fopen(out_name, "w");
			break;
		case 3:
			src = fopen(argv[1], "r");
			out = fopen(argv[2], "w");
			break;
	}

	if( src == NULL ){
		throw(
			new_error_exception(
				"Error while opening the source file.\n", -1
			)
		);
		exit(EXIT_FAIL);
	}

	if( out == NULL ){
		throw(
			new_error_exception(
				"Error while opening the output file.\n", -1
			)
		);
		exit(EXIT_FAIL);
	}
    ok = build(src, out);

    if(src)
        fclose(src);
    if(out)
        fclose(out);

    return ok? EXIT_SUCESS : EXIT_FAIL;
}

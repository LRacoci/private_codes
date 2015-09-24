#include <stdio.h>
#include "auxTypes.h"

#ifndef EXCEPTION_DEFINED
#define EXCEPTION_DEFINED

#define EXIT_FAIL -1
#define str(s) #s

/* Define uma macro pra printar erros */
#define stderror(line, ...){ \
    /*fprintf(stderr, "\033[0;91m"); \*/\
    if(0 < (line) && (line) < IAS_MAX_LINE_NUMBER){ \
		fprintf(stderr, "ERROR on line %d\n", (line)); \
	} \
	fprintf(stderr, __VA_ARGS__); \
    /* fprintf(stderr, "\033[0;00m");  \*/\
}
/* Similar ao assert, mas não foi ultilizada */
#define make_sure(line, condition, what_to_do , ...) {\
    if(!(condition)){ \
        stderror(line, __VA_ARGS__); \
        what_to_do; \
    } \
}
#endif

#include <stdio.h>
#include "auxTypes.h"

#ifndef EXCEPTION_DEFINED
#define EXCEPTION_DEFINED

#define EXIT_FAIL -1
#define str(s) #s
/*
#define stderror(msg, line){ \
    throw( \
        new_error_exception( \
            (msg), (line) \
        )\
        exit(EXIT_FAIL); \
    ); \
}
*/
#define stderror(line, ...){ \
    fprintf(stderr, "\033[0;91m"); \
    if((line) < IAS_MAX_LINE_NUMBER){ \
		fprintf(stderr, "ERROR on line %d\n", (line)); \
	} \
	fprintf(stderr, __VA_ARGS__); \
    fprintf(stderr, "\033[0;00m"); \
}

#define make_sure(line, condition, what_to_do , ...) {\
    if(!(condition)){ \
        stderror(line, __VA_ARGS__); \
        what_to_do; \
    } \
}

typedef enum TypeException{
    ERROR,
    WARNING
} TypeException;



typedef struct sException{
    TypeException type;
    bool complete;
    String msg;
    unsigned short int line;
} sException, *Exception;

Exception new_error_exception(String _msg, unsigned short int _line);
void throw(Exception e);

#endif

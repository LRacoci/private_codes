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
#define stderror(line, msg){ \
    if((line) < IAS_MAX_LINE_NUMBER){ \
		fprintf(stderr, "ERROR on line %d\n", (line)); \
	} \
		fprintf(stderr, msg); \
		exit(EXIT_FAIL); \
}

#define make_sure(condition, mesg, line) {\
    if(!(x)){ \
        stderror(y , line); \
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
Exception start_error_exception(String _msg);
Exception new_warning_exception(String _msg, unsigned short int _line);
Exception start_warning_exception(String _msg);

void set_line_exception(Exception e, unsigned short int line);
void throw(Exception e);

#endif

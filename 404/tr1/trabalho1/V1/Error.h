#include <stdio.h>
#include "auxTypes.h"

#ifndef EXCEPTION_DEFINED
#define EXCEPTION_DEFINED

#define EXIT_FAIL -1
#define str(s) #s

#define make_sure(x, y) {\
    if(!x){ \
        stderror(new_error_exception(y , -1)); \
        exit(EXIT_FAIL); \
    } \
}

typedef enum TypeException{
    ERROR,
    WARNING
} TypeException;



typedef struct sException{
    TypeException type;
    bool incomplete;
    String msg;
    unsigned short int line;
} sException, *Exception;

void new_error_exception(String _msg, unsigned short int _line);
void start_error_exception(String _msg);
void new_warning_exception(Exception* e,String _msg, unsigned short int _line);
void start_warning_exception(Exception* e,String _msg);

void set_line_exception(Exception e, unsigned short int line);
void stderror(Exception e);

#endif

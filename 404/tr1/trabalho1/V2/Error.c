#include <stdio.h>
#include <stdlib.h>
#include "iasDefs.h"
#include "auxTypes.h"
#include "Error.h"

Exception aux_exception_creator(
	TypeException _type,
	 bool _complete, String _msg,
	 unsigned short int _line
){
	Exception e = malloc(sizeof(sException));
	e->type = _type;
	e->complete = _complete;
	e->msg = _msg;
	e->line = _line;
	return e;
}
Exception new_error_exception(
	String _msg,
	unsigned short int _line
){
	return aux_exception_creator(ERROR, true, _msg, _line);
}
Exception start_error_exception(String _msg){
	return aux_exception_creator(ERROR, false, _msg, -1);
}
Exception new_warning_exception(String _msg, unsigned short int _line){
	return aux_exception_creator(WARNING, true, _msg, _line);
}
Exception start_warning_exception(String _msg){
	return aux_exception_creator(WARNING, false, _msg, -1);
}
void set_line_exception(Exception e, unsigned short int _line){
	if(!e) return;
	e->line = _line;
	e->complete = true;
}
void stderror(Exception exc){
	if(exc == NULL || ! exc->complete){
		return;
	}
	if(exc->line < IAS_MAX_LINE_NUMBER){
		fprintf(stderr, "ERROR on line %d\n", exc->line);
	}
		fprintf(stderr, "%s\n", exc->msg);
		free(exc);
		exit(EXIT_FAIL);
}

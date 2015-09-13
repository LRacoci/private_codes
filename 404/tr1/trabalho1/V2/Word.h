#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "auxTypes.h"
#include "iasDefs.h"
#include "genericDefs.h"
#include "Error.h"
#include "Data.h"

bool char_in_string(char target, String s);
bool element_of(
    String e,
    char vet[][MAX_INSTR],
    func_comp cmp,
    unsigned int size
);

unsigned int fgetword(FILE * src, String * str);

String get_part_string(String src, int ini, int fim);
